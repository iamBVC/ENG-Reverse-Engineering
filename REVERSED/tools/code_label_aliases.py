"""Map Ghidra's LAB address names onto real function entries when bodies exist."""

from __future__ import annotations

import re


def function_for_code_label(label: str) -> str | None:
    match = re.fullmatch(r"(?:LAB|FUN)_([0-9a-fA-F]{1,8})", label)
    if not match:
        return None
    # Recovered/exported C function names conventionally uppercase A-F in the
    # hexadecimal address.  Keep the spelling canonical so direct symbol
    # filtering (which is case-sensitive on Windows tool outputs) finds bodies
    # such as `sub_43CD60` for a stale `FUN_0043cd60` linker name.
    return f"sub_{int(match.group(1), 16):X}"


def aliases_for_code_labels(labels: set[str], functions: set[str]) -> dict[str, str]:
    """Return label -> function only for exact-address bodies in the current image."""
    aliases: dict[str, str] = {}
    by_address = {
        int(match.group(1), 16): name
        for name in functions
        if (match := re.fullmatch(r"sub_([0-9a-fA-F]+)", name))
    }
    for label in labels:
        target = function_for_code_label(label)
        if target is not None:
            address = int(target[4:], 16)
            if address in by_address:
                aliases[label] = by_address[address]
    return aliases
