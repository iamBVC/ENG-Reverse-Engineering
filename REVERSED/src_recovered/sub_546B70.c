/* Original music-stream setup, with the arguments Ghidra lost restored. */
void sub_546B70(int param_1)
{
    char filename[260];
    char *path;
    char *name;
    unsigned int index = 0xffffffff;
    unsigned char *header = (unsigned char *)DAT_006d9478_storage;
    int rate;
    if (!DAT_005834dc) return;
    if (!param_1) {
        sub_546CC0();
        return;
    }
    if (DAT_006d94a4) sub_546CC0();
    if (param_1 < 0 || param_1 >= 40) {
        fprintf(stderr, "[audio] invalid music stream %d\n", param_1);
        return;
    }
    name = (char *)((unsigned int *)&DAT_00578960)[param_1 * 5];
    if (!name || name + 8 == (char *)&DAT_0057f834) {
        fprintf(stderr, "[audio] no file for music stream %d\n", param_1);
        return;
    }
    sub_562717(filename, s__s_ASF_00578e7c, name + 8);
    path = (char *)sub_415690(s_Music_00578e48, filename);
    if (!path) {
        fprintf(stderr, "[audio] music file unavailable: %s\n", filename);
        return;
    }
    DAT_006d948c = (void *)_AAL_LoadFile_8(path, 0x40);
    if (!DAT_006d948c) return;
    *(unsigned int *)(header + 0) = _AAL_GetDataSize_4(DAT_006d948c);
    rate = _AAL_GetSampleRate_4(DAT_006d948c);
    *(short *)(header + 4) = (short)((rate << 12) / 44100);
    *(short *)(header + 6) = 0x7f;
    *(short *)(header + 8) = 0x2400;
    *(short *)(header + 10) = 1;
    DAT_006d94a4 = sub_5487A0(header, 0, 0x2400, &index);
    if (DAT_006d94a4)
        sub_5489C0(DAT_006d9498 + 0x10, DAT_006d94a4);
}
