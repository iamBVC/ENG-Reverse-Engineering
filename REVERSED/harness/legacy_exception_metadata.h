/* Reconstructed MSVC 6 EH3 metadata referenced by the game's C++ throw sites.
 * Ghidra reported these records as one-byte undefined globals, so the bulk C image
 * otherwise passed zero-filled bytes to RaiseException instead of valid ThrowInfo.
 * Layout and hierarchy below are decoded from the original groove.exe .rdata bytes.
 */
#ifndef GROOVE_LEGACY_EXCEPTION_METADATA_H
#define GROOVE_LEGACY_EXCEPTION_METADATA_H

#include <stddef.h>
#include <stdint.h>

typedef struct GrooveLegacyTypeDescriptor {
    const void *vftable;
    const void *spare;
    const char *name;
} GrooveLegacyTypeDescriptor;

typedef struct GrooveLegacyCatchableType {
    unsigned int properties;
    const GrooveLegacyTypeDescriptor *type;
    int this_mdisp;
    int this_pdisp;
    int this_vdisp;
    int size_or_offset;
    const void *copy_function;
} GrooveLegacyCatchableType;

typedef struct GrooveLegacyCatchableTypeArray {
    int count;
    const GrooveLegacyCatchableType *entries[3];
} GrooveLegacyCatchableTypeArray;

typedef struct GrooveLegacyThrowInfo {
    unsigned int attributes;
    const void *unwind_function;
    const void *forward_compat;
    const GrooveLegacyCatchableTypeArray *catchable_types;
} GrooveLegacyThrowInfo;

typedef struct GrooveLegacyUnwindEntry {
    int to_state;
    const void *action;
} GrooveLegacyUnwindEntry;

typedef struct GrooveLegacyHandlerType {
    unsigned int adjectives;
    const GrooveLegacyTypeDescriptor *type;
    int object_displacement;
    const void *handler;
} GrooveLegacyHandlerType;

typedef struct GrooveLegacyTryBlock {
    int try_low;
    int try_high;
    int catch_high;
    int handler_count;
    const GrooveLegacyHandlerType *handlers;
} GrooveLegacyTryBlock;

typedef struct GrooveLegacyFuncInfo {
    unsigned int magic;
    int max_state;
    const GrooveLegacyUnwindEntry *unwind_map;
    int try_block_count;
    const GrooveLegacyTryBlock *try_blocks;
    int ip_entry_count;
    const void *ip_to_state_map;
    const void *exception_specification;
    const void *reserved;
} GrooveLegacyFuncInfo;

extern unsigned char DAT_0056eff0;
extern unsigned char DAT_0056f000;
extern unsigned char DAT_0056f168;
extern unsigned char DAT_0056f5d8;
extern unsigned char DAT_0056f648;
extern unsigned char DAT_0056f700;
extern int DAT_0056F0D0;

extern void groove_unwind_410700_state1(void);
extern void groove_unwind_410700_state2(void);
extern void groove_unwind_56d0a0_state1(void);
extern void groove_unwind_56d0fa_state1(void);
extern void groove_unwind_56d2cc_state1(void);
extern void groove_unwind_56d_exception_base_state1(void);
extern int __cdecl groove_catch_handler_impl(void);

/* On x86 the original type_info vftable has a deleting destructor in slot zero. */
static const void *const groove_legacy_type_info_vftable[2] = {
    (const void *)sub_5632FF,
    NULL
};

#define GROOVE_LEGACY_TYPE(symbol, decorated_name) \
    static const GrooveLegacyTypeDescriptor symbol = { \
        groove_legacy_type_info_vftable, NULL, decorated_name \
    }

#define GROOVE_LEGACY_CATCHABLE(symbol, descriptor, object_size, copy_fn) \
    static const GrooveLegacyCatchableType symbol = { \
        0, &(descriptor), 0, -1, 0, object_size, (const void *)(copy_fn) \
    }

