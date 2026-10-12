/* Hand reconstruction of 0x00412710: Direct3D texture-format callback (ret 8). */
int __stdcall sub_412710(unsigned int *format, unsigned int *context)
{
    char description[256];
    unsigned char marker = 11;
    unsigned int *record = (unsigned int *)context[2];
    unsigned int *selected;
    int i, accepted;
    unsigned int counts[4] = {0};
    for (i = 0; i < 4; ++i) {
        unsigned int mask = format[i == 0 ? 7 : i + 3];
        while (mask) {
            counts[i] += mask & 1;
            mask >>= 1;
        }
    }
    if (format[1] & 0x20)
        sub_562717(description, "indexed %d", format[3]);
    else if (format[1] & 0x40) {
        if (format[1] & 1)
            sub_562717(description, "argb %d%d%d%d", counts[0], counts[1], counts[2], counts[3]);
        else
            sub_562717(description, "rgb %d%d%d", counts[1], counts[2], counts[3]);
    } else
        sub_562717(description, "unknown format");
    if (DAT_005834d4) {
        sub_562B75(&marker, 1, 1, DAT_005834d4);
        sub_562B75(description, 1, _strlen(description) + 1, DAT_005834d4);
        sub_562B75(format, 32, 1, DAT_005834d4);
    }
    for (i = 0; i < 4; ++i) {
        selected = record + 22 + i * 8;
        switch (i) {
        case 0: accepted = sub_412D70(selected, format); break;
        case 1: accepted = sub_412D90(selected, format); break;
        case 2: accepted = sub_412F10(selected, format); break;
        default: accepted = sub_412FF0(selected, format); break;
        }
        if (accepted & 0xff) {
            int word;
            for (word = 0; word < 8; ++word)
                selected[word] = format[word];
        }
    }
    return 1;
}
