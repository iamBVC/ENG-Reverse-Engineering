"""Validate the generated numeric registry reader without touching the registry."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static unsigned char payload[2048];
static DWORD payload_size, payload_type;
static int open_error, query_error, closes;
undefined4 sub_405960(undefined4 root, DWORD path, int read)
{
    REQUIRE(read == 1); return open_error ? 0 : 0x1234;
}
static LSTATUS WINAPI query(HKEY key, LPCSTR name, LPDWORD reserved, LPDWORD type, LPBYTE data, LPDWORD size)
{
    REQUIRE(key == (HKEY)0x1234 && *size == 2048 && reserved == NULL);
    if (query_error) return ERROR_MORE_DATA;
    *type = payload_type; *size = payload_size; memcpy(data, payload, payload_size); return ERROR_SUCCESS;
}
static LSTATUS WINAPI close_key(HKEY key) { REQUIRE(key == (HKEY)0x1234); ++closes; return 0; }
#define RegQueryValueExA query
#define RegCloseKey close_key
'''
MAIN = r'''
int main(void)
{
    float value = 99.0f;
    DWORD number = 0xffffffff;
    int before;
    payload_type = REG_SZ; payload_size = 7;
    memcpy(payload, " -1.25 ", 7); /* No NUL in the queried bytes. */
    REQUIRE(sub_405B00(&value, 0, 0, "test") == 1 && value == -1.25f && closes == 1);
    REQUIRE(sub_4057C0(0, 3.0f) == -1.25);
    payload_type = REG_DWORD; payload_size = sizeof number;
    memcpy(payload, &number, sizeof number);
    REQUIRE(sub_405B00(&value, 0, 0, "test") == 1 && value == (float)number);
    payload_size = 3; value = 99.0f;
    REQUIRE(sub_405B00(&value, 0, 0, "test") == 0 && value == 99.0f);
    payload_type = REG_SZ; payload_size = 2048;
    memset(payload, ' ', sizeof payload); payload[2047] = '2';
    REQUIRE(sub_405B00(&value, 0, 0, "test") == 1 && value == 2.0f);
    payload_size = 0;
    REQUIRE(sub_405B00(&value, 0, 0, "test") == 1 && value == 0.0f);
    query_error = 1; before = closes; value = 99.0f;
    REQUIRE(sub_405B00(&value, 0, 0, "test") == 0 && value == 99.0f && closes == before + 1);
    REQUIRE(sub_4057C0(0, 3.0f) == 3.0);
    open_error = 1; before = closes;
    REQUIRE(sub_405B00(&value, 0, 0, "test") == 0 && closes == before);
    REQUIRE(sub_56286F((byte *)"  -1.25e2tail") == -125.0);
    REQUIRE(sub_56286F((byte *)"invalid") == 0.0);
    puts("numeric preferences: terminated/bounded text, unsigned DWORDs, defaults, failures and CRT atof passed");
    return 0;
}
'''
if __name__ == '__main__':
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    bodies = [text.split(f'/* ==== {name} ==== */', 1)[1].split('/* ====', 1)[0]
              for name in ['sub_405B00', 'sub_4057C0', 'sub_56286F']]
    raise SystemExit(build_and_run(SOURCE + '\n'.join(bodies) + MAIN,
                                  'numeric_preferences_test', bulk=False))
