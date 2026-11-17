"""Compare a fresh Ghidra function inventory with the reconstruction sources."""

from __future__ import annotations

import argparse
import csv
import re
from collections import Counter, defaultdict
from pathlib import Path


SOURCE_ROLES = {
    "src": "source",
    "src_recovered": "recovered",
    "src_generated": "generated",
    "harness": "harness",
    "decompiled": "decompiled",
}
SYMBOL_RE = re.compile(r"\b(?:thunk_)?(?:sub|FUN)_[0-9A-Fa-f]{6,8}\b")
COMMENT_RE = re.compile(r"/\*.*?\*/|//[^\r\n]*", re.DOTALL)
IMPORT_THUNK_MODULES = {
    "DirectDrawEnumerateA": "DDRAW.dll",
    "DirectDrawEnumerateExA": "DDRAW.dll",
    "DirectDrawCreate": "DDRAW.dll",
    "DirectInputCreateA": "DINPUT.dll",
    "RtlUnwind": "KERNEL32.dll",
}
RUNTIME_FUNCTIONS = {
    "__nh_malloc": (
        "runtime_internal",
        "excluded CRT allocation callers are replaced by modern malloc/operator_new",
    ),
    "__NLG_Notify1": (
        "runtime_replacement",
        "harness/recovered_crt_helpers.c: groove_nlg_notify1",
    ),
    "__freebuf": (
        "runtime_internal",
        "legacy FILE helper is called only by excluded fclose; modern fclose is active",
    ),
    "__CxxThrowException@8": (
        "runtime_replacement",
        "harness/recovered_crt_helpers.c: __CxxThrowException_8",
    ),
    "__CallSettingFrame@12": (
        "runtime_replacement",
        "harness/recovered_crt_helpers.c: __CallSettingFrame_12",
    ),
}


def normalize_address(value: str) -> str:
    """Normalize Ghidra/CSV addresses while retaining external address identity."""
    value = (value or "").strip()
    if "EXTERNAL:" in value.upper():
        return "EXTERNAL:" + value.split(":", 1)[-1].upper()
    match = re.search(r"(?:0x)?([0-9A-Fa-f]{6,16})$", value)
    return match.group(1).upper().lstrip("0") or "0" if match else value.upper()


def address_from_symbol(name: str) -> str | None:
    match = re.fullmatch(r"(?:thunk_)?(?:sub|FUN)_([0-9A-Fa-f]{6,8})", name)
    return normalize_address(match.group(1)) if match else None


def _matching_paren(text: str, open_index: int) -> int | None:
    depth = 0
    for index in range(open_index, len(text)):
        if text[index] == "(":
            depth += 1
        elif text[index] == ")":
            depth -= 1
            if depth == 0:
                return index
    return None


def _definitions(path: Path, symbols: set[str]) -> list[tuple[str, int]]:
    if not symbols:
        return []
    try:
        text = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return []
    # Keep newlines so the original source line can be reported.
    text = COMMENT_RE.sub(lambda match: "\n" * match.group(0).count("\n"), text)
    alternatives = "|".join(re.escape(name) for name in sorted(symbols, key=len, reverse=True))
    pattern = re.compile(r"\b(" + alternatives + r")\s*\(")
    found = []
    for match in pattern.finditer(text):
        open_index = text.find("(", match.start(), match.end())
        close_index = _matching_paren(text, open_index)
        if close_index is None:
            continue
        cursor = close_index + 1
        # Function declarations may carry a calling-convention attribute between
        # the parameter list and body. A statement terminator means this was only
        # a prototype or call.
        while cursor < len(text) and text[cursor].isspace():
            cursor += 1
        if text.startswith("__declspec", cursor) or text.startswith("__attribute__", cursor):
            brace = text.find("{", cursor, min(len(text), cursor + 256))
            semicolon = text.find(";", cursor, min(len(text), cursor + 256))
            if brace < 0 or (semicolon >= 0 and semicolon < brace):
                continue
        elif cursor >= len(text) or text[cursor] != "{":
            continue
        line = text.count("\n", 0, match.start()) + 1
        found.append((match.group(1), line))
    return found


def _read_csv(path: Path) -> list[dict[str, str]]:
    if not path.exists():
        return []
    with path.open(newline="", encoding="utf-8-sig") as stream:
        return list(csv.DictReader(stream))


