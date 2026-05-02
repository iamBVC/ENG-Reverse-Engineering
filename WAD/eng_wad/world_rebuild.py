"""
world_rebuild.py — experimental world reconstruction probe.

This module combines the parts of the WAD that are now structurally decoded:

    TRAK  -> terrain/world sector triangle geometry
    MAP   -> object placement records with confirmed 12.12 fixed-point XYZ
    STPC  -> mesh bank plus object-definition/script data

The important bridge is the MAP object field named stpc_object_def_offset in the
reverse-engineering notes.  At runtime the game converts it to:

    dword_6D9DBC + stpc_object_def_offset

where dword_6D9DBC is the raw STPC chunk base.  Many of those object-definition
records contain 32-bit values that match decoded STPC mesh-record offsets.

This exporter is deliberately conservative:

* It only instances STPC meshes when an exact little-endian u32 match to a
  decoded mesh-record offset is found inside the object's STPC definition scan
  window.
* It uses the confirmed MAP object XYZ as translation.
* It does NOT apply rotation or scale by default, because those fields are not
  fully proven yet.  Candidate angle/rotation fields are exported in CSV so they
  can be tested visually.

The output is meant to guide the next reverse-engineering step, not to claim a
perfect final world renderer.
"""

from __future__ import annotations

import csv
import json
import math
import shutil
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

from .map_full_chunk import MapFullExe, MapObjectRecord
from .stpc_chunk import MeshCandidate, STPCExportResult
from .trak_chunk import TrakFile, write_table_b_surfaces_obj


# ---------------------------------------------------------------------------
# Data structures
# ---------------------------------------------------------------------------

@dataclass
class WorldObjectInstance:
    """A MAP object placement converted to world units."""
    object_index: int
    stpc_def_offset: int
    world_x: float
    world_y: float
    world_z: float
    small_00: int
    small_04: int
    small_08: int
    field_16: int
    section2_index_or_sentinel: int
    field_1e: int
    field_22: int
    field_26_angle_candidate: int
    field_2a: int
    section4_index_or_sentinel: int
    field_32: int
    field_36: int
    field_38: int


@dataclass
class StpcMeshReferenceHit:
    """One exact mesh-offset reference found inside an STPC object definition."""
    object_index: int
    stpc_def_offset: int
    scan_start: int
    scan_end: int
    hit_file_offset: int
    hit_relative_offset: int
    mesh_index: int
    mesh_offset: int
    duplicate_index_for_object: int


@dataclass
class WorldRebuildResult:
    output_dir: Path
    object_instances: list[WorldObjectInstance]
    mesh_reference_hits: list[StpcMeshReferenceHit]
    unique_objects_with_hits: int
    unique_meshes_referenced: int
    combined_obj_path: Path | None
    terrain_obj_path: Path | None


# ---------------------------------------------------------------------------
# Small helpers
# ---------------------------------------------------------------------------

def _i32_from_u32(v: int) -> int:
    """Interpret an unsigned 32-bit integer as signed."""
    return struct.unpack("<i", struct.pack("<I", v & 0xFFFFFFFF))[0]


def _fixed12(v: int) -> float:
    """Convert the MAP object's confirmed 12.12 fixed-point coordinate."""
    return _i32_from_u32(v) / 4096.0


def _hex(v: int) -> str:
    return f"0x{v:08X}"


