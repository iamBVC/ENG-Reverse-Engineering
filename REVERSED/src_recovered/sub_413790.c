/* Hand reconstruction of 0x00413790: width, then height. */
int sub_413790(unsigned int *left, unsigned int *right)
{
    if (left[3] != right[3])
        return (int)(left[3] - right[3]);
    return (int)(left[4] - right[4]);
}
