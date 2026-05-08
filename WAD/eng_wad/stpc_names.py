"""stpc_names.py — Extract human-readable object names from a STPC bytecode blob.

Strategy
--------
MAP script_offset values point somewhere inside the STPC binary.  The VM has a
debug/name opcode B4 whose inline payload ends with a null-terminated CamelCase
identifier — typically the object's class name.

Two strategies are tried per offset, falling back if the first finds nothing:

1. B4 marker scan  — build a global list of (position, name) pairs for every
   B4 record in STPC; find the nearest marker *before* the target offset.
2. Referenced-script name — look for a B2 (call) opcode near the entrypoint
   whose target offset has a named B4 marker.
3. Forward marker scan — look for a B4 marker *after* the offset (≤ 1 kB).
4. Raw scan fallback — search for the first CamelCase null-terminated string
   in the 2 kB window following the entrypoint.
"""

from __future__ import annotations

import re

_B4_OPCODE = b"\xB4\x00\x00\x00"   # VM debug/name opcode

# CamelCase identifier: uppercase start, then alphanumeric, 3–30 chars total.
# Filters out error strings (spaces, colons) while matching all known ENG names.
_NAME_RE = re.compile(r"^[A-Z][A-Za-z0-9]{2,29}$")


def _valid_stpc_name(raw: bytes) -> bool:
    """Return True if *raw* looks like a plausible ENG object name."""
    try:
        text = raw.decode("ascii")
    except UnicodeDecodeError:
        return False
    if not _NAME_RE.match(text):
        return False
    # Require at least one lowercase letter (rejects ALL_CAPS constants and
    # packed 4-byte immediates that accidentally start with an uppercase byte).
    if len(raw) < 3 or not any(97 <= b <= 122 for b in raw):
        return False
    # Very short names are fine only if purely alphabetic (no digits like "A1B")
    return len(raw) >= 4 or not any(48 <= b <= 57 for b in raw)


def _b4_name_markers(stpc_data: bytes) -> list[tuple[int, str]]:
    """Return candidate debug/name markers from all B4 opcode records.

    B4's inline payload is variable-width, so the name is not always at a fixed
    +20 byte offset.  We scan a 128-byte window after each B4 header and keep
    the *longest* plausible CamelCase string found — this picks the root name
    (e.g. 'RisingColumns') over shorter child labels ('ColumnChild').

    Returns a list of (byte_position, name) sorted by position.
    """
    markers: list[tuple[int, str]] = []
    n   = len(stpc_data)
    pos = stpc_data.find(_B4_OPCODE)
    while pos != -1:
        candidates: list[bytes] = []
        window_end = min(pos + 128, n)
        i = pos + 4
        while i < window_end:
            if ord("A") <= stpc_data[i] <= ord("Z"):
                j = i
                while j < window_end and stpc_data[j] != 0 and 32 <= stpc_data[j] <= 126:
                    j += 1
                raw = stpc_data[i:j]
                if j < n and stpc_data[j] == 0 and _valid_stpc_name(raw):
                    candidates.append(raw)
                i = max(j + 1, i + 1)
            else:
                i += 1
        if candidates:
            name = max(candidates, key=len).decode("ascii", errors="replace")
            markers.append((pos, name))
        pos = stpc_data.find(_B4_OPCODE, pos + 1)
    return markers


def _name_via_scan(stpc_data: bytes, start: int, end: int) -> str:
    """Fallback: find the first CamelCase identifier anywhere in [start, end).

    Scans byte-by-byte for null-terminated strings that start with an uppercase
    letter and contain only printable ASCII — matches all ENG object names while
    rejecting error messages (spaces, punctuation).
    """
    n = len(stpc_data)
    i = start
    while i < min(end, n):
        b = stpc_data[i]
        if ord("A") <= b <= ord("Z"):
            j = i
            while j < n and stpc_data[j] != 0 and 32 <= stpc_data[j] <= 126:
                j += 1
            if j < n and stpc_data[j] == 0:
                name = stpc_data[i:j].decode("ascii", errors="replace")
                if _valid_stpc_name(name.encode("ascii", errors="ignore")):
                    return name
            i = j + 1
        else:
            i += 1
    return ""


def _marker_name_near(
    markers: list[tuple[int, str]],
    offset: int,
    *,
    before: int = 4096,
    after: int = 0,
) -> str:
    """Return the name of the nearest B4 marker within *before* bytes before
    or *after* bytes after *offset*.  Prefers the before-direction."""
    best_before: tuple[int, str] | None = None
    best_after:  tuple[int, str] | None = None
    for pos, name in markers:
        if pos <= offset and offset - pos <= before:
            best_before = (pos, name)
        elif pos > offset:
            if pos - offset <= after:
                best_after = (pos, name)
            break  # markers are sorted; no point continuing
    return (best_before or best_after or (0, ""))[1]


def _referenced_script_name(stpc_data: bytes, start: int,
                             markers: list[tuple[int, str]]) -> str:
    """Follow B2 (call) operands near *start* to find a named target.

    B2 operands that are geometry refs tend to be small values; large values
    (≥ 0x100000) are script/DEFANIM pointers.  If such a target has a nearby
    B4 marker, its name is a reasonable fallback for wrapper entrypoints.
    """
    for pos in range(start, min(len(stpc_data) - 8, start + 768)):
        if stpc_data[pos:pos + 4] == b"\xB2\x00\x00\x00":
            target = int.from_bytes(stpc_data[pos + 4:pos + 8], "little")
            if 0 <= target < len(stpc_data) and target >= 0x100000:
                name = _marker_name_near(markers, target, before=768, after=256)
                if name:
                    return name
    return ""


def build_stpc_name_map(stpc_data: bytes,
                        script_offsets: list[int]) -> dict[int, str]:
    """Return {script_offset: name} for every offset that has a readable name.

    MAP script_offsets often point *inside* a larger STPC object block, so the
    B4 name marker typically appears *before* the entrypoint.  We prefer the
    nearest preceding marker, then try the four fallback strategies above.
    """
    n      = len(stpc_data)
    unique = sorted(so for so in set(script_offsets) if 0 <= so < n)
    if not unique:
        return {}

    result:  dict[int, str] = {}
    markers = _b4_name_markers(stpc_data)

    for i, so in enumerate(unique):
        # Strategy 1: nearest B4 marker strictly before this offset
        name = _marker_name_near(markers, so, before=4096, after=0)
        # Strategy 2: follow a B2 call from the entrypoint to a named target
        if not name:
            name = _referenced_script_name(stpc_data, so, markers)
        # Strategy 3: nearest B4 marker slightly after this offset
        if not name:
            name = _marker_name_near(markers, so, before=0, after=1024)
        # Strategy 4: raw scan forward for any CamelCase string
        if not name:
            next_so = unique[i + 1] if i + 1 < len(unique) else n
            name = _name_via_scan(stpc_data, so, min(next_so, so + 2048))
        if name:
            result[so] = name

    return result
