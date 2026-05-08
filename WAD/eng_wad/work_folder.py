"""work_folder.py — WAD work-folder: extract every chunk to per-bin files + manifest.

WorkFolder keeps a mirror of a WAD on disk so individual chunks can be edited
externally and repacked.  It is intentionally data-format agnostic; any tool
that opens WAD files can reuse it.
"""

from __future__ import annotations

import json
import struct
from pathlib import Path

from .wad import WadChunk

# Suffix appended to the WAD stem for the work directory (e.g. "t1l1m001_wadedit")
WORK_SUFFIX = "_wadedit"


class WorkFolder:
    """Manages a temp directory that mirrors a WAD's chunks as individual .bin files.

    Workflow:
        wf = WorkFolder(path)
        wf.extract(wad_data, chunks)   # first open
        wf.load()                      # subsequent opens (reads manifest)
        wf.get_chunk_data("MAP ")      # read a chunk
        wf.save_chunk_data("MAP ", …)  # write a modified chunk
        wf.pack_wad(out_path)          # reassemble modified WAD
    """

    def __init__(self, wad_path: Path) -> None:
        self.wad_path      = wad_path
        self.work_dir      = wad_path.parent / (wad_path.stem + WORK_SUFFIX)
        self.manifest_path = self.work_dir / "manifest.json"
        self.entries: list[dict] = []

    # ── extraction ────────────────────────────────────────────────────────────

    def extract(self, wad_data: bytes, chunks: list[WadChunk]) -> None:
        """Dump each chunk to a numbered .bin and write manifest.json."""
        self.work_dir.mkdir(parents=True, exist_ok=True)
        self.entries = []
        for i, chunk in enumerate(chunks):
            safe = "".join(c if (c.isalnum() or c in "_-") else "_"
                           for c in chunk.tag).strip("_") or "UNK"
            bin_name = f"chunk_{i:03d}_{safe}.bin"
            (self.work_dir / bin_name).write_bytes(
                wad_data[chunk.offset: chunk.offset + chunk.size])
            self.entries.append({
                "index": i, "tag": chunk.tag,
                "original_offset": chunk.offset, "original_size": chunk.size,
                "bin_file": bin_name,
            })
        self._save_manifest()

    def _save_manifest(self) -> None:
        self.manifest_path.write_text(
            json.dumps({"wad_source": str(self.wad_path), "chunks": self.entries},
                       indent=2),
            encoding="utf-8")

    # ── loading ───────────────────────────────────────────────────────────────

    def load(self) -> bool:
        """Reload entries from an existing manifest.json; return True on success."""
        if not self.manifest_path.exists():
            return False
        try:
            data = json.loads(self.manifest_path.read_text(encoding="utf-8"))
            self.entries = data.get("chunks", [])
            return bool(self.entries)
        except Exception:
            return False

    # ── chunk I/O ─────────────────────────────────────────────────────────────

    def get_chunk_data(self, tag: str) -> bytes | None:
        """Read the .bin for the first chunk matching *tag*; None if missing."""
        for e in self.entries:
            if e["tag"] == tag:
                p = self.work_dir / e["bin_file"]
                return p.read_bytes() if p.exists() else None
        return None

    def save_chunk_data(self, tag: str, data: bytes) -> bool:
        """Overwrite the .bin for the first chunk matching *tag*; return success."""
        for e in self.entries:
            if e["tag"] == tag:
                (self.work_dir / e["bin_file"]).write_bytes(data)
                return True
        return False

    def chunk_info(self) -> list[dict]:
        """Return entries enriched with *current_size* from the on-disk .bin."""
        out = []
        for e in self.entries:
            p = self.work_dir / e["bin_file"]
            out.append({**e, "current_size": p.stat().st_size if p.exists() else 0})
        return out

    # ── packing ───────────────────────────────────────────────────────────────

    def pack_wad(self, out_path: Path) -> None:
        """Reassemble all .bin files into a new WAD at *out_path*."""
        chunk_blocks = []
        for e in self.entries:
            p = self.work_dir / e["bin_file"]
            chunk_blocks.append((e["tag"], p.read_bytes() if p.exists() else b""))
        # WAD header: total_size (excl. itself) then tag-reversed + size + data per chunk
        total = 4 + sum(8 + len(d) for _, d in chunk_blocks)
        out_path.parent.mkdir(parents=True, exist_ok=True)
        with out_path.open("wb") as f:
            f.write(struct.pack("<I", total - 4))
            for tag, cdata in chunk_blocks:
                tag_b = tag.encode("ascii", errors="replace")[:4].ljust(4, b"\x00")
                f.write(bytes(reversed(tag_b)))
                f.write(struct.pack("<I", len(cdata)))
                f.write(cdata)

    @property
    def is_open(self) -> bool:
        return bool(self.entries)