def _write_csv(path: Path, fieldnames: list[str], rows: Iterable[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for row in rows:
            w.writerow(row)


def _obj_vertex_line(x: float, y: float, z: float, *, scale: float, flip_z: bool) -> str:
    z2 = -z if flip_z else z
    return f"v {x * scale:.9g} {y * scale:.9g} {z2 * scale:.9g}\n"


def _obj_normal_line(nx: float, ny: float, nz: float, *, flip_z: bool) -> str:
    nz2 = -nz if flip_z else nz
    return f"vn {nx:.9g} {ny:.9g} {nz2:.9g}\n"


def _write_marker_cross_obj(path: Path, instances: list[WorldObjectInstance], hits_by_object: dict[int, list[StpcMeshReferenceHit]], *, scale: float, flip_z: bool) -> None:
    """Write small cross markers at every MAP object position."""
    if instances:
        xs = [o.world_x for o in instances]
        ys = [o.world_y for o in instances]
        zs = [o.world_z for o in instances]
        span = max(max(xs)-min(xs), max(ys)-min(ys), max(zs)-min(zs), 1.0)
    else:
        span = 1.0
    s = span * 0.005
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# Cross markers at confirmed MAP object XYZ positions.\n")
        f.write("# Objects with mesh-reference hits are named object_XXX_hits_N.\n")
        v = 1
        for o in instances:
            n_hits = len(hits_by_object.get(o.object_index, []))
            f.write(f"\no object_{o.object_index:03d}_hits_{n_hits}\n")
            pts = [
                (o.world_x-s, o.world_y, o.world_z), (o.world_x+s, o.world_y, o.world_z),
                (o.world_x, o.world_y-s, o.world_z), (o.world_x, o.world_y+s, o.world_z),
                (o.world_x, o.world_y, o.world_z-s), (o.world_x, o.world_y, o.world_z+s),
            ]
            for x, y, z in pts:
                f.write(_obj_vertex_line(x, y, z, scale=scale, flip_z=flip_z))
            f.write(f"l {v} {v+1}\n")
            f.write(f"l {v+2} {v+3}\n")
            f.write(f"l {v+4} {v+5}\n")
            v += 6


# ---------------------------------------------------------------------------
# Core extraction logic
# ---------------------------------------------------------------------------

def build_world_object_instances(mapx: MapFullExe) -> list[WorldObjectInstance]:
    """Convert MAP object records into confirmed world-position rows."""
    out: list[WorldObjectInstance] = []
    for o in mapx.objects:
        out.append(WorldObjectInstance(
            object_index=o.index,
            stpc_def_offset=o.name_or_string_offset,
            world_x=_fixed12(o.u32_16),
            world_y=_fixed12(o.u32_20),
            world_z=_fixed12(o.u32_24),
            small_00=o.small_00,
            small_04=o.small_04,
            small_08=o.small_08,
            field_16=o.u32_36,
            section2_index_or_sentinel=o.section2_index_or_sentinel,
            field_1e=o.u32_44,
            field_22=o.u32_48,
            field_26_angle_candidate=o.u32_52,
            field_2a=o.u32_56,
            section4_index_or_sentinel=o.section4_index_or_sentinel,
            field_32=o.u32_64,
            field_36=o.u16_68,
            field_38=o.u16_70,
        ))
    return out


def scan_stpc_definition_for_mesh_offsets(
    *,
    stpc_bytes: bytes,
    instances: list[WorldObjectInstance],
    meshes: list[MeshCandidate],
    scan_bytes: int = 2048,
    dedupe_per_object_mesh: bool = True,
) -> list[StpcMeshReferenceHit]:
    """Find exact u32 references to decoded STPC mesh-record offsets.

    The STPC object-definition format is still not fully decoded, so we do not
    parse opcodes yet.  We scan each object's definition window byte-by-byte for
    little-endian u32 values equal to one of the known mesh record offsets.  A
    byte-by-byte scan is intentional because object definitions are not always
    4-byte aligned.
    """
    mesh_by_offset = {m.offset: m for m in meshes}
    if not mesh_by_offset:
        return []

    hits: list[StpcMeshReferenceHit] = []
    for inst in instances:
        start = inst.stpc_def_offset
        if start < 0 or start >= len(stpc_bytes):
            continue
        end = min(len(stpc_bytes), start + max(0, scan_bytes))
        seen_meshes: set[int] = set()
        dup_index = 0
        # Need at least four bytes for a u32.
        for off in range(start, max(start, end - 3)):
            val = struct.unpack_from("<I", stpc_bytes, off)[0]
            mesh = mesh_by_offset.get(val)
            if mesh is None:
                continue
            if dedupe_per_object_mesh and mesh.index in seen_meshes:
                continue
            seen_meshes.add(mesh.index)
            hits.append(StpcMeshReferenceHit(
                object_index=inst.object_index,
                stpc_def_offset=inst.stpc_def_offset,
                scan_start=start,
                scan_end=end,
                hit_file_offset=off,
                hit_relative_offset=off - start,
                mesh_index=mesh.index,
                mesh_offset=mesh.offset,
                duplicate_index_for_object=dup_index,
            ))
            dup_index += 1
    return hits


# ---------------------------------------------------------------------------
# OBJ exporters
# ---------------------------------------------------------------------------

def _write_instanced_mesh_obj(
    f,
    mesh: MeshCandidate,
    inst: WorldObjectInstance,
    *,
    object_name: str,
    scale: float,
    flip_z: bool,
    vertex_base: int,
) -> int:
    """Append one translated STPC mesh instance to an open OBJ file."""
    f.write(f"\no {object_name}\n")
    f.write(f"# MAP object {inst.object_index}; STPC mesh {mesh.index}; mesh_offset=0x{mesh.offset:08X}\n")
    f.write(f"# translation={inst.world_x:.9g},{inst.world_y:.9g},{inst.world_z:.9g}; rotation/scale not applied yet\n")
    for v in mesh.vertices:
        f.write(_obj_vertex_line(inst.world_x + v.x, inst.world_y + v.y, inst.world_z + v.z, scale=scale, flip_z=flip_z))
    for v in mesh.vertices:
        f.write(_obj_normal_line(v.nx, v.ny, v.nz, flip_z=flip_z))
    current_mat: int | None = None
    for tri in mesh.triangles:
        if not (tri.i0 < mesh.vertex_count and tri.i1 < mesh.vertex_count and tri.i2 < mesh.vertex_count):
            continue
        if len({tri.i0, tri.i1, tri.i2}) != 3:
            continue
        if tri.material != current_mat:
            current_mat = tri.material
            f.write(f"usemtl stpc_mat_{current_mat:04d}\n")
        a = vertex_base + tri.i0
        b = vertex_base + tri.i1
        c = vertex_base + tri.i2
        f.write(f"f {a}//{a} {b}//{b} {c}//{c}\n")
    return vertex_base + mesh.vertex_count


def write_instanced_stpc_objs(
    *,
    out_dir: Path,
    instances: list[WorldObjectInstance],
    hits: list[StpcMeshReferenceHit],
    meshes: list[MeshCandidate],
    scale: float = 1.0,
    flip_z: bool = False,
    write_per_object: bool = True,
) -> Path | None:
    """Write combined and per-object STPC instance OBJ files."""
    if not hits:
        return None
    out_dir.mkdir(parents=True, exist_ok=True)
    by_object = {o.object_index: o for o in instances}
    by_mesh = {m.index: m for m in meshes}

    # Combined file: one object/group per MAP-object/mesh-hit pair.
    combined = out_dir / "stpc_instances_combined.obj"
    with combined.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib world.mtl\n")
        f.write("# Experimental: STPC meshes translated to confirmed MAP object XYZ.\n")
        f.write("# Rotation and scale are not applied yet. Validate visually.\n")
        vbase = 1
        for hit in hits:
            inst = by_object.get(hit.object_index)
            mesh = by_mesh.get(hit.mesh_index)
            if inst is None or mesh is None:
                continue
            name = f"object_{inst.object_index:03d}_mesh_{mesh.index:03d}_hit_{hit.duplicate_index_for_object}"
            vbase = _write_instanced_mesh_obj(f, mesh, inst, object_name=name, scale=scale, flip_z=flip_z, vertex_base=vbase)

    if write_per_object:
        per_dir = out_dir / "stpc_instances_by_object"
        per_dir.mkdir(parents=True, exist_ok=True)
        hits_by_object: dict[int, list[StpcMeshReferenceHit]] = {}
        for h in hits:
            hits_by_object.setdefault(h.object_index, []).append(h)
        for object_index, obj_hits in sorted(hits_by_object.items()):
            inst = by_object.get(object_index)
            if inst is None:
                continue
            path = per_dir / f"object_{object_index:03d}_stpc_instances.obj"
            with path.open("w", encoding="utf-8", newline="\n") as f:
                f.write("mtllib ../world.mtl\n")
                f.write(f"# Experimental STPC instances for MAP object {object_index}.\n")
                f.write(f"# position={inst.world_x:.9g},{inst.world_y:.9g},{inst.world_z:.9g}\n")
                vbase = 1
                for hit in obj_hits:
                    mesh = by_mesh.get(hit.mesh_index)
                    if mesh is None:
                        continue
                    name = f"object_{object_index:03d}_mesh_{mesh.index:03d}_hit_{hit.duplicate_index_for_object}"
                    vbase = _write_instanced_mesh_obj(f, mesh, inst, object_name=name, scale=scale, flip_z=flip_z, vertex_base=vbase)
    return combined


def write_world_combined_probe_obj(world_dir: Path, *, include_terrain: bool = True) -> Path | None:
    """Create a tiny OBJ wrapper that references terrain and instance geometry.

    OBJ cannot include other OBJ files, so this function concatenates the two
    generated OBJs when both exist.  It rewrites face indices while copying the
    second file to keep the combined OBJ valid.
    """
    terrain = world_dir / "terrain_trak.obj"
    inst = world_dir / "stpc_instances_combined.obj"
    if not inst.exists() and not terrain.exists():
        return None
    out = world_dir / "world_combined_probe.obj"

    vertex_offset = 0
    normal_offset = 0

    def copy_obj(src: Path, dst, *, add_offsets: bool) -> tuple[int, int]:
        nonlocal vertex_offset, normal_offset
        local_v = 0
        local_n = 0
        for line in src.read_text(encoding="utf-8", errors="replace").splitlines():
            if line.startswith("mtllib"):
                continue
            if line.startswith("v "):
                local_v += 1
                dst.write(line + "\n")
            elif line.startswith("vn "):
                local_n += 1
                dst.write(line + "\n")
            elif line.startswith("f ") and add_offsets:
                parts = line.split()[1:]
                new_parts = []
                for p in parts:
                    bits = p.split("/")
                    # Supports v//n emitted by our exporters.
                    vi = int(bits[0]) + vertex_offset
                    if len(bits) >= 3 and bits[2]:
                        ni = int(bits[2]) + normal_offset
                        new_parts.append(f"{vi}//{ni}")
                    else:
                        new_parts.append(str(vi))
                dst.write("f " + " ".join(new_parts) + "\n")
            else:
                dst.write(line + "\n")
        vertex_offset += local_v
        normal_offset += local_n
        return local_v, local_n

    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib world.mtl\n")
        f.write("# Combined experimental world probe: TRAK terrain + translated STPC candidates.\n")
        if include_terrain and terrain.exists():
            f.write("\no terrain_trak\n")
            copy_obj(terrain, f, add_offsets=True)
        if inst.exists():
            f.write("\n# --- STPC translated candidate instances ---\n")
            copy_obj(inst, f, add_offsets=True)
    return out


def write_world_mtl(path: Path) -> None:
    """Write simple placeholder materials for world probe OBJs."""
    with path.open("w", encoding="utf-8") as f:
        f.write("# Placeholder materials for experimental WAD world reconstruction.\n")
        f.write("newmtl trak_surface\nKd 0.55 0.55 0.55\nKa 0 0 0\n\n")
        f.write("newmtl stpc_mat_default\nKd 0.75 0.75 0.75\nKa 0 0 0\n\n")
        # A broad set is enough for most material ids without bloating too much.
        for i in range(512):
            shade = 0.25 + ((i * 37) % 100) / 160.0
            f.write(f"newmtl stpc_mat_{i:04d}\nKd {shade:.3f} {min(1.0, shade+0.12):.3f} {max(0.0, shade-0.08):.3f}\nKa 0 0 0\n\n")


# ---------------------------------------------------------------------------
# HTML viewer
# ---------------------------------------------------------------------------

def write_world_viewer_html(path: Path, instances: list[WorldObjectInstance], hits: list[StpcMeshReferenceHit], meshes: list[MeshCandidate]) -> None:
    """Write a lightweight object-placement viewer.

    It previews MAP object positions and highlights those for which an STPC mesh
    reference was found.  It intentionally does not embed all mesh triangles;
    the OBJ files are the authoritative geometry exports.
    """
    hit_count_by_object: dict[int, int] = {}
    mesh_ids_by_object: dict[int, list[int]] = {}
    for h in hits:
        hit_count_by_object[h.object_index] = hit_count_by_object.get(h.object_index, 0) + 1
        mesh_ids_by_object.setdefault(h.object_index, []).append(h.mesh_index)

    points = []
    for o in instances:
        points.append({
            "i": o.object_index,
            "x": o.world_x,
            "y": o.world_y,
            "z": o.world_z,
            "def": o.stpc_def_offset,
            "hits": hit_count_by_object.get(o.object_index, 0),
            "meshes": sorted(set(mesh_ids_by_object.get(o.object_index, []))),
            "angle": o.field_26_angle_candidate,
            "s2": o.section2_index_or_sentinel,
            "s4": o.section4_index_or_sentinel,
        })
    payload = json.dumps({"objects": points, "mesh_count": len(meshes)}, separators=(",", ":"))
    html = f"""<!doctype html>
<html><head><meta charset=\"utf-8\"><title>WAD World Rebuild Probe</title>
<style>
body{{margin:0;background:#111;color:#ddd;font-family:system-ui,Segoe UI,sans-serif;overflow:hidden}}
#bar{{position:fixed;left:0;right:0;top:0;background:#1d1d1d;padding:8px 10px;display:flex;gap:10px;align-items:center;z-index:2;box-shadow:0 2px 8px #0008}}
button,select,input{{background:#2b2b2b;color:#eee;border:1px solid #555;border-radius:6px;padding:4px 8px}}
#tip{{position:fixed;pointer-events:none;background:#000d;border:1px solid #777;border-radius:6px;padding:7px 9px;display:none;white-space:pre;font:12px ui-monospace,monospace}}
canvas{{display:block;width:100vw;height:100vh}}
.small{{font-size:12px;color:#aaa}}
</style></head><body>
<div id=\"bar\">
  <b>World rebuild probe</b>
  <label>View <select id=\"view\"><option value=\"top\">top X/Z</option><option value=\"iso\">isometric</option></select></label>
  <label><input id=\"hitsOnly\" type=\"checkbox\"> only objects with STPC mesh hits</label>
  <label>min hits <input id=\"minHits\" type=\"range\" min=\"0\" max=\"8\" value=\"0\"></label><span id=\"minHitsText\">0</span>
  <button id=\"fit\">fit</button>
  <span class=\"small\">Drag to pan, wheel to zoom. Orange = object has mesh reference hit.</span>
</div>
<canvas id=\"c\"></canvas><div id=\"tip\"></div>
<script>
const data = {payload};
const c = document.getElementById('c'), ctx = c.getContext('2d'), tip = document.getElementById('tip');
const viewSel = document.getElementById('view'), hitsOnly = document.getElementById('hitsOnly'), minHits = document.getElementById('minHits'), minHitsText = document.getElementById('minHitsText');
let W=0,H=0, zoom=1, panX=0, panY=0, dragging=false, lx=0, ly=0, hover=null;
function resize(){{ W=c.width=innerWidth*devicePixelRatio; H=c.height=innerHeight*devicePixelRatio; draw(); }}
addEventListener('resize', resize);
function project(p){{
  if(viewSel.value==='iso'){{ const x=(p.x-p.z)*0.7071, y=(p.x+p.z)*0.35-p.y; return [x,y]; }}
  return [p.x,p.z];
}}
function filtered(){{ const mh=+minHits.value; return data.objects.filter(p => (!hitsOnly.checked || p.hits>0) && p.hits>=mh); }}
function fit(){{ const pts=filtered(); if(!pts.length) return; let xs=[],ys=[]; for(const p of pts){{ const q=project(p); xs.push(q[0]); ys.push(q[1]); }}
  const minX=Math.min(...xs),maxX=Math.max(...xs),minY=Math.min(...ys),maxY=Math.max(...ys); const sx=W/Math.max(1,maxX-minX), sy=(H-60*devicePixelRatio)/Math.max(1,maxY-minY); zoom=Math.min(sx,sy)*0.82; panX=W/2-(minX+maxX)/2*zoom; panY=H/2-(minY+maxY)/2*zoom+25*devicePixelRatio; draw(); }}
function screen(p){{ const q=project(p); return [q[0]*zoom+panX, q[1]*zoom+panY]; }}
function draw(){{ ctx.clearRect(0,0,W,H); ctx.fillStyle='#111'; ctx.fillRect(0,0,W,H); const pts=filtered(); hover=null; const mx=lastMouseX??-9999,my=lastMouseY??-9999;
  for(const p of pts){{ const [x,y]=screen(p); const r=(p.hits?5:3)*devicePixelRatio; ctx.beginPath(); ctx.arc(x,y,r,0,Math.PI*2); ctx.fillStyle=p.hits?'#ffb14a':'#6aa6ff'; ctx.fill(); ctx.strokeStyle='#000'; ctx.stroke(); if(Math.hypot(x-mx,y-my)<r+5*devicePixelRatio) hover=p; }}
  ctx.fillStyle='#ccc'; ctx.font=(12*devicePixelRatio)+'px system-ui'; ctx.fillText(`${{pts.length}} / ${{data.objects.length}} objects shown; STPC mesh bank: ${{data.mesh_count}} meshes`, 12*devicePixelRatio, H-14*devicePixelRatio);
  if(hover){{ tip.style.display='block'; tip.textContent=`object ${{hover.i}}\nxyz: ${{hover.x.toFixed(3)}}, ${{hover.y.toFixed(3)}}, ${{hover.z.toFixed(3)}}\nstpc def: 0x${{hover.def.toString(16)}}\nmesh hits: ${{hover.hits}} [${{hover.meshes.join(', ')}}]\nangle candidate: 0x${{hover.angle.toString(16)}}\nsection2: ${{hover.s2}}\nsection4: ${{hover.s4}}`; }} else tip.style.display='none'; }}
let lastMouseX=null,lastMouseY=null;
c.addEventListener('mousedown',e=>{{dragging=true;lx=e.clientX*devicePixelRatio;ly=e.clientY*devicePixelRatio;}});
addEventListener('mouseup',()=>dragging=false);
c.addEventListener('mousemove',e=>{{ const x=e.clientX*devicePixelRatio,y=e.clientY*devicePixelRatio; lastMouseX=x; lastMouseY=y; if(dragging){{panX+=x-lx; panY+=y-ly; lx=x; ly=y;}} tip.style.left=(e.clientX+14)+'px'; tip.style.top=(e.clientY+14)+'px'; draw(); }});
c.addEventListener('wheel',e=>{{e.preventDefault(); const k=e.deltaY<0?1.12:0.89; const mx=e.clientX*devicePixelRatio,my=e.clientY*devicePixelRatio; panX=mx+(panX-mx)*k; panY=my+(panY-my)*k; zoom*=k; draw();}},{{passive:false}});
for(const el of [viewSel,hitsOnly,minHits]) el.addEventListener('input',()=>{{minHitsText.textContent=minHits.value; fit();}});
document.getElementById('fit').onclick=fit; resize(); fit();
</script></body></html>"""
    path.write_text(html, encoding="utf-8")


# ---------------------------------------------------------------------------
# Public export API
# ---------------------------------------------------------------------------

def export_world_rebuild_probe(
    *,
    out_dir: Path,
    mapx: MapFullExe,
    trak: TrakFile,
    stpc_bytes: bytes,
    stpc_result: STPCExportResult,
    scan_bytes: int = 2048,
    scale: float = 1.0,
    flip_z: bool = False,
    write_terrain: bool = True,
    write_per_object: bool = True,
) -> WorldRebuildResult:
    """Export a first-pass reconstructed world probe into `out_dir`.

    The result combines confirmed terrain geometry with candidate STPC object
    instances.  Treat STPC instance placement as experimental until rotation,
    scale, and the full STPC object-definition language are decoded.
    """
    out_dir.mkdir(parents=True, exist_ok=True)
    write_world_mtl(out_dir / "world.mtl")

    instances = build_world_object_instances(mapx)
    hits = scan_stpc_definition_for_mesh_offsets(
        stpc_bytes=stpc_bytes,
        instances=instances,
        meshes=stpc_result.meshes,
        scan_bytes=scan_bytes,
        dedupe_per_object_mesh=True,
    )
    hits_by_object: dict[int, list[StpcMeshReferenceHit]] = {}
    for h in hits:
        hits_by_object.setdefault(h.object_index, []).append(h)

    terrain_obj: Path | None = None
    if write_terrain:
        terrain_obj = out_dir / "terrain_trak.obj"
        write_table_b_surfaces_obj(trak, terrain_obj, scale=scale, flip_z=flip_z)

    _write_marker_cross_obj(out_dir / "map_object_markers.obj", instances, hits_by_object, scale=scale, flip_z=flip_z)

    combined_obj = write_instanced_stpc_objs(
        out_dir=out_dir,
        instances=instances,
        hits=hits,
        meshes=stpc_result.meshes,
        scale=scale,
        flip_z=flip_z,
        write_per_object=write_per_object,
    )
    world_combined = write_world_combined_probe_obj(out_dir)

    # CSV: all MAP object placements.
    _write_csv(out_dir / "map_object_instances.csv", [
        "object_index","stpc_def_offset","stpc_def_offset_hex","world_x","world_y","world_z",
        "mesh_hit_count","mesh_indices","small_00","small_04","small_08","field_16",
        "section2_index_or_sentinel","field_1e","field_22","field_26_angle_candidate",
        "field_26_hex","field_2a","section4_index_or_sentinel","field_32","field_36","field_38",
    ], (
        {
            "object_index": o.object_index,
            "stpc_def_offset": o.stpc_def_offset,
            "stpc_def_offset_hex": _hex(o.stpc_def_offset),
            "world_x": o.world_x,
            "world_y": o.world_y,
            "world_z": o.world_z,
            "mesh_hit_count": len(hits_by_object.get(o.object_index, [])),
            "mesh_indices": " ".join(str(h.mesh_index) for h in hits_by_object.get(o.object_index, [])),
            "small_00": o.small_00,
            "small_04": o.small_04,
            "small_08": o.small_08,
            "field_16": o.field_16,
            "section2_index_or_sentinel": o.section2_index_or_sentinel,
            "field_1e": o.field_1e,
            "field_22": o.field_22,
            "field_26_angle_candidate": o.field_26_angle_candidate,
            "field_26_hex": _hex(o.field_26_angle_candidate),
            "field_2a": o.field_2a,
            "section4_index_or_sentinel": o.section4_index_or_sentinel,
            "field_32": o.field_32,
            "field_36": o.field_36,
            "field_38": o.field_38,
        } for o in instances
    ))

    # CSV: one row per exact mesh-offset hit found in an object definition.
    _write_csv(out_dir / "stpc_mesh_reference_hits.csv", [
        "object_index","stpc_def_offset","stpc_def_offset_hex","scan_start","scan_end",
        "hit_file_offset","hit_relative_offset","mesh_index","mesh_offset","mesh_offset_hex",
        "duplicate_index_for_object",
    ], (
        {
            "object_index": h.object_index,
            "stpc_def_offset": h.stpc_def_offset,
            "stpc_def_offset_hex": _hex(h.stpc_def_offset),
            "scan_start": h.scan_start,
            "scan_end": h.scan_end,
            "hit_file_offset": h.hit_file_offset,
            "hit_relative_offset": h.hit_relative_offset,
            "mesh_index": h.mesh_index,
            "mesh_offset": h.mesh_offset,
            "mesh_offset_hex": _hex(h.mesh_offset),
            "duplicate_index_for_object": h.duplicate_index_for_object,
        } for h in hits
    ))

    # CSV: unique object definitions observed from MAP objects.
    defs: dict[int, dict] = {}
    for o in instances:
        d = defs.setdefault(o.stpc_def_offset, {"count": 0, "objects": []})
        d["count"] += 1
        d["objects"].append(o.object_index)
    _write_csv(out_dir / "stpc_object_defs.csv", [
        "stpc_def_offset","stpc_def_offset_hex","object_count","object_indices","in_stpc_range","first_32_bytes_hex",
    ], (
        {
            "stpc_def_offset": off,
            "stpc_def_offset_hex": _hex(off),
            "object_count": info["count"],
            "object_indices": " ".join(str(i) for i in info["objects"]),
            "in_stpc_range": 0 <= off < len(stpc_bytes),
            "first_32_bytes_hex": stpc_bytes[off:min(len(stpc_bytes), off+32)].hex(" ") if 0 <= off < len(stpc_bytes) else "",
        } for off, info in sorted(defs.items())
    ))

    write_world_viewer_html(out_dir / "world_viewer.html", instances, hits, stpc_result.meshes)

    summary = {
        "map_object_count": len(instances),
        "stpc_mesh_count": len(stpc_result.meshes),
        "scan_bytes_per_object_definition": scan_bytes,
        "mesh_reference_hit_count": len(hits),
        "objects_with_mesh_hits": len({h.object_index for h in hits}),
        "unique_meshes_referenced": len({h.mesh_index for h in hits}),
        "terrain_obj": str(terrain_obj.name) if terrain_obj else None,
        "stpc_instances_combined_obj": str(combined_obj.name) if combined_obj else None,
        "world_combined_probe_obj": str(world_combined.name) if world_combined else None,
        "important_note": "STPC instances are translated to confirmed MAP object XYZ. Rotation/scale are not applied yet.",
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "summary.txt").write_text("\n".join(f"{k}: {v}" for k, v in summary.items()) + "\n", encoding="utf-8")

    return WorldRebuildResult(
        output_dir=out_dir,
        object_instances=instances,
        mesh_reference_hits=hits,
        unique_objects_with_hits=summary["objects_with_mesh_hits"],
        unique_meshes_referenced=summary["unique_meshes_referenced"],
        combined_obj_path=combined_obj,
        terrain_obj_path=terrain_obj,
    )