GROOVE_LEGACY_TYPE(groove_td_ddraw_exception, ".?AVddraw_exception@@");
GROOVE_LEGACY_TYPE(groove_td_display_exception, ".?AVdisplay_exception@@");
GROOVE_LEGACY_TYPE(groove_td_croc_exception, ".?AVcroc_exception@@");
GROOVE_LEGACY_TYPE(groove_td_d3d_exception, ".?AVd3d_exception@@");
GROOVE_LEGACY_TYPE(groove_td_std_exception, ".?AVexception@@");
GROOVE_LEGACY_TYPE(groove_td_logic_error, ".?AVlogic_error@std@@");
GROOVE_LEGACY_TYPE(groove_td_length_error, ".?AVlength_error@std@@");
GROOVE_LEGACY_TYPE(groove_td_out_of_range, ".?AVout_of_range@std@@");

GROOVE_LEGACY_CATCHABLE(groove_ct_ddraw, groove_td_ddraw_exception, 0x0c, sub_40FCD0);
GROOVE_LEGACY_CATCHABLE(groove_ct_display, groove_td_display_exception, 0x08, sub_40FC90);
GROOVE_LEGACY_CATCHABLE(groove_ct_croc, groove_td_croc_exception, 0x08, sub_40FCB0);
GROOVE_LEGACY_CATCHABLE(groove_ct_d3d, groove_td_d3d_exception, 0x0c, sub_411470);
GROOVE_LEGACY_CATCHABLE(groove_ct_std_exception, groove_td_std_exception, 0x0c, sub_56D605);
GROOVE_LEGACY_CATCHABLE(groove_ct_logic_error, groove_td_logic_error, 0x1c, sub_56D1E1);
GROOVE_LEGACY_CATCHABLE(groove_ct_length_error, groove_td_length_error, 0x1c, sub_56D2B4);
GROOVE_LEGACY_CATCHABLE(groove_ct_out_of_range, groove_td_out_of_range, 0x1c, sub_56D39C);

static const GrooveLegacyCatchableTypeArray groove_cta_ddraw = {
    3, { &groove_ct_ddraw, &groove_ct_display, &groove_ct_croc }
};
static const GrooveLegacyCatchableTypeArray groove_cta_display = {
    2, { &groove_ct_display, &groove_ct_croc }
};
static const GrooveLegacyCatchableTypeArray groove_cta_d3d = {
    3, { &groove_ct_d3d, &groove_ct_display, &groove_ct_croc }
};
static const GrooveLegacyCatchableTypeArray groove_cta_length_error = {
    3, { &groove_ct_length_error, &groove_ct_logic_error, &groove_ct_std_exception }
};
static const GrooveLegacyCatchableTypeArray groove_cta_logic_error = {
    2, { &groove_ct_logic_error, &groove_ct_std_exception }
};
static const GrooveLegacyCatchableTypeArray groove_cta_out_of_range = {
    3, { &groove_ct_out_of_range, &groove_ct_logic_error, &groove_ct_std_exception }
};

static const GrooveLegacyThrowInfo groove_ti_ddraw = {
    0, (const void *)sub_413B10, NULL, &groove_cta_ddraw
};
static const GrooveLegacyThrowInfo groove_ti_display = {
    0, (const void *)sub_413B10, NULL, &groove_cta_display
};
static const GrooveLegacyThrowInfo groove_ti_d3d = {
    0, (const void *)sub_413B10, NULL, &groove_cta_d3d
};
static const GrooveLegacyThrowInfo groove_ti_length_error = {
    0, (const void *)sub_56D23E, NULL, &groove_cta_length_error
};
static const GrooveLegacyThrowInfo groove_ti_logic_error = {
    0, (const void *)sub_56D188, NULL, &groove_cta_logic_error
};
static const GrooveLegacyThrowInfo groove_ti_out_of_range = {
    0, (const void *)sub_56D326, NULL, &groove_cta_out_of_range
};

static const GrooveLegacyUnwindEntry groove_um_410700[4] = {
    { -1, NULL },
    { -1, NULL },
    { 1, (const void *)groove_unwind_410700_state1 },
    { 2, (const void *)groove_unwind_410700_state2 }
};
static const GrooveLegacyHandlerType groove_ht_410700[1] = {
    { 0, &groove_td_croc_exception, -0x15c, (const void *)groove_catch_handler_impl }
};
static const GrooveLegacyTryBlock groove_tb_410700[1] = {
    { 0, 0, 3, 1, groove_ht_410700 }
};
static const GrooveLegacyFuncInfo groove_fi_410700 = {
    0x19930520, 4, groove_um_410700, 1, groove_tb_410700, 0, NULL, NULL, NULL
};

