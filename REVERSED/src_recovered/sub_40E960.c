/* Hand reconstruction of 0x0040E960: first keyboard product-name prefix, ret 8. */
int __stdcall sub_40E960(unsigned char *instance, void *context)
{
    int i;
    for (i = 0; i < 16; ++i)
        ((unsigned char *)DAT_00582b50)[i] = instance[0x12c + i];
    return 0;
}