def audit(manifest_path: Path, root: Path, previous_manifest: Path | None = None) -> list[dict[str, str]]:
    """Return one source-coverage row for each function in a Ghidra manifest."""
    functions = _read_csv(manifest_path)
    if not functions:
        raise ValueError(f"function manifest is missing or empty: {manifest_path}")

    function_names = {row.get("name", "").strip() for row in functions if row.get("name")}
    sanitized_eh_names = {
        re.sub(r"[^A-Za-z0-9_]", "_", name): name
        for name in function_names
        if name.startswith(("Catch@", "Unwind@"))
    }
    by_address: dict[str, list[str]] = defaultdict(list)
    for function in functions:
        name = function.get("name", "").strip()
        address = normalize_address(function.get("address", ""))
        if address and not address.startswith("EXTERNAL:"):
            by_address[address].append(name)

    def owner_for(symbol: str) -> str | None:
        if symbol in sanitized_eh_names:
            return sanitized_eh_names[symbol]
        address = address_from_symbol(symbol)
        if address:
            matches = by_address.get(address, [])
            return matches[0] if len(matches) == 1 else None
        return symbol if symbol in function_names else None

    symbols = function_names | set(sanitized_eh_names)
    candidates: dict[str, list[tuple[str, str, int]]] = defaultdict(list)
    for folder, default_role in SOURCE_ROLES.items():
        source_root = root / folder
        if not source_root.exists():
            continue
        for path in source_root.rglob("*"):
            if path.suffix.lower() not in {".c", ".h"} or not path.is_file():
                continue
            relative = path.relative_to(root).as_posix()
            if folder == "src_generated" and path.name == "link_stubs.c":
                role = "link_stub"
            elif folder == "src_generated" and path.name == "bulk_all.c":
                role = "generated_bulk"
            elif folder == "src_generated" and path.name == "clean_subset.c":
                role = "generated_subset"
            elif folder == "src_generated" and "chunks" in path.parts:
                role = "generated_chunks"
            else:
                role = default_role
            scan_symbols = symbols | {match.group(0) for match in SYMBOL_RE.finditer(
                COMMENT_RE.sub(lambda match: "\n" * match.group(0).count("\n"),
                               path.read_text(encoding="utf-8", errors="replace")))}
            for name, line in _definitions(path, scan_symbols):
                owner = owner_for(name)
                if owner:
                    candidates[owner].append((role, relative, line))

    decomp_status = {
        row.get("name", "").strip(): row.get("status", "unknown").strip()
        for row in _read_csv(manifest_path.with_name("_index.csv"))
    }
    previous_manifest = previous_manifest or root / "decompiled" / "_functions.csv"
    previous_addresses = {
        normalize_address(row.get("address", ""))
        for row in _read_csv(previous_manifest)
        if row.get("address")
    }
    original_kinds = {
        normalize_address(row.get("address", "")): row.get("kind", "")
        for row in _read_csv(root / "functions.csv")
        if row.get("address") and row.get("kind")
    }
    original_addresses = {
        normalize_address(row.get("address", ""))
        for row in _read_csv(root / "functions.csv")
        if row.get("address")
    }

    rows = []
    for function in functions:
        name = function.get("name", "").strip()
        address = function.get("address", "").strip()
        normalized_address = normalize_address(address)
        found = candidates.get(name, [])
        active = [item for item in found if item[0] != "decompiled"]
        direct = [item for item in active if item[0] in {"source", "recovered", "harness"}]
        generated = [item for item in active if item[0].startswith("generated_")]
        stubs = [item for item in active if item[0] == "link_stub"]
        is_thunk = name.startswith("thunk_") or original_kinds.get(normalize_address(address)) == "thunk"
        original_kind = original_kinds.get(normalize_address(address), "")
        runtime_status, runtime_provider = RUNTIME_FUNCTIONS.get(name, ("", ""))
        if "EXTERNAL:" in address.upper():
            status = "external"
        elif name in IMPORT_THUNK_MODULES:
            # These six-byte bodies are import jumps, not missing C routines.
            # Their API implementations live in the named Windows DLL; the rebuild
            # links the same exports directly or through the harness import bridge.
            status = "import_thunk"
        elif runtime_status:
            status = runtime_status
        elif len(direct) > 1 or (stubs and (direct or generated)):
            status = "duplicate"
        elif stubs:
            status = "link_stub"
        elif direct and direct[0][0] == "harness" and not generated:
            status = "runtime_replacement"
        elif direct or generated:
            status = "implemented"
        elif found:
            status = "thunk_decompiled_only" if is_thunk else "decompiled_only"
        else:
            status = "thunk_missing" if is_thunk else "missing"

        # Ghidra can split an internal switch target into a pseudo-function even
        # though its bytes are already part of a larger function body. Report these
        # separately from absent bodies, but only when the containing function has
        # an active source definition. This preserves the overlap for review rather
        # than silently counting it as independently implemented.
        overlapping_functions: list[str] = []
        if address and not address.upper().startswith("EXTERNAL:"):
            try:
                fragment_start = int(normalized_address, 16)
                fragment_end = fragment_start + int(function.get("size", "0"))
            except ValueError:
                fragment_start = fragment_end = 0
            if fragment_end > fragment_start:
                for container in functions:
                    container_name = container.get("name", "").strip()
                    if not container_name or container_name == name:
                        continue
                    container_address = normalize_address(container.get("address", ""))
                    try:
                        container_start = int(container_address, 16)
                        container_end = container_start + int(container.get("size", "0"))
                    except ValueError:
                        continue
                    if (container_start < fragment_start and
                            fragment_end <= container_end and
                            any(role != "decompiled" for role, _, _ in candidates.get(container_name, []))):
                        overlapping_functions.append(container_name)
                if status == "decompiled_only" and overlapping_functions:
                    status = "overlapping_fragment"

        if "EXTERNAL:" in address.upper():
            obligation = "external"
        elif name in IMPORT_THUNK_MODULES:
            obligation = "external_import_thunk"
        elif runtime_status:
            obligation = runtime_status
        elif name.startswith(("Catch@", "Unwind@")):
            obligation = "compiler_eh_artifact"
        elif name.startswith(("__CxxThrowException@", "__CallSettingFrame@")):
            obligation = "compiler_runtime_helper"
        elif is_thunk:
            obligation = "thunk"
        elif name.startswith("FUN_"):
            obligation = "unlabelled_in_image_function"
        elif normalize_address(address) not in original_addresses:
            obligation = "fresh_only_function"
        elif original_kind == "library":
            obligation = "runtime_library"
        else:
            obligation = "named_function"

        fallback = any(role == "decompiled" and path.startswith("decompiled/rea/")
                       for role, path, _ in found)
        if decomp_status.get(name) == "ok":
            pseudocode_source = "fresh_ghidra"
        elif fallback:
            pseudocode_source = "rea_fallback"
        else:
            pseudocode_source = "none"

        rows.append({
            "name": name,
            "address": address,
            "size": function.get("size", ""),
            "decompile_status": decomp_status.get(name, "unknown"),
            "pseudocode_source": pseudocode_source,
            "previous_export": "yes" if normalize_address(address) in previous_addresses else "no",
            "original_inventory": "yes" if normalize_address(address) in original_addresses else "no",
            "original_kind": original_kind,
            "overlapping_functions": ";".join(sorted(overlapping_functions)),
            "import_module": IMPORT_THUNK_MODULES.get(name, ""),
            "runtime_provider": runtime_provider,
            "obligation_class": obligation,
            "source_status": status,
            "candidate_count": str(len(found)),
            "active_definition_count": str(len(direct) + bool(generated) + bool(stubs)),
            "candidates": ";".join(f"{role}:{path}:{line}" for role, path, line in found),
        })
    return rows


