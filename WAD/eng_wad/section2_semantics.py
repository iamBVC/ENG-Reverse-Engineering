"""Evidence-backed semantic labels for MAP Section2 object-local slices.

Schemas are intentionally narrow: an object name and local count must both
match. Similar names can refer to different STPC programs and must not inherit
labels until their normalized bytecode behavior has been verified.
"""

from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class Section2FieldSemantic:
    name: str
    value_type: str
    description: str
    confidence: str = "confirmed"


_COIN_3 = (
    Section2FieldSemantic(
        "Run interaction block",
        "fixed12_bool",
        "When false, the Coin script skips its contact/collection response block.",
    ),
    Section2FieldSemantic(
        "Enable contact propagation flags",
        "fixed12_bool",
        "When true, the script enables actor E8:0x8000 and EC:0x2, then runs the contact update path.",
    ),
    Section2FieldSemantic(
        "Skip default render setup",
        "fixed12_bool",
        "When true, the script skips its default render-index/radius and initial-yaw setup.",
    ),
)


def section2_schema(object_name: str, local_count: int) -> tuple[Section2FieldSemantic, ...] | None:
    """Return a verified schema only for an exact known object variant."""
    if object_name == "Coin" and local_count == 3:
        return _COIN_3
    return None
