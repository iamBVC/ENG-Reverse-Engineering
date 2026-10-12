/* Hand reconstruction of 0x00412640: Direct3D depth-format callback (ret 8). */
int __stdcall sub_412640(unsigned int *format, unsigned int *context)
{
    char description[0x100];
    unsigned char marker = 0x0b;
    unsigned int *selected = (unsigned int *)(context[2] + 0x38);
    int i;

    sub_562717(description, "%d bit", format[3]);
    if (DAT_005834d4 != 0) {
        sub_562B75(&marker, 1, 1, DAT_005834d4);
        sub_562B75(description, 1, _strlen(description) + 1, DAT_005834d4);
        if (format != 0)
            sub_562B75(format, 0x20, 1, DAT_005834d4);
    }
    if (sub_412CB0(selected, format, context[1]) & 0xff) {
        for (i = 0; i < 8; ++i)
            selected[i] = format[i];
    }
    return 1;
}
