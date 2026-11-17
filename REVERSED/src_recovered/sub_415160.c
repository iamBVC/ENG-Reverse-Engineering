/* Recovered from the callback block at 0x00415160 in groove.exe.asm. */
void sub_415160(void)
{
    int position = DAT_0058370c;
    int step;

    DAT_00583714 = 9;
    DAT_00583734 = 1;
    DAT_00583738 = 0;
    if (position >= 0xff)
        position = 0xff;
    else if (position <= 0)
        position = 0;

    DAT_0058373c = (int)((uint)position << 24);
    step = DAT_00583710;
    position += step;
    DAT_0058370c = position;
    sub_41A440(0xc0 - (position >> 1));

    if (position > 0x80)
        DAT_00583730 = 1;
}