def write_report(rows: list[dict[str, str]], output: Path) -> Counter[str]:
    fields = ["name", "address", "size", "decompile_status", "pseudocode_source",
              "previous_export", "original_inventory", "original_kind", "overlapping_functions",
              "import_module", "runtime_provider",
              "obligation_class",
              "source_status", "candidate_count", "active_definition_count", "candidates"]
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields)
        writer.writeheader()
        writer.writerows(rows)
    return Counter(row["source_status"] for row in rows)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--manifest", type=Path, help="Ghidra _functions.csv; defaults to decompiled_fresh/_functions.csv")
    parser.add_argument("--output", type=Path, help="CSV output; defaults to decompiled_fresh/source_coverage.csv")
    parser.add_argument("--previous-manifest", type=Path, help="prior Ghidra _functions.csv for address-based drift checks")
    args = parser.parse_args()

    root = args.root.resolve()
    manifest = (args.manifest or root / "decompiled_fresh" / "_functions.csv").resolve()
    output = (args.output or root / "decompiled_fresh" / "source_coverage.csv").resolve()
    rows = audit(manifest, root, args.previous_manifest)
    counts = write_report(rows, output)
    print(f"Fresh function rows: {len(rows)}")
    print("Source coverage: " + ", ".join(f"{key}={counts[key]}" for key in sorted(counts)))
    print(f"Manifest: {manifest}")
    print(f"Coverage report: {output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
