"""Check that the recovered CRT wrappers initialize their exact timer objects."""
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


def main() -> int:
    names = ("419450", "41A390", "41CED0")
    sources = [ROOT / "src_recovered" / f"sub_{name}.c" for name in names]
    missing = [str(path) for path in sources if not path.exists()]
    if missing:
        print("missing recovered initializer source: " + ", ".join(missing))
        return 1

    wrapper_text = "\n".join(path.read_text(encoding="utf-8") for path in sources)
    preamble = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int DAT_00584860_storage[7] = {0};
int DAT_005846b8_storage[7] = {0};
int DAT_00585a70_storage[7] = {0};
static void *last_object;
static unsigned int last_argument;
undefined4 *sub_54B970(undefined4 *object, undefined4 argument)
{
    last_object = object;
    last_argument = argument;
    return object;
}
'''
    main_text = r'''
int main(void)
{
    sub_419450();
    REQUIRE(last_object == DAT_005846b8_storage && last_argument == 0);
    sub_41A390();
    REQUIRE(last_object == DAT_00584860_storage && last_argument == 0);
    sub_41CED0();
    REQUIRE(last_object == DAT_00585a70_storage && last_argument == 0);
    puts("CRT timer initializers: all three exact object addresses passed");
    return 0;
}
'''
    return build_and_run(preamble + wrapper_text + main_text,
                         "crt_timer_initializers_test", bulk=False)


if __name__ == "__main__":
    raise SystemExit(main())
