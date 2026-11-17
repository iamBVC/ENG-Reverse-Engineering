/* MSVC x86 implementations for x87 operations Ghidra emitted as external calls.
 * float10 is long double in the decompiler output; MSVC x86 stores that type as
 * an IEEE-754 double, and each helper uses the original x87 instruction. */
#include "ghidra_shim.h"

/* Read-only constants used by the original 32-bit x87 remainder routines.
 * These are copied from groove.exe at 0x0057D04C..0x0057D08D. The Ghidra
 * globals export split these overlapping values as 4-byte integers, which
 * would lose the 64-bit/80-bit operands needed by the recovered instructions. */
const unsigned char groove_sub_56b_expclass_table[16] = {
    0x00, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x07,
    0x00, 0x00, 0x0a, 0x00, 0x00, 0x0d, 0x00, 0x00
};
const double groove_sub_56b_scale_up = 18446744073709551616.0;
const double groove_sub_56b_scale_down = 5.42101086242752217003726400434970855712890625e-20;
const double groove_sub_56b_half = 0.5;
const unsigned char groove_sub_56b_remainder_limit[10] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x7f
};
const char groove_sub_563382_math_name[4] = "pow";
const unsigned char groove_sub_563382_positive_infinity[10] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x7f
};
const unsigned char groove_sub_563382_negative_infinity[10] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff
};

float10 ABS(float10 value)
{
    float10 result;
    __asm {
        fld qword ptr [value]
        fabs
        fstp qword ptr [result]
    }
    return result;
}

float10 ROUND(float10 value)
{
    float10 result;
    __asm {
        fld qword ptr [value]
        frndint
        fstp qword ptr [result]
    }
    return result;
}

float10 SQRT(float10 value)
{
    float10 result;
    __asm {
        fld qword ptr [value]
        fsqrt
        fstp qword ptr [result]
    }
    return result;
}

float10 f2xm1(float10 value)
{
    float10 result;
    __asm {
        fld qword ptr [value]
        f2xm1
        fstp qword ptr [result]
    }
    return result;
}

float10 fscale(float10 value, float10 exponent)
{
    float10 result;
    __asm {
        fld qword ptr [exponent]
        fld qword ptr [value]
        fscale
        fstp qword ptr [result]
        fstp st(0)
    }
    return result;
}

unsigned int SUB104(float10 value, unsigned int byte_offset)
{
    unsigned int result = 0;
    const unsigned int value_size = (unsigned int)sizeof(value);

    if (byte_offset <= value_size && value_size - byte_offset >= sizeof(result))
        memcpy(&result, (const unsigned char *)&value + byte_offset, sizeof(result));
    return result;
}

/* sub_403020 performs this exact x87 sequence in the original: FPATAN, multiply
 * by the game's -4096/(2*pi) scale, then convert with truncation regardless of the
 * caller's x87 rounding mode. Keep the data scale as a parameter so the generated
 * body retains an explicit reference to the recovered global. */
int groove_angle_to_game_units(int delta_x, int delta_y, float scale)
{
    unsigned short original_control;
    unsigned short truncate_control;
    long long converted;
    int result;

    __asm {
        fild dword ptr [delta_x]
        fild dword ptr [delta_y]
        fpatan
        fmul dword ptr [scale]
        fnstcw word ptr [original_control]
        mov ax, word ptr [original_control]
        or ah, 0Ch
        mov word ptr [truncate_control], ax
        fldcw word ptr [truncate_control]
        fistp qword ptr [converted]
        fldcw word ptr [original_control]
        mov eax, dword ptr [converted]
        mov result, eax
    }
    return result;
}
