"""Verify a valid Direct3D software descriptor is used when HW caps are empty."""
from test_hardware_enumeration import SOURCE, main as build_and_run


source = SOURCE.replace(
    "int *record, *format, *mode;",
    "int *record, *format, *mode;\n    unsigned int hardware_caps[63] = {0};",
).replace(
    'sub_411D60((int)guid, "fixture", "fixture HAL", caps, 0, (unsigned int *)&parent)',
    'sub_411D60((int)guid, "fixture", "fixture RGB software", hardware_caps, (undefined4)(UINT_PTR)caps, (unsigned int *)&parent)',
)
if source == SOURCE or '"fixture RGB software"' not in source:
    raise RuntimeError("software-descriptor fixture was not constructed")

if __name__ == "__main__":
    raise SystemExit(build_and_run(source, "software_device_fallback_test"))
