#!/usr/bin/env python3
"""
wad_extractor.py — main CLI entry point for Emperor's New Groove WAD tools.

This script intentionally stays small.  The actual reverse-engineering logic is
split into modules under eng_wad/ so each chunk parser can be studied separately.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from eng_wad.binary import Reader, u32
from eng_wad.light_chunk import export_lights, parse_lght_chunk
from eng_wad.map_chunk import parse_map_chunk
from eng_wad.map_export import export_map_outputs
from eng_wad.raw_export import RAW_EXPORTS, export_raw_chunk
from eng_wad.stpc_chunk import export_stpc_meshes_from_bytes
from eng_wad.text_chunk import export_textures, parse_text_chunk
from eng_wad.wad import chunk_bytes, chunk_manifest_lines, read_wad


def _write_level_metadata(data: bytes, by_tag: dict, out_dir: Path, info_lines: list[str]) -> None:
    """Write info.txt and level_name.txt from simple metadata chunks."""
    if "NAME" in by_tag:
        chunk = by_tag["NAME"]
        r = Reader(chunk_bytes(data, chunk))
        _name_count = r.u32()
        level_name = r.read(chunk.size - 4).rstrip(b"\x00").decode("latin-1", errors="replace")
        (out_dir / "level_name.txt").write_text(level_name + "\n", encoding="utf-8")
        info_lines.append(f"Level name  : {level_name}")
        print(f"  → level_name.txt ({level_name!r})")

    if "VERS" in by_tag:
        info_lines.append(f"Version     : {u32(data, by_tag['VERS'].offset)}")
    if "INFO" in by_tag:
        info_lines.append(f"INFO value  : {u32(data, by_tag['INFO'].offset)}")
    if "LNFO" in by_tag and by_tag["LNFO"].size >= 8:
        off = by_tag["LNFO"].offset
        info_lines.append(f"Light info  : count={u32(data, off)}, version={u32(data, off + 4)}")
    if "SPRT" in by_tag and by_tag["SPRT"].size >= 4:
        info_lines.append(f"Sprite count: {u32(data, by_tag['SPRT'].offset)}")


def extract_wad(
    wad_path: Path,
    out_dir: Path,
    *,
    extract_textures: bool = True,
    extract_map: bool = True,
    extract_stpc_obj: bool = True,
    extract_lights: bool = True,
    extract_raw: bool = True,
    texture_fields: bool = True,
    stpc_alignment: int = 4,
    stpc_min_score: float = 0.85,
    stpc_scale: float = 1.0,
    stpc_flip_z: bool = False,
    stpc_debug_faces: bool = False,
    verbose: bool = True,
) -> bool:
    """Extract one WAD file into a clean per-level output folder."""
    data, chunks, by_tag = read_wad(wad_path)
    if not chunks:
        print(f"ERROR: {wad_path.name}: no valid chunks found", file=sys.stderr)
        return False

    out_dir.mkdir(parents=True, exist_ok=True)

    print(f"\n{'=' * 72}")
    print(f"  {wad_path.name} ({len(data):,} bytes, {len(chunks)} chunks)")
    print(f"  → {out_dir}")
    print(f"{'=' * 72}")

    info_lines = chunk_manifest_lines(wad_path, data, chunks)
    _write_level_metadata(data, by_tag, out_dir, info_lines)
    (out_dir / "info.txt").write_text("\n".join(info_lines) + "\n", encoding="utf-8")
    print("  → info.txt")

    # TEXT: textures and palette/control-map diagnostics.
    if extract_textures and "TEXT" in by_tag:
        print("  [TEXT] Parsing textures/palette …")
        try:
            text = parse_text_chunk(chunk_bytes(data, by_tag["TEXT"]))
            export_textures(text, out_dir, verbose=verbose, export_fields=texture_fields)
        except Exception as exc:
            print(f"  [TEXT] Parse/export error: {exc}", file=sys.stderr)
    elif extract_textures:
        print("  [TEXT] chunk not found — skipping")

    # MAP: world tile-list, grid, OBJ marker geometry, and HTML viewer.
    if extract_map and "MAP " in by_tag:
        print("  [MAP ] Parsing level map …")
        try:
            parsed_map = parse_map_chunk(chunk_bytes(data, by_tag["MAP "]), verbose=verbose)
            export_map_outputs(parsed_map, out_dir / "map", verbose=verbose)
        except Exception as exc:
            print(f"  [MAP ] Parse/export error: {exc}", file=sys.stderr)
    elif extract_map:
        print("  [MAP ] chunk not found — skipping")

    # LGHT: light source CSV.
    if extract_lights and "LGHT" in by_tag:
        print("  [LGHT] Parsing lights …")
        try:
            lights = parse_lght_chunk(chunk_bytes(data, by_tag["LGHT"]))
            export_lights(lights, out_dir / "lights")
        except Exception as exc:
            print(f"  [LGHT] Parse/export error: {exc}", file=sys.stderr)

    # Raw exports: keep source bytes for chunks that are not fully decoded yet.
    if extract_raw:
        raw_dir = out_dir / "raw"
        for tag in RAW_EXPORTS:
            if tag in by_tag:
                chunk = by_tag[tag]
                path = export_raw_chunk(tag, chunk_bytes(data, chunk), raw_dir)
                print(f"  [{tag:4s}] → raw/{path.name} ({chunk.size:,} bytes)")

    # STPC: additionally unpack static meshes to OBJ using the importable library.
    if extract_stpc_obj and "STPC" in by_tag:
        print("  [STPC] Exporting static geometry OBJ meshes …")
        try:
            result = export_stpc_meshes_from_bytes(
                chunk_bytes(data, by_tag["STPC"]),
                out_dir / "stpc",
                alignment=stpc_alignment,
                min_score=stpc_min_score,
                scale=stpc_scale,
                flip_z=stpc_flip_z,
                write_debug=stpc_debug_faces,
                verbose=verbose,
            )
            print(f"  → stpc/ ({len(result.meshes)} meshes, manifest.csv, combined.obj)")
        except Exception as exc:
            print(f"  [STPC] OBJ export error: {exc}", file=sys.stderr)

    print(f"\n  Done — outputs in: {out_dir}\n")
    return True


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="wad_extractor",
        description="Extract and visualize Emperor's New Groove .WAD level files.",
    )
    parser.add_argument("inputs", nargs="+", metavar="INPUT", help=".wad file(s) or directory containing .wad files")
    parser.add_argument("--out-dir", "-o", default=None, metavar="DIR", help="root output directory")

    parser.add_argument("--no-tex", action="store_true", help="skip TEXT texture/palette extraction")
    parser.add_argument("--no-texture-fields", action="store_true", help="skip diagnostic palette-field images")
    parser.add_argument("--no-map", action="store_true", help="skip MAP parsing and map viewer exports")
    parser.add_argument("--no-stpc-obj", action="store_true", help="skip STPC OBJ mesh export")
    parser.add_argument("--no-lights", action="store_true", help="skip LGHT light CSV export")
    parser.add_argument("--no-raw", action="store_true", help="do not export raw undecoded chunks")
    parser.add_argument("--quiet", action="store_true", help="suppress per-record progress")

    parser.add_argument("--stpc-alignment", type=int, default=4, help="STPC scan alignment; use 1 for exhaustive scan")
    parser.add_argument("--stpc-min-score", type=float, default=0.85, help="minimum STPC mesh validation score")
    parser.add_argument("--stpc-scale", type=float, default=1.0, help="scale applied to STPC OBJ vertices")
    parser.add_argument("--stpc-flip-z", action="store_true", help="flip Z axis in STPC OBJ export")
    parser.add_argument("--stpc-debug-faces", action="store_true", help="write stpc/faces_debug.csv")

    args = parser.parse_args(argv)

    wad_files: list[Path] = []
    for inp in args.inputs:
        p = Path(inp)
        if p.is_dir():
            found = sorted(p.glob("*.wad")) + sorted(p.glob("*.WAD"))
            if not found:
                print(f"warning: no .wad files in {p}", file=sys.stderr)
            wad_files.extend(found)
        else:
            wad_files.append(p)

    if not wad_files:
        parser.error("no .wad files to process")

    root_out = Path(args.out_dir) if args.out_dir else None
    errors = 0
    for wad in wad_files:
        out = (root_out / wad.stem) if root_out else (wad.parent / "extracted" / wad.stem)
        ok = extract_wad(
            wad,
            out,
            extract_textures=not args.no_tex,
            extract_map=not args.no_map,
            extract_stpc_obj=not args.no_stpc_obj,
            extract_lights=not args.no_lights,
            extract_raw=not args.no_raw,
            texture_fields=not args.no_texture_fields,
            stpc_alignment=args.stpc_alignment,
            stpc_min_score=args.stpc_min_score,
            stpc_scale=args.stpc_scale,
            stpc_flip_z=args.stpc_flip_z,
            stpc_debug_faces=args.stpc_debug_faces,
            verbose=not args.quiet,
        )
        if not ok:
            errors += 1

    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
