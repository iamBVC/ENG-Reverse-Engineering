"""Ensure legacy MSVC ThrowInfo records are reconstructed for the game EH path."""

from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


class LegacyExceptionMetadataTests(unittest.TestCase):
    def test_throw_info_maps_to_complete_original_type_hierarchies(self):
        fixture = r'''
#include <string.h>
unsigned char DAT_0056eff0, DAT_0056f000, DAT_0056f168;
unsigned char DAT_0056f5d8, DAT_0056f648, DAT_0056f700;
int DAT_0056F0D0;
void sub_413B10(void) {}
void sub_40FCD0(void) {}
void sub_40FC90(void) {}
void sub_40FCB0(void) {}
void sub_411470(void) {}
void sub_56D23E(void) {}
void sub_56D188(void) {}
void sub_56D326(void) {}
void sub_56D2B4(void) {}
void sub_56D1E1(void) {}
void sub_56D605(void) {}
void sub_56D39C(void) {}
void sub_5632FF(void) {}
void groove_unwind_410700_state1(void) {}
void groove_unwind_410700_state2(void) {}
void groove_unwind_56d0a0_state1(void) {}
void groove_unwind_56d0fa_state1(void) {}
void groove_unwind_56d2cc_state1(void) {}
int groove_catch_handler_impl(void) { return 0; }
#include "../harness/legacy_exception_metadata.h"

int main(void)
{
    const GrooveLegacyThrowInfo *info;
    info = groove_resolve_legacy_throw_info(&DAT_0056eff0);
    if (!info || info->catchable_types->count != 3) return 1;
    if (strcmp(info->catchable_types->entries[0]->type->name,
               ".?AVddraw_exception@@") != 0) return 2;
    if (strcmp(info->catchable_types->entries[2]->type->name,
               ".?AVcroc_exception@@") != 0) return 3;
    info = groove_resolve_legacy_throw_info(&DAT_0056f000);
    if (!info || info->catchable_types->count != 2) return 4;
    if (strcmp(info->catchable_types->entries[0]->type->name,
               ".?AVdisplay_exception@@") != 0) return 5;
    info = groove_resolve_legacy_throw_info(&DAT_0056f168);
    if (!info || info->catchable_types->count != 3) return 6;
    if (strcmp(info->catchable_types->entries[0]->type->name,
               ".?AVd3d_exception@@") != 0) return 7;
    info = groove_resolve_legacy_throw_info(&DAT_0056f5d8);
    if (!info || info->catchable_types->count != 3) return 8;
    if (strcmp(info->catchable_types->entries[0]->type->name,
               ".?AVlength_error@std@@") != 0) return 9;
    info = groove_resolve_legacy_throw_info(&DAT_0056f648);
    if (!info || info->catchable_types->count != 2) return 10;
    info = groove_resolve_legacy_throw_info(&DAT_0056f700);
    if (!info || info->catchable_types->count != 3) return 11;
    if (groove_resolve_legacy_throw_info((void *)1) != NULL) return 12;
    if (sizeof(GrooveLegacyTypeDescriptor) != 12) return 13;
    if (sizeof(GrooveLegacyCatchableType) != 28) return 14;
    if (sizeof(GrooveLegacyThrowInfo) != 16) return 15;
    {
        const GrooveLegacyFuncInfo *frame =
            groove_find_legacy_func_info(&DAT_0056F0D0);
        if (!frame || frame->magic != 0x19930520 || frame->max_state != 4) return 16;
        if (!frame->unwind_map || frame->unwind_map[2].to_state != 1 ||
            frame->unwind_map[3].to_state != 2) return 17;
        if (frame->try_block_count != 1 || !frame->try_blocks) return 18;
        if (frame->try_blocks[0].try_low != 0 ||
            frame->try_blocks[0].catch_high != 3 ||
            frame->try_blocks[0].handler_count != 1) return 19;
        if (strcmp(frame->try_blocks[0].handlers[0].type->name,
                   ".?AVcroc_exception@@") != 0) return 20;
        if (frame->try_blocks[0].handlers[0].object_displacement != -0x15c ||
            !frame->try_blocks[0].handlers[0].handler) return 21;
        if (groove_find_legacy_func_info((void *)1) != NULL) return 22;
    }
    {
        const unsigned addresses[] = { 0x0056f5e8, 0x0056f610, 0x0056f710 };
        unsigned i;
        for (i = 0; i < sizeof(addresses) / sizeof(addresses[0]); ++i) {
            const GrooveLegacyFuncInfo *frame =
                groove_find_legacy_func_info((void *)(uintptr_t)addresses[i]);
            if (!frame || frame->magic != 0x19930520 || frame->max_state != 1) return 23;
            if (!frame->unwind_map || frame->unwind_map[0].to_state != -1 ||
                !frame->unwind_map[0].action || frame->try_block_count != 0) return 24;
        }
    }
    return 0;
}
'''
        self.assertEqual(build_and_run(fixture, "legacy_exception_metadata_test",
                                       bulk=False), 0)


if __name__ == "__main__":
    unittest.main()