/* Original FuncInfo records at 0x0056F5E8, 0x0056F610 and 0x0056F710
 * each have one active unwind state and no try blocks. Their original actions
 * destroy the temporary strings/exception base using the owning EBP frame. */
static const GrooveLegacyUnwindEntry groove_um_56d0a0[1] = {
    { -1, (const void *)groove_unwind_56d0a0_state1 }
};
static const GrooveLegacyUnwindEntry groove_um_56d0fa[1] = {
    { -1, (const void *)groove_unwind_56d0fa_state1 }
};
static const GrooveLegacyUnwindEntry groove_um_56d2cc[1] = {
    { -1, (const void *)groove_unwind_56d2cc_state1 }
};
static const GrooveLegacyFuncInfo groove_fi_56d0a0 = {
    0x19930520, 1, groove_um_56d0a0, 0, NULL, 0, NULL, NULL, NULL
};
static const GrooveLegacyFuncInfo groove_fi_56d0fa = {
    0x19930520, 1, groove_um_56d0fa, 0, NULL, 0, NULL, NULL, NULL
};
static const GrooveLegacyFuncInfo groove_fi_56d2cc = {
    0x19930520, 1, groove_um_56d2cc, 0, NULL, 0, NULL, NULL, NULL
};

/* The four neighbouring C++ exception constructors share the same EBP-local
 * base-object cleanup action. Their FuncInfo addresses remain original tokens. */
static const GrooveLegacyUnwindEntry groove_um_56d_exception_base[1] = {
    { -1, (const void *)groove_unwind_56d_exception_base_state1 }
};
static const GrooveLegacyFuncInfo groove_fi_56d188 = {
    0x19930520, 1, groove_um_56d_exception_base, 0, NULL, 0, NULL, NULL, NULL
};
static const GrooveLegacyFuncInfo groove_fi_56d1e1 = {
    0x19930520, 1, groove_um_56d_exception_base, 0, NULL, 0, NULL, NULL, NULL
};
static const GrooveLegacyFuncInfo groove_fi_56d23e = {
    0x19930520, 1, groove_um_56d_exception_base, 0, NULL, 0, NULL, NULL, NULL
};
static const GrooveLegacyFuncInfo groove_fi_56d326 = {
    0x19930520, 1, groove_um_56d_exception_base, 0, NULL, 0, NULL, NULL, NULL
};

static const GrooveLegacyFuncInfo *groove_find_legacy_func_info(void *legacy_info)
{
    if (legacy_info == &DAT_0056F0D0) return &groove_fi_410700;
    if (legacy_info == (void *)(uintptr_t)0x0056F5E8u) return &groove_fi_56d0a0;
    if (legacy_info == (void *)(uintptr_t)0x0056F610u) return &groove_fi_56d0fa;
    if (legacy_info == (void *)(uintptr_t)0x0056F658u) return &groove_fi_56d188;
    if (legacy_info == (void *)(uintptr_t)0x0056F680u) return &groove_fi_56d1e1;
    if (legacy_info == (void *)(uintptr_t)0x0056F6A8u) return &groove_fi_56d23e;
    if (legacy_info == (void *)(uintptr_t)0x0056F710u) return &groove_fi_56d2cc;
    if (legacy_info == (void *)(uintptr_t)0x0056F738u) return &groove_fi_56d326;
    return NULL;
}

static const GrooveLegacyThrowInfo *groove_resolve_legacy_throw_info(void *legacy_info)
{
    if (legacy_info == &DAT_0056eff0) return &groove_ti_ddraw;
    if (legacy_info == &DAT_0056f000) return &groove_ti_display;
    if (legacy_info == &DAT_0056f168) return &groove_ti_d3d;
    if (legacy_info == &DAT_0056f5d8) return &groove_ti_length_error;
    if (legacy_info == &DAT_0056f648) return &groove_ti_logic_error;
    if (legacy_info == &DAT_0056f700) return &groove_ti_out_of_range;
    return NULL;
}

#undef GROOVE_LEGACY_TYPE
#undef GROOVE_LEGACY_CATCHABLE

#endif
