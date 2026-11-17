"""compile_check.py - how much of the decompiled bulk actually compiles?

Compiles `src_generated/clean_subset.c` in chunks (one translation unit per few
dozen functions) and reports, per function, whether the compiler accepted it.

Why chunks: MSVC gives up after ~100 errors in a translation unit (C1003).  A
single huge file therefore stops being checked part-way through, and "function X
produced no error" would be meaningless for everything after the cap.  With small
chunks every function's verdict is real, and a chunk that still hits the cap is
reported so it can be split further.

    python tools/compile_check.py
    python tools/compile_check.py --chunk 20
    python tools/compile_check.py --all --chunk 20
"""

from __future__ import annotations

import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "src_generated"
BUILD = ROOT / "build"
VS_CANDIDATES = [
    r"C:\Program Files\Microsoft Visual Studio\2022\Community",
    r"F:\Programmi\Microsoft Visual Studio\2022\Community",
]
MARKER = re.compile(r"^/\* ==== ([\w@]+) ==== \*/")


def compile_source_path(include_all: bool) -> Path:
    """Choose the compiler input without changing the default clean-subset flow."""
    return OUT / ("bulk_all.c" if include_all else "clean_subset.c")


def compiler_input_groups(chunks: list[Path], max_files: int = 30) -> list[list[Path]]:
    """Keep each cl.exe command below cmd.exe's practical argument-length limit."""
    if max_files < 1:
        raise ValueError("max_files must be positive")
    return [chunks[i:i + max_files] for i in range(0, len(chunks), max_files)]


def updated_failed_functions(previous: set[str], compiled: set[str],
                             bad: set[str]) -> set[str]:
    """Keep untested worklist entries, replace results for functions compiled now."""
    # Older exporter runs stored Ghidra's raw `Catch@...`/`Unwind@...` names;
    # generated C now uses the sanitized identifiers, so retire those stale entries
    # when the corresponding functions are included in a clean compile pass.
    normalized_previous = {re.sub(r"[^A-Za-z0-9_]", "_", name) for name in previous}
    return (normalized_previous - compiled) | bad


def write_batch(chunks: list[Path]) -> Path:
    vsdir = next((c for c in VS_CANDIDATES if (Path(c) / "VC/Auxiliary/Build/vcvars32.bat").exists()),
                 None)
    if vsdir is None:
        raise SystemExit("no Visual Studio installation found; edit VS_CANDIDATES")
    groups = compiler_input_groups(chunks)
    batch = BUILD / "_bulk_compile.bat"
    lines = [
        "@echo off",
        f'call "{vsdir}\\VC\\Auxiliary\\Build\\vcvars32.bat" >nul',
        f'cd /d "{BUILD}"',
        'set "CL_FAILED=0"',
    ]
    for i, group in enumerate(groups):
        # Compile shared data definitions once, alongside the final group.
        sources = list(group)
        if i == len(groups) - 1:
            sources.append(OUT / "ghidra_globals.c")
        cl_list = " ".join(f'"{p}"' for p in sources)
        redirect = ">" if i == 0 else ">>"
        lines.extend([
            f'cl /nologo /c /TC /W0 /GS- /MD /I"{ROOT}\\include" /I"{OUT}" '
            f'{cl_list} {redirect} "_bulk_compile.log" 2>&1',
            'if errorlevel 1 set "CL_FAILED=1"',
        ])
    lines.append("exit /b %CL_FAILED%")
    batch.write_text("\r\n".join(lines) + "\r\n", encoding="ascii")
    return batch


