"""
map_chunk.py — MAP chunk parser.

The MAP chunk is the main level-layout chunk.  It is not fully decoded yet, but
several important sections are useful and stable enough to export.

Confirmed / currently useful structure:

    +0x00  u32  tile_count
    +0x04  u32  grid_width   usually 96
    +0x08  u32  grid_height  usually 96

    +0x0C  tile_count records, 24 bytes each:
             f32 x           world-space X coordinate
             f32 y           world-space Y coordinate, likely height
             f32 z           world-space Z coordinate
             f32 unknown     possible radius/layer/height/unused field
             u32 flags       tile flags, not fully decoded
             u32 type_idx    tile type/material/lookup index, not fully decoded

    Later sections are partially understood:

        Section 2: count + count * u32
        Section 3: count + count * 90 bytes
        Section 4: count + count * 48 bytes
        Section 5: lookup/padding table, observed as either 256*8 or 32*8 bytes
        Section 6: grid_width * grid_height * u32 MAP grid
        Section 7: tile_count * 32-byte tile-definition-like records

Because several later MAP areas are still unknown, this parser is partial-safe:
if a later section does not fit, it returns all earlier data instead of raising
and losing the already parsed XYZ tile coordinates.
"""

from __future__ import annotations

from dataclasses import dataclass, field

from .binary import Reader


@dataclass
class MapTile:
    x: float
    y: float
    z: float
    unknown: float
    flags: int
    type_idx: int


@dataclass
class TileDef:
    v0: int
    v1: int
    v2: int
    v4: int
    v5: int
    v6: int


@dataclass
class MapChunk:
    tile_count: int
    grid_width: int
    grid_height: int
    tiles: list[MapTile] = field(default_factory=list)
    grid: list[list[int]] = field(default_factory=list)
    tile_defs: list[TileDef] = field(default_factory=list)
    parse_warnings: list[str] = field(default_factory=list)
    parse_stopped_at: int = 0


def parse_map_chunk(data: bytes, *, verbose: bool = True) -> MapChunk:
    """Parse MAP and return whatever sections can be read safely."""
    if len(data) < 12:
        raise ValueError(f"MAP chunk too small: {len(data)} bytes")

    r = Reader(data)
    warnings: list[str] = []

    def warn(msg: str) -> None:
        warnings.append(msg)
        if verbose:
            print(f"  [MAP ] warning: {msg}")

    tile_count = r.u32()
    grid_width = r.u32()
    grid_height = r.u32()

    result = MapChunk(tile_count=tile_count, grid_width=grid_width, grid_height=grid_height)

    def finish(reason: str | None = None) -> MapChunk:
        if reason:
            warn(reason)
        result.parse_warnings = warnings
        result.parse_stopped_at = r.pos
        return result

    def can_read(n: int) -> bool:
        return 0 <= n <= r.remaining()

    if tile_count > 1_000_000 or grid_width > 4096 or grid_height > 4096:
        return finish(f"suspicious header tile_count={tile_count}, grid={grid_width}x{grid_height}")

    # Tile list: this is the most important known MAP section for world viewing.
    for i in range(tile_count):
        if not can_read(24):
            return finish(f"tile list ended early at tile {i}/{tile_count}, offset=0x{r.pos:X}")
        result.tiles.append(MapTile(
            x=r.f32(),
            y=r.f32(),
            z=r.f32(),
            unknown=r.f32(),
            flags=r.u32(),
            type_idx=r.u32(),
        ))

    # Section 2: count + u32 list.
    if not can_read(4):
        return finish("no room for section2 count")
    s2_count = r.u32()
    if s2_count > 1_000_000 or not can_read(s2_count * 4):
        return finish(f"section2 does not fit: count={s2_count}, offset=0x{r.pos:X}, remaining={r.remaining()}")
    r.skip(s2_count * 4)

    # Section 3: observed 90-byte entries.  Contents are still unknown.
    if not can_read(4):
        return finish("no room for section3 count")
    s3_count = r.u32()
    s3_bytes = s3_count * 90
    if s3_count > 1_000_000 or not can_read(s3_bytes):
        return finish(f"section3 does not fit: count={s3_count}, bytes={s3_bytes}, offset=0x{r.pos:X}, remaining={r.remaining()}")
    r.skip(s3_bytes)

    # Section 4: observed 48-byte stride.  Older notes read only 34 known bytes;
    # skipping the full stride keeps the following grid aligned.
    if not can_read(4):
        return finish("no room for section4 count")
    s4_count = r.u32()
    s4_bytes = s4_count * 48
    if s4_count > 1_000_000 or not can_read(s4_bytes):
        return finish(f"section4 does not fit: count={s4_count}, bytes={s4_bytes}, offset=0x{r.pos:X}, remaining={r.remaining()}")
    r.skip(s4_bytes)

    # Section 5: unknown table/padding before the grid. Try known observed sizes.
    grid_bytes = grid_width * grid_height * 4
    chosen_s5 = None
    for s5_bytes in (256 * 8, 32 * 8, 0):
        if can_read(s5_bytes + grid_bytes):
            chosen_s5 = s5_bytes
            break
    if chosen_s5 is None:
        return finish(f"cannot locate grid after section4: need grid_bytes={grid_bytes}, offset=0x{r.pos:X}, remaining={r.remaining()}")
    r.skip(chosen_s5)

    # Section 6: raw grid. Values are not fully decoded; exporters try safe views.
    for row_i in range(grid_height):
        if not can_read(grid_width * 4):
            return finish(f"grid ended early at row {row_i}/{grid_height}, offset=0x{r.pos:X}")
        result.grid.append([r.u32() for _ in range(grid_width)])

    # Section 7: optional 32-byte tile definitions.  Currently raw fields only.
    for i in range(tile_count):
        if not can_read(32):
            warn(f"tile definitions ended early at {i}/{tile_count}, offset=0x{r.pos:X}")
            break
        v0 = r.u32(); v1 = r.u32(); v2 = r.u32()
        r.skip(4)
        v4 = r.u32(); v5 = r.u32(); v6 = r.u32()
        r.skip(8)
        result.tile_defs.append(TileDef(v0, v1, v2, v4, v5, v6))

    return finish()
