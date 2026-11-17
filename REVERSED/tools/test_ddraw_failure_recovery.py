"""Guard the generated DirectDraw retry path against malformed CSV patches."""

import csv
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
PATCHES = ROOT / "src_generated" / "bulk_patches.csv"
GENERATED_CHUNKS = ROOT / "src_generated" / "chunks"

with PATCHES.open(encoding="utf-8", newline="") as stream:
    rows = list(csv.DictReader(stream))

fallback = next(
    row for row in rows
    if row["function"] == "sub_411D60"
    and "cVar4 = sub_412A10(local_24 + 4,iVar5);" in row["find"]
)
assert "param_5 != 0" in fallback["replace"]
assert "sub_412A10(enum_context.record + 4" in fallback["replace"]

mode_failure = next(
    row for row in rows
    if row["function"] == "sub_410700"
    and "__CxxThrowException_8(&local_94" in row["find"]
)
assert "ExceptionList = local_10;" in mode_failure["replace"]
assert "return 0;" in mode_failure["replace"]
assert "__CxxThrowException_8" not in mode_failure["replace"]
assert "sub_410ED0();" in mode_failure["replace"]

primary_surface_failure = next(
    row for row in rows
    if row["function"] == "sub_410700"
    and "__CxxThrowException_8(&local_58" in row["find"]
)
assert "__CxxThrowException_8" not in primary_surface_failure["replace"]
assert "sub_410ED0();" in primary_surface_failure["replace"]

generated = "\n".join(
    path.read_text(encoding="utf-8")
    for path in sorted(GENERATED_CHUNKS.glob("chunk_*.c"))
)
assert "if ((cVar4 == 0) && (param_5 != 0))" in generated
assert "sub_412A10(enum_context.record + 4" in generated
start = generated.index("/* ==== sub_410700 ====")
end = generated.find("/* ==== ", start + 1)
function = generated[start:end]
assert "[graphics] failure: %s hr=%08x" in function
assert "ExceptionList = local_10;\n    return 0;" in function
assert "sub_410ED0();\n    ExceptionList = local_10;\n    return 0;" in function
assert function.index("return 0;", function.index("local_94")) < function.index(
    "DAT_00582cdc + 0x14"
)
print("DirectDraw capability fallback and failed-mode retry paths are generated.")