def main() -> int:
    chunk_size = 40
    include_all = "--all" in sys.argv
    if "--chunk" in sys.argv:
        chunk_size = int(sys.argv[sys.argv.index("--chunk") + 1])

    src = compile_source_path(include_all)
    if not src.exists():
        print(f"{src} missing - run tools/make_bulk.py first")
        return 1
    text = src.read_text(encoding="utf-8", errors="replace")
    if "/* ==== " not in text:
        print(f"{src.name} has no function markers; regenerate with make_bulk.py")
        return 1
    preamble = text[:text.index("/* ==== ")]
    blocks = re.split(r"(?=^/\* ==== )", text[text.index("/* ==== "):], flags=re.M)[1:]
    names = [MARKER.match(b).group(1) for b in blocks if MARKER.match(b)]

    chunk_dir = OUT / "chunks"
    chunk_dir.mkdir(exist_ok=True)
    for f in chunk_dir.glob("*.c"):
        f.unlink()
    chunk_files: list[Path] = []
    for i in range(0, len(blocks), chunk_size):
        p = chunk_dir / f"chunk_{i // chunk_size:03d}.c"
        p.write_text(preamble + "".join(blocks[i:i + chunk_size]), encoding="utf-8")
        chunk_files.append(p)

    BUILD.mkdir(exist_ok=True)
    batch = write_batch(chunk_files)
    proc = subprocess.run(["cmd", "/c", str(batch)], capture_output=True, text=True)
    log = BUILD / "_bulk_compile.log"
    logtext = log.read_text(encoding="latin1", errors="replace") if log.exists() else ""

    # which function owns each reported error
    owners: dict[str, dict[int, str]] = {}
    for p in chunk_files:
        own: dict[int, str] = {}
        cur = "?"
        for i, line in enumerate(p.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
            m = MARKER.match(line)
            if m:
                cur = m.group(1)
            own[i] = cur
        owners[p.name] = own

    bad: Counter = Counter()
    per_chunk_errors: Counter = Counter()
    for fname, line in re.findall(r"(chunk_\d+\.c)\((\d+)\): error", logtext):
        per_chunk_errors[fname] += 1
        bad[owners.get(fname, {}).get(int(line), "?")] += 1

    capped = sorted(f for f, n in per_chunk_errors.items() if n >= 95)
    errors = re.findall(r"error (C\d+):", logtext)

    label = "all generated functions" if include_all else "clean subset of the decompiled bulk"
    print(f"--- chunked compile of {label} (C mode) ---")
    print(f"chunks                    : {len(chunk_files)} x <= {chunk_size} functions")
    print(f"cl exit code              : {proc.returncode}")
    print(f"errors reported           : {len(errors)}")
    for code, n in Counter(errors).most_common(8):
        print(f"   {code}  x{n}")
    if capped:
        print(f"chunks that hit the error cap: {', '.join(capped)} (rerun with --chunk {chunk_size // 2})")
    print()
    print(f"functions compiled        : {len(names)}")
    print(f"  with a reported error   : {len(bad)}")
    if proc.returncode == 0 and not errors:
        print(f"  compiling cleanly       : {len(names)}")
    else:
        print("  compilation incomplete  : failed chunks or shared-header errors; see log")
    print("worst offenders:")
    for name, n in bad.most_common(10):
        print(f"   {name:<18} {n} error(s)")
    print(f"\nlog: {log}")

    # Two things depend on knowing which functions fail:
    #   * MSVC emits NO object file for a translation unit that had any error, so
    #     a chunk containing one bad function yields nothing to link.  Excluding
    #     the failures (make_bulk.py reads this list) is what makes the chunks
    #     buildable, and the loop converge.
    #   * it is the work queue for the hand fixes.
    # Keep failures not present in this invocation, but replace the status of every
    # function that was just compiled. This lets an all-functions clean pass clear
    # stale exclusions and restore those functions to the clean subset.
    failed = OUT / "failed.txt"
    previously = set()
    if failed.exists():
        previously = {ln.strip() for ln in failed.read_text(encoding="utf-8").splitlines() if ln.strip()}
    allbad = updated_failed_functions(previously, set(names), set(bad))
    failed.write_text("\n".join(sorted(allbad)) + ("\n" if allbad else ""), encoding="utf-8")
    print(f"failures written to {failed}: {len(bad)} current, {len(allbad)} pending")
    return 0 if proc.returncode == 0 and not errors else 1


if __name__ == "__main__":
    raise SystemExit(main())
