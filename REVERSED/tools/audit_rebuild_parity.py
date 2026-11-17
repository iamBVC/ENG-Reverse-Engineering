"""Trace each independently identified EXE function from Ghidra export to EXE input.

This is a provenance audit, not a claim that decompiled C is behaviorally equal
to the original machine code. It only reads files; it never rebuilds or runs the
game. Run after make_bulk.py, compile_check.py, and make_dll_source.py --exe.
"""

from __future__ import annotations

import csv
import hashlib
import json
import re
from collections import Counter
from datetime import datetime, timezone
from pathlib import Path

from make_bulk import collect_source_files, is_game_code, read_merged_function_fragments


ROOT = Path(__file__).resolve().parents[1]
MARKER = re.compile(r"^/\* ==== (\S+) ==== \*/", re.M)
ADDRESS = re.compile(r"(?:0x)?([0-9a-fA-F]{6,8})$")

# Original CRT bodies intentionally removed from the EXE inputs. Their behavior
# is provided by a modern CRT or an explicit harness implementation.
LEGACY_CRT_REPLACEMENTS = {
    "sub_562AEE": "harness/crt_aliases.c: modern fopen wrapper",
    "sub_562B75": "harness/crt_aliases.c: modern fwrite wrapper",
    "sub_5628EB": "harness/crt_aliases.c: modern fclose wrapper",
    "sub_562717": "harness/crt_aliases.c: modern vsprintf wrapper",
    "sub_56279D": "harness/crt_aliases.c: modern strtok wrapper",
    "sub_56C7DF": "harness/crt_aliases.c: modern _chsize wrapper",
    "sub_5629E6": "harness/crt_aliases.c: modern fread wrapper",
    "sub_56294C": "harness/crt_aliases.c: modern fseek wrapper",
    "sub_5639C2": "harness/crt_aliases.c: modern ftell wrapper",
    "sub_5628BC": "harness/crt_aliases.c: modern free wrapper",
    "sub_562640": "modern CRT onexit table via recovered sub_5626AD",
    "sub_5626BF": "modern CRT onexit table via recovered sub_5626AD",
    "sub_5645F3": "modern CRT onexit table via recovered sub_5626AD",
    "sub_56753F": "modern CRT startup replaces legacy _ioinit",
}


