/* gr_data.c - data symbols referenced by the reversed code.
 *
 * Two different things live here, and the distinction matters:
 *
 *  1. CONSTANTS AND COUNTERS WHOSE VALUE IS KNOWN.  e.g. flt_56E008 = 1.0 and
 *     flt_56E1A0 = 0.01 were read straight out of the executable's .rdata, so
 *     the ported code computes the same numbers as the original.
 *
 *  2. ADDRESS-ONLY PLACEHOLDERS.  The original stores absolute addresses in
 *     these slots (the `off_xxxx` labels are IDA's name for a data location
 *     holding an offset).  Here they are dummy objects that exist purely so the
 *     code compiles and links at a *different* address; reversing the actual
 *     .data / .rdata contents is a separate phase of the project.  Anything
 *     marked PLACEHOLDER must not be treated as reversed.
 */
#include "groove.h"

/* ---- constants with confirmed values (original .rdata) ------------------- */
const float flt_56E008 = 1.0f;          /* 0x56E008 */
const float flt_56E1A0 = 0.0099999998f; /* 0x56E1A0, i.e. 0.01f */

/* ---- game globals ------------------------------------------------------- */
int  dword_581158 = 0;                  /* sub_406E30 clears it */
int  dword_583740 = 0;                  /* sub_4155E0 clears it */
int  dword_584644 = 0;                  /* scratch copy consumed by sub_41E1B0 */
int  dword_586408 = 0;                  /* sub_41D330 clears it */
int  dword_58640C = 0;                  /* sub_41D330 clears it */
int  dword_586420 = 0;                  /* sub_41E1B0 latches dword_584644 */

unsigned char byte_6D9858 = 0;          /* sub_40D900 clears it */
unsigned char byte_6D94E8 = 0;          /* sub_40D910 clears it */

float flt_581970 = 0.0f;                /* sub_40DB70 writes 1.0f / 0.01f */

/* Two 0x100- and 0x0F-dword buffers cleared by sub_40E020. */
unsigned int dword_58226C[0x100];
unsigned int unk_5821E0[0x0F];

/* PLACEHOLDER: data slots whose *address* is stored by sub_413B10 /
 * sub_40FC90.  The real contents belong to the .data reversal. */
void *off_56E1C4 = 0;
void *off_56E1C8 = 0;
