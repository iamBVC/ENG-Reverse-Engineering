/* Hand reconstruction of the Direct3D device comparator at 0x00413480. */
int sub_413480(unsigned char *left, unsigned char *right)
{
    if (left[0x10] != right[0x10])
        return left[0x10] ? -1 : 1;
    if (left[0x11] != right[0x11])
        return left[0x11] ? 1 : -1;
    return 0;
}
