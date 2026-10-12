/* Hand reconstruction of 0x004136A0: compare mode keys, with x86 wraparound. */
int sub_4136A0(unsigned int *left, unsigned int *right)
{
    return (int)(left[3] - right[3]);
}
