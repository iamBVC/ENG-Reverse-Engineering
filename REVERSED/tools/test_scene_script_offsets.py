"""Compare actual menu script relocation with the independent asset parser."""
import sys
from test_hardware_enumeration import ROOT, main as build_and_run

sys.path.insert(0, str(ROOT.parent / 'WAD'))
from eng_wad.wad import read_wad, chunk_bytes
from eng_wad.trak_chunk import parse_trak_chunk
from eng_wad.map_full_chunk import parse_map_full_exe
from eng_wad.wfpc_chunk import parse_wfpc_chunk

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static FILE *chunk(const char *path, unsigned int wanted, unsigned int *size)
{
    unsigned int tag;
    FILE *file = fopen(path, "rb"); REQUIRE(file);
    REQUIRE(fseek(file, 4, SEEK_SET) == 0);
    for (;;) {
        REQUIRE(fread(&tag, 4, 1, file) == 1 && fread(size, 4, 1, file) == 1);
        if (tag == wanted) return file;
        REQUIRE(fseek(file, *size, SEEK_CUR) == 0);
    }
}
int main(void)
{
    unsigned int size, cursor, *world, *records, i;
    unsigned char *track, *scripts;
    long start;
    FILE *file;
    const char *path = WAD_PATH;
    unsigned int expected[] = EXPECTED_OFFSETS;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    DAT_00586580 = (int)malloc(0x1000000); REQUIRE(DAT_00586580);
    sub_41EEE0(); DAT_006d7c61 = 1; DAT_006da330 = WFPC_FLAGS;
    DAT_00581154 = (int)calloc(256, 20);
    file = chunk(path, 0x5452414b, &size);
    track = malloc(size); REQUIRE(track && fread(track, size, 1, file) == 1); fclose(file);
    cursor = (UINT_PTR)(track+4);
    sub_5563F0(&cursor, *(unsigned int *)track, &DAT_005846ec);
    file = chunk(path, 0x53545043, &size);
    scripts = malloc(size); REQUIRE(scripts && fread(scripts, size, 1, file) == 1); fclose(file);
    DAT_006d9dbc = (int *)scripts;
    world = (unsigned int *)sub_42AA60(); REQUIRE(world);
    file = chunk(path, 0x4d415020, &size); start = ftell(file);
    sub_42AC50(world, file);
    REQUIRE(ftell(file) == start + size); fclose(file);
    REQUIRE(world[1] == sizeof expected / sizeof expected[0]);
    records = (unsigned int *)world[14];
    for (i = 0; i < world[1]; ++i)
        REQUIRE(records[i*18+8] == (UINT_PTR)(scripts+expected[i]));
    puts("scene scripts: shipped menu MAP consumed exactly and all six script offsets match the independent parser");
    return 0;
}
'''

if __name__ == '__main__':
    path = ROOT.parent / 'Game/wads/t0i0m000.wad'
    data, chunks, tags = read_wad(path)
    flags = parse_wfpc_chunk(chunk_bytes(data, tags['WFPC'])).flags
    parsed = parse_map_full_exe(chunk_bytes(data, tags['MAP ']),
        parse_trak_chunk(chunk_bytes(data, tags['TRAK'])),
        assume_optional20=bool(flags & 0x10000), assume_final_dword=bool(flags & 0x10))
    path_literal = str(path).replace('\\', '\\\\')
    offsets = '{' + ','.join(str(record.script_offset) for record in parsed.objects) + '}'
    source = SOURCE.replace('WAD_PATH', '"' + path_literal + '"').replace(
        'EXPECTED_OFFSETS', offsets).replace('WFPC_FLAGS', str(flags))
    raise SystemExit(build_and_run(source, 'scene_script_test'))