def rows(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8-sig") as stream:
        return list(csv.DictReader(stream))


def address_of(value: str) -> int | None:
    match = ADDRESS.search(value.strip())
    return int(match.group(1), 16) if match else None


def generated_name(value: str) -> str:
    """Ghidra's Catch@/Unwind@ labels are sanitized to C identifiers."""
    return value.replace("@", "_")


def markers(path: Path) -> set[str]:
    if not path.exists():
        raise FileNotFoundError(path)
    return set(MARKER.findall(path.read_text(encoding="utf-8", errors="replace")))


def marked_bodies(path: Path) -> dict[str, str]:
    text = path.read_text(encoding="utf-8", errors="replace")
    blocks = re.split(r"(?=^/\* ==== \S+ ==== \*/)", text, flags=re.M)
    return {match.group(1): block for block in blocks if (match := MARKER.match(block))}


def body_mismatches(reference: dict[str, str], observed: dict[str, str]) -> list[str]:
    """Return observed bodies that differ from their corresponding source body."""
    return sorted(name for name, body in observed.items()
                  if reference.get(name) != body)


def body_gap_report(all_bodies: set[str], exe_bodies: set[str],
                    runtime_replacements: set[str]) -> dict[str, list[str]]:
    """Separate missing EXE bodies from known bodies replaced by the runtime.

    A generated legacy CRT function can be intentionally absent from the rebuilt
    EXE because its behavior is supplied by a modern CRT or a recovered helper.
    Those expected substitutions must not be reported as missing game functions.
    """
    omitted = all_bodies - exe_bodies
    return {
        "unresolved_generated_bodies": sorted(omitted - runtime_replacements),
        "runtime_replacement_bodies": sorted(omitted & runtime_replacements),
        "missing_runtime_replacement_bodies": sorted(runtime_replacements - all_bodies),
        "unexpectedly_included_replacements": sorted(runtime_replacements & exe_bodies),
    }


def utc_mtime(path: Path) -> str:
    return datetime.fromtimestamp(path.stat().st_mtime, timezone.utc).isoformat()


def file_hash(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def classify(*, exported: bool, selected: bool, generated: bool,
             compiled_input: bool, stub: bool, game_code: bool,
             runtime_replacement: bool = False) -> str:
    """Rank a function's *provenance*; none of these states means parity."""
    if not exported:
        return "no_ghidra_export"
    if runtime_replacement:
        return "runtime_replacement"
    if not game_code:
        return "excluded_runtime_or_artifact"
    if not selected:
        return "export_not_selected"
    if not generated:
        return "selected_not_generated"
    if not compiled_input:
        return "not_in_exe_compile_input"
    if stub:
        return "compiled_input_with_stub"
    return "in_exe_compile_input"


def classify_merged_fragment(parent_in_exe_compile_input: bool) -> str:
    """A split Ghidra entry is covered only when its recovered parent is compiled."""
    return "covered_by_parent_body" if parent_in_exe_compile_input else "missing_parent_body"


def audit(root: Path) -> tuple[list[dict[str, object]], dict[str, object]]:
    comparison = root / "build" / "radare2_ghidra_function_comparison_20261017.csv"
    baseline = root / "decompiled_ghidra_complete_20261018_all"
    original = root.parent / "Game" / "groove.exe"
    exported = {address_of(row["address"]): row for row in rows(baseline / "_index.csv")}
    source_files = collect_source_files([baseline], root / "src_recovered")
    merged_fragments = read_merged_function_fragments(
        root / "src_generated" / "merged_function_fragments.csv")
    named_exports = {row["name"]: address for address, row in exported.items()}
    selected = {}
    for name, (path, _) in source_files.items():
        address = address_of(name)
        if address is None:
            address = named_exports.get(name)
        if address is None or address in selected:
            raise ValueError(f"unmapped or duplicate selected source: {name}")
        selected[address] = (name, path)
    all_bodies = markers(root / "src_generated" / "bulk_all.c")
    clean_bodies = markers(root / "src_generated" / "clean_subset.c")
    exe_bodies: set[str] = set()
    chunk_paths = list((root / "build" / "exe_chunks").glob("*.c"))
    if not chunk_paths:
        raise FileNotFoundError(root / "build" / "exe_chunks")
    for path in chunk_paths:
        exe_bodies.update(markers(path))
    all_blocks = marked_bodies(root / "src_generated" / "bulk_all.c")
    exe_blocks = {}
    for path in chunk_paths:
        exe_blocks.update(marked_bodies(path))
    exe_body_mismatches = body_mismatches(all_blocks, exe_blocks)
    stubs = {row.get("c_name", "") for row in rows(root / "src_generated" / "link_stubs.csv")}
    patches = Counter(row["function"] for row in rows(root / "src_generated" / "bulk_patches.csv"))
    original_entries: dict[int, dict[str, str]] = {}
    for row in rows(comparison):
        if row["Binary"].lower() != "groove.exe":
            continue
        address = address_of(row["Address"])
        if address is None or address in original_entries:
            raise ValueError(f"invalid or duplicate EXE comparison address: {row['Address']}")
        original_entries[address] = row

    result: list[dict[str, object]] = []
    for address, comparison_row in sorted(original_entries.items()):
        export = exported.get(address)
        chosen = selected.get(address)
        name = chosen[0] if chosen else (export or {}).get("name", "")
        c_name = generated_name(name)
        merged_parent = merged_fragments.get(name)
        game_code = is_game_code(name)
        replacement = LEGACY_CRT_REPLACEMENTS.get(name, "")
        generated = c_name in all_bodies
        exe_input = c_name in exe_bodies
        if merged_parent:
            merged_parent_in_exe = generated_name(merged_parent) in exe_bodies
            status = classify_merged_fragment(merged_parent_in_exe)
        else:
            merged_parent_in_exe = False
            status = classify(exported=export is not None, selected=chosen is not None,
                              generated=generated, compiled_input=exe_input,
                              stub=c_name in stubs, game_code=game_code,
                              runtime_replacement=bool(replacement))
        result.append({
            "address": f"{address:08X}",
            "ghidra_name": (export or {}).get("name", ""),
            "ghidra_status": (export or {}).get("status", "missing"),
            "radare2_class": comparison_row["Classification"],
            "selected_name": name,
            "selected_source": chosen[1].relative_to(root).as_posix() if chosen else "",
            "obligation_class": ("merged_code_fragment" if merged_parent
                                 else "compiler_eh_artifact" if name.startswith(("Catch@", "Unwind@"))
                                 else "crt_entry" if name == "entry"
                                 else "legacy_crt_replacement" if replacement
                                 else "runtime_or_import" if not game_code else "in_image_code"),
            "runtime_replacement": replacement,
            "merged_into": merged_parent or "",
            "merged_parent_in_exe": merged_parent_in_exe,
            "hand_recovered": bool(chosen and chosen[1].parent == root / "src_recovered"),
            "patch_count": patches[c_name],
            "generated_bulk": generated,
            "clean_subset": c_name in clean_bodies,
            "exe_compile_input": exe_input,
            "link_stub_symbol": c_name in stubs,
            "status": status,
        })

    extras = {
        "original_sha256": file_hash(original),
        "comparison_entries": len(original_entries),
        "export_entries": len(exported),
        "selected_entries": len(selected),
        "generated_bodies": len(all_bodies),
        "clean_bodies": len(clean_bodies),
        "exe_input_bodies": len(exe_bodies),
        "exe_body_mismatches_vs_bulk_all": exe_body_mismatches,
        "status_counts": dict(sorted(Counter(str(row["status"]) for row in result).items())),
        "obligation_counts": dict(sorted(Counter(str(row["obligation_class"]) for row in result).items())),
        "hand_recovered_count": sum(bool(row["hand_recovered"]) for row in result),
        "merged_code_fragment_count": sum(row["obligation_class"] == "merged_code_fragment"
                                          for row in result),
        "uncovered_merged_code_fragment_count": sum(row["obligation_class"] == "merged_code_fragment"
                                                    and not row["merged_parent_in_exe"] for row in result),
        "patched_function_count": sum(int(row["patch_count"]) > 0 for row in result),
        "in_image_code_excluded_count": sum(row["obligation_class"] == "in_image_code"
                                             and not row["exe_compile_input"] for row in result),
        "in_image_code_stub_count": sum(row["obligation_class"] == "in_image_code"
                                         and row["link_stub_symbol"] for row in result),
        **body_gap_report(all_bodies, exe_bodies, set(LEGACY_CRT_REPLACEMENTS)),
        "exe_input_without_comparison_entry": sorted(exe_bodies - {generated_name(str(row["selected_name"])) for row in result}),
    }
    staged_exe = root / "build" / "run" / "groove_rebuild.exe"
    if staged_exe.exists():
        current_inputs = [path for path, _ in source_files.values()]
        current_inputs.extend([root / "tools" / "make_bulk.py",
                               root / "src_generated" / "bulk_patches.csv",
                               root / "src_generated" / "type_overrides.csv",
                               root / "src_generated" / "merged_function_fragments.csv"])
        generated_c = root / "src_generated" / "bulk_all.c"
        newest_source = max(current_inputs, key=lambda path: path.stat().st_mtime_ns)
        newest_chunk = max(chunk_paths, key=lambda path: path.stat().st_mtime_ns)
        extras["staged_exe_sha256"] = file_hash(staged_exe)
        extras["stage_timestamps_utc"] = {
            "newest_source": [newest_source.relative_to(root).as_posix(), utc_mtime(newest_source)],
            "generated_c": utc_mtime(generated_c),
            "newest_exe_chunk": utc_mtime(newest_chunk),
            "staged_exe": utc_mtime(staged_exe),
        }
        extras["stage_timestamp_order_ok"] = (
            newest_source.stat().st_mtime_ns <= generated_c.stat().st_mtime_ns
            <= newest_chunk.stat().st_mtime_ns <= staged_exe.stat().st_mtime_ns)
    return result, extras


def main() -> int:
    result, summary = audit(ROOT)
    output = ROOT / "build" / "rebuild_parity_audit.csv"
    with output.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=result[0].keys())
        writer.writeheader()
        writer.writerows(result)
    summary_path = ROOT / "build" / "rebuild_parity_audit.json"
    summary_path.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: value for key, value in summary.items()
                      if key not in {"unresolved_generated_bodies", "exe_input_without_comparison_entry"}},
                     indent=2))
    print(f"rows: {output}\nsummary: {summary_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
