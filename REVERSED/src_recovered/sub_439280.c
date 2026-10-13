/* Clear the frame surfaces with native COM cleanup and complete descriptors. */
void sub_439280(void)
{
    unsigned int effect[25] = {0};
    unsigned int rectangle[4] = {0, 0, DAT_00583374, DAT_00583378};
    effect[0] = 100;
    (**(groove_com6 **)(*DAT_00582ce4 + 0x14))
        (DAT_00582ce4, 0, 0, 0, 0x1000400, effect);
    if (DAT_005833e1 != 0) {
        memset(DAT_005832f0, 0xff, DAT_00583374 * DAT_00583378 * 2);
        return;
    }
    if (G_BYTE(DAT_005833e4, 1) != 0)
        (**(groove_com7 **)(*DAT_00582cd8 + 0x50))
            (DAT_00582cd8, 1, rectangle, 2, 0, 0x3f800000, 0);
}
