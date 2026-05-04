# SRPC / CPRS reverse-engineering notes

## Identity

The WAD dispatcher compares the chunk id against `0x53525043`. The bytes are `43 50 52 53`, so the on-disk byte label is `CPRS`; this project displays chunk tags reversed for readability, so the chunk appears as `SRPC`.

The dispatcher calls:

```c
sub_545350(level_context, stream, 2);
```

Therefore `sub_545350` case `2` is the SRPC/CPRS loader.

## Loader: `sub_545350(..., case 2)`

Equivalent pseudocode:

```c
uint32_t count;
read_u32(stream, &count);

SRPCEntry16 *entries = alloc(count * 16);
for (uint32_t i = 0; i < count * 4; i++)
    read_u32(stream, ((uint32_t *)entries) + i);

sub_5465D0(entries, count);
```

## Runtime registration: `sub_5465D0`

```c
SRPCEntry16 *dword_6D91C4; // entries
uint32_t     dword_6D91C8; // count
uint32_t     dword_6D91D4; // loaded flag

void *sub_5465D0(SRPCEntry16 *entries, uint32_t count) {
    dword_6D91C4 = entries;
    dword_6D91C8 = count;
    dword_6D91D4 = 1;
    return entries + count;
}
```

## Disk structure

```c
#pragma pack(push, 1)
struct SRPCChunkDisk {
    uint32_t count;
    SRPCEntry16 entries[count];
};

struct SRPCEntry16 {
    uint32_t unknown_00;       // observed as dialogue/resource id-like value
    uint16_t rate_or_timing;   // sample-rate scalar; 2048 -> 22050 Hz
    uint16_t unknown_06;       // usually 0 in observed files
    uint32_t cvs_offset;       // byte offset into Music/ENGLISH.CVS
    uint32_t cvs_size;         // byte size before runtime 0x800 alignment
};
#pragma pack(pop)
```

## Playback: `sub_546620`

`sub_546620` validates the requested speech id against `dword_6D91C8`, selects `dword_6D91C4[speech_id]`, opens `Music/ENGLISH.CVS`, and sends a slice to AAL:

```c
entry = &dword_6D91C4[speech_id];
stream_ptr  = lpBaseAddress + entry->cvs_offset;
stream_size = (entry->cvs_size + 0x7FF) & ~0x7FF;
AAL_LoadResourceType(stream_ptr, stream_size, 0x15, 0);
```

It also copies `entry->rate_or_timing` to `word_6D93E4` and derives a sample-rate-like value:

```text
sample_rate_hz = rate_or_timing * 44100 / 4096
```

Observed common value:

```text
rate_or_timing = 2048 -> 22050 Hz
```

## CVS stream codec

The uploaded `english.CVS` slices match PlayStation/SPU ADPCM:

- 16-byte frames.
- 28 mono PCM samples per frame.
- first byte = filter/shift header.
- second byte = frame flags.
- remaining 14 bytes = 28 4-bit ADPCM nibbles.

This project decodes them to mono 16-bit PCM WAV.

## Exporter outputs

```text
srpc/srpc_entries.csv
srpc/summary.txt
srpc/cvs_slices/*.cvs
srpc/wav/*.wav
srpc/mp3/*.mp3       optional, requires ffmpeg and --srpc-mp3
```

The raw WAD chunk is still preserved separately as `raw/srpc.bin` when raw export is enabled.

## Remaining unknowns

- `SRPCEntry16.unknown_00`: often looks like a dialogue/resource id and is useful in filenames, but the confirmed playback path indexes by table index, not by this value.
- `SRPCEntry16.unknown_06`: observed as zero in tested samples; no confirmed consumer yet.
- Exact AAL resource type `0x15` name is unknown; behavior matches streamed speech/voice.
