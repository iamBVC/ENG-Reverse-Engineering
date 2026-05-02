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
from eng_wad.instance_hunter import export_instance_hunt
from eng_wad.map_chunk import parse_map_chunk
from eng_wad.map_full_chunk import export_map_full_exe, parse_map_full_exe
from eng_wad.map_export import export_map_outputs
from eng_wad.material_chunk import export_material_diagnostics
from eng_wad.raw_export import RAW_EXPORTS, export_raw_chunk
from eng_wad.stpc_chunk import export_stpc_meshes_from_bytes
from eng_wad.text_chunk import export_textures, parse_text_chunk
from eng_wad.trak_chunk import export_trak_from_bytes
from eng_wad.world_rebuild import export_world
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
    extract_trak: bool = True,
    extract_lights: bool = True,
    extract_raw: bool = True,
    extract_world_probe: bool = False,
    extract_map_full: bool = True,
    extract_world: bool = True,
    texture_fields: bool = True,
    stpc_alignment: int = 4,
    stpc_min_score: float = 0.85,
    stpc_scale: float = 1.0,
    stpc_flip_z: bool = False,
    stpc_debug_faces: bool = False,
    trak_scale: float = 1.0,
    trak_flip_z: bool = False,
    world_def_scan_bytes: int = 2048,
    world_scale: float = 1.0,
    world_flip_z: bool = False,
    world_terrain_yaw_sign: int = 1,
    world_mirror_terrain_z: bool = True,
    world_stpc_object_z_sign: int = -1,
    world_stpc_local_z_sign: int = -1,
    world_apply_stpc_yaw: bool = True,
    world_stpc_yaw_sign: int = 1,
    world_object_x_offset: float = 0.0,
    world_object_y_offset: float = 0.0,
    world_object_z_offset: float = 1.5,
    world_terrain_uv_variant: str = "default",
    world_write_terrain_uv_variants: bool = True,
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

    parsed_map = None
    map_bytes_for_probe = None
    trak_result = None
    stpc_result = None
    mapx = None
    stpc_bytes_for_world = None
    text_chunk_for_materials = None

    info_lines = chunk_manifest_lines(wad_path, data, chunks)
    _write_level_metadata(data, by_tag, out_dir, info_lines)
    (out_dir / "info.txt").write_text("\n".join(info_lines) + "\n", encoding="utf-8")
    print("  → info.txt")

    # TEXT: textures and palette/control-map diagnostics.
    if extract_textures and "TEXT" in by_tag:
        print("  [TEXT] Parsing textures/palette …")
        try:
            text = parse_text_chunk(chunk_bytes(data, by_tag["TEXT"]))
            text_chunk_for_materials = text
            export_textures(text, out_dir, verbose=verbose, export_fields=texture_fields)
        except Exception as exc:
            print(f"  [TEXT] Parse/export error: {exc}", file=sys.stderr)
    elif extract_textures:
        print("  [TEXT] chunk not found — skipping")

    # MAP: world tile-list, grid, OBJ marker geometry, and HTML viewer.
    if extract_map and "MAP " in by_tag:
        print("  [MAP ] Parsing level map …")
        try:
            map_bytes_for_probe = chunk_bytes(data, by_tag["MAP "])
            parsed_map = parse_map_chunk(map_bytes_for_probe, verbose=verbose)
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

    # TRAK: track/navigation/collision-like sector data.
    # The raw TRAK chunk is still preserved in raw/trak.bin when raw export is enabled.
    # This decoded export writes the confirmed record table, Table A vertices,
    # Table B triangle/plane records, raw Table C/D/E rows, diagnostic OBJ files,
    # and an HTML viewer into the dedicated trak/ folder.
    if extract_trak and "TRAK" in by_tag:
        print("  [TRAK] Parsing track/spatial sector data …")
        try:
            trak_result = export_trak_from_bytes(
                chunk_bytes(data, by_tag["TRAK"]),
                out_dir / "trak",
                scale=trak_scale,
                flip_z=trak_flip_z,
            )
            trak = trak_result.trak
            print(
                f"  → trak/ ({trak.record_count} records, "
                f"A={trak.total_a_entries:,}, B={trak.total_b_entries:,}, "
                f"C/D/E={trak.total_c_entries:,}/{trak.total_d_entries:,}/{trak.total_e_entries:,})"
            )
        except Exception as exc:
            print(f"  [TRAK] Parse/export error: {exc}", file=sys.stderr)
    elif extract_trak:
        print("  [TRAK] chunk not found — skipping")

    # MAP_FULL: executable-confirmed MAP parser. This needs TRAK because MAP
    # stores per-tile vertex colors sized from the referenced TRAK record's
    # Table A vertex count. It writes corrected MAP diagnostics into map_full/.
    if extract_map_full:
        if map_bytes_for_probe is not None and trak_result is not None:
            print("  [MAPX] Parsing executable-confirmed MAP structure …")
            try:
                mapx = parse_map_full_exe(map_bytes_for_probe, trak_result.trak)
                export_map_full_exe(mapx, out_dir / "map_full")
                print(
                    f"  → map_full/ ({mapx.tile_count} tiles, "
                    f"objects={len(mapx.objects)}, colors={sum(c.byte_size + c.extra_byte_size for c in mapx.colors):,} bytes)"
                )
            except Exception as exc:
                print(f"  [MAPX] Parse/export error: {exc}", file=sys.stderr)
        elif verbose:
            print("  [MAPX] skipped — needs both MAP and TRAK")

    # STPC: additionally unpack static meshes to OBJ using the importable library.
    if extract_stpc_obj and "STPC" in by_tag:
        print("  [STPC] Exporting static geometry OBJ meshes …")
        try:
            stpc_bytes_for_world = chunk_bytes(data, by_tag["STPC"])
            stpc_result = export_stpc_meshes_from_bytes(
                stpc_bytes_for_world,
                out_dir / "stpc",
                alignment=stpc_alignment,
                min_score=stpc_min_score,
                scale=stpc_scale,
                flip_z=stpc_flip_z,
                write_debug=stpc_debug_faces,
                verbose=verbose,
            )
            print(f"  → stpc/ ({len(stpc_result.meshes)} meshes, manifest.csv, combined.obj)")
        except Exception as exc:
            print(f"  [STPC] OBJ export error: {exc}", file=sys.stderr)


    # MATERIALS: executable-informed TEXT trailing table export.  This decodes
    # dword_581154-style 20-byte material rows and cross-references TRAK/STPC
    # material usage.
    if text_chunk_for_materials is not None:
        print("  [MAT ] Exporting material/UV diagnostics …")
        try:
            export_material_diagnostics(
                text=text_chunk_for_materials,
                out_dir=out_dir / "materials",
                trak=trak_result.trak if trak_result is not None else None,
                stpc_result=stpc_result,
            )
            print("  → materials/ (runtime material table + terrain/STPC usage)")
        except Exception as exc:
            print(f"  [MAT ] Material export error: {exc}", file=sys.stderr)


    # WORLD REBUILD: experimental reconstruction using confirmed MAP object XYZ
    # and exact STPC mesh-offset references found inside STPC object definitions.
    if extract_world:
        if mapx is not None and trak_result is not None and stpc_result is not None and stpc_bytes_for_world is not None:
            print("  [WRLD] Exporting reconstructed TRAK + STPC world …")
            try:
                world = export_world(
                    out_dir=out_dir / "world",
                    mapx=mapx,
                    trak=trak_result.trak,
                    stpc_bytes=stpc_bytes_for_world,
                    stpc_result=stpc_result,
                    text_chunk=text_chunk_for_materials,
                    scan_bytes=world_def_scan_bytes,
                    scale=world_scale,
                    flip_z=world_flip_z,
                    terrain_yaw_sign=world_terrain_yaw_sign,
                    mirror_terrain_z=world_mirror_terrain_z,
                    stpc_object_z_sign=world_stpc_object_z_sign,
                    stpc_local_z_sign=world_stpc_local_z_sign,
                    apply_stpc_object_yaw=world_apply_stpc_yaw,
                    stpc_object_yaw_sign=world_stpc_yaw_sign,
                    object_x_offset=world_object_x_offset,
                    object_y_offset=world_object_y_offset,
                    object_z_offset=world_object_z_offset,
                    world_terrain_uv_variant=world_terrain_uv_variant,
                    write_terrain_uv_variants=world_write_terrain_uv_variants,
                )
                print(
                    f"  → world/ ({len(world.object_instances)} MAP objects, "
                    f"{len(world.mesh_reference_hits)} STPC mesh-reference hits, "
                    f"objects_with_hits={world.unique_objects_with_hits})"
                )
            except Exception as exc:
                print(f"  [WRLD] World rebuild export error: {exc}", file=sys.stderr)
        elif verbose:
            missing = []
            if mapx is None:
                missing.append("MAP_FULL")
            if trak_result is None:
                missing.append("TRAK")
            if stpc_result is None or stpc_bytes_for_world is None:
                missing.append("STPC")
            print(f"  [WRLD] skipped — missing {', '.join(missing)}")


    # WORLD PROBE: exploratory search for STPC placement/instance tables.
    # This is intentionally diagnostic and conservative. It exports MAP Section 4
    # as raw numeric fields and produces candidate mesh-id + XYZ combinations that
    # can be compared against TRAK terrain and in-game object locations.
    if extract_world_probe:
        if map_bytes_for_probe is not None and parsed_map is not None and stpc_result is not None:
            print("  [WRLD] Exporting instance-hunting diagnostics …")
            try:
                probe = export_instance_hunt(
                    out_dir=out_dir / "world_probe",
                    map_bytes=map_bytes_for_probe,
                    parsed_map=parsed_map,
                    trak=trak_result.trak if trak_result else None,
                    stpc_result=stpc_result,
                )
                print(f"  → world_probe/ ({len(probe.candidates):,} MAP Section 4 candidates)")
            except Exception as exc:
                print(f"  [WRLD] Probe export error: {exc}", file=sys.stderr)
        elif verbose:
            missing = []
            if map_bytes_for_probe is None or parsed_map is None:
                missing.append("MAP")
            if stpc_result is None:
                missing.append("STPC")
            print(f"  [WRLD] skipped — missing {', '.join(missing)}")

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
    parser.add_argument("--no-trak", action="store_true", help="skip TRAK CSV/OBJ/viewer export")
    parser.add_argument("--no-lights", action="store_true", help="skip LGHT light CSV export")
    parser.add_argument("--no-raw", action="store_true", help="do not export raw undecoded chunks")
    parser.add_argument("--world-probe", action="store_true", help="also run the older Section-4 instance-hunting diagnostics (deprecated)")
    parser.add_argument("--no-map-full", action="store_true", help="skip executable-confirmed MAP full diagnostics")
    parser.add_argument("--no-world", action="store_true", help="skip reconstructed TRAK + MAP-object + STPC world export")
    parser.add_argument("--no-world-rebuild", action="store_true", help=argparse.SUPPRESS)
    parser.add_argument("--quiet", action="store_true", help="suppress per-record progress")

    parser.add_argument("--stpc-alignment", type=int, default=4, help="STPC scan alignment; use 1 for exhaustive scan")
    parser.add_argument("--stpc-min-score", type=float, default=0.85, help="minimum STPC mesh validation score")
    parser.add_argument("--stpc-scale", type=float, default=1.0, help="scale applied to STPC OBJ vertices")
    parser.add_argument("--stpc-flip-z", action="store_true", help="flip Z axis in STPC OBJ export")
    parser.add_argument("--stpc-debug-faces", action="store_true", help="write stpc/faces_debug.csv")

    parser.add_argument("--trak-scale", type=float, default=1.0, help="scale applied to TRAK OBJ vertices")
    parser.add_argument("--trak-flip-z", action="store_true", help="flip Z axis in TRAK OBJ export")

    parser.add_argument("--world-def-scan-bytes", type=int, default=2048, help="bytes to scan from each MAP object STPC-definition offset for mesh references")
    parser.add_argument("--world-scale", type=float, default=1.0, help="scale applied to world/ OBJ exports")
    parser.add_argument("--world-flip-z", action="store_true", help="flip final Z axis in all world/ OBJ exports after per-source conversion")
    parser.add_argument("--world-terrain-yaw-sign", type=int, choices=(-1, 1), default=1, help="sign used when applying MAP tile yaw to TRAK terrain")
    parser.add_argument("--world-no-terrain-z-mirror", action="store_true", help="disable the default centered Z mirror applied to TRAK terrain")
    parser.add_argument("--world-stpc-object-z-sign", type=int, choices=(-1, 1), default=-1, help="Z sign applied to MAP object positions when exporting STPC instances; -1 aligns object Z with TRAK terrain")
    parser.add_argument("--world-stpc-local-z-sign", type=int, choices=(-1, 1), default=-1, help="Z sign applied to local STPC mesh vertices before object yaw/translation")
    parser.add_argument("--world-no-stpc-yaw", action="store_true", help="do not apply experimental MAP object yaw from small_04 to STPC instances")
    parser.add_argument("--world-stpc-yaw-sign", type=int, choices=(-1, 1), default=1, help="sign used when applying experimental MAP object yaw to STPC instances")
    parser.add_argument("--world-object-x-offset", type=float, default=0.0, help="final world-space X offset applied only to STPC object instances after all conversion/mirroring")
    parser.add_argument("--world-object-y-offset", type=float, default=0.0, help="final world-space Y offset applied only to STPC object instances after all conversion/mirroring")
    parser.add_argument("--world-object-z-offset", type=float, default=1.5, help="final world-space Z offset applied only to STPC object instances after all conversion/mirroring; default 1.5 is the visually validated object/terrain alignment correction")
    parser.add_argument("--world-terrain-uv-variant", choices=("default", "flip_u", "flip_v", "flip_uv", "rot90_cw", "rot90_ccw", "rot180", "diag_alt"), default="default", help="UV corner-order variant used for world/terrain_textured_probe.obj")
    parser.add_argument("--no-world-terrain-uv-variants", action="store_true", help="skip writing world/terrain_uv_variants/ textured OBJ comparison set")

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
            extract_trak=not args.no_trak,
            extract_lights=not args.no_lights,
            extract_raw=not args.no_raw,
            extract_world_probe=args.world_probe,
            extract_map_full=not args.no_map_full,
            extract_world=not (args.no_world or args.no_world_rebuild),
            texture_fields=not args.no_texture_fields,
            stpc_alignment=args.stpc_alignment,
            stpc_min_score=args.stpc_min_score,
            stpc_scale=args.stpc_scale,
            stpc_flip_z=args.stpc_flip_z,
            stpc_debug_faces=args.stpc_debug_faces,
            trak_scale=args.trak_scale,
            trak_flip_z=args.trak_flip_z,
            world_def_scan_bytes=args.world_def_scan_bytes,
            world_scale=args.world_scale,
            world_flip_z=args.world_flip_z,
            world_terrain_yaw_sign=args.world_terrain_yaw_sign,
            world_mirror_terrain_z=not args.world_no_terrain_z_mirror,
            world_stpc_object_z_sign=args.world_stpc_object_z_sign,
            world_stpc_local_z_sign=args.world_stpc_local_z_sign,
            world_apply_stpc_yaw=not args.world_no_stpc_yaw,
            world_stpc_yaw_sign=args.world_stpc_yaw_sign,
            world_object_x_offset=args.world_object_x_offset,
            world_object_y_offset=args.world_object_y_offset,
            world_object_z_offset=args.world_object_z_offset,
            world_terrain_uv_variant=args.world_terrain_uv_variant,
            world_write_terrain_uv_variants=not args.no_world_terrain_uv_variants,
            verbose=not args.quiet,
        )
        if not ok:
            errors += 1

    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
