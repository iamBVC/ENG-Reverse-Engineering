/* Initialize the lookup tables used by RGB555 histogram construction. */
void sub_436CC0(undefined4 preserve_black)
{
  int i;
  int *table = &DAT_0061fb34;
  uint *count;

  DAT_006d76c8 = preserve_black;
  for (i = 0; i < 256; ++i)
    table[i] = i * i;

  count = (uint *)&DAT_006b4544;
  for (i = 0; i < 0x8c61; ++i) count[i] = 0;
  count = (uint *)&DAT_006913c0;
  for (i = 0; i < 0x8c61; ++i) count[i] = 0;
  count = (uint *)&DAT_0066e23c;
  for (i = 0; i < 0x8c61; ++i) count[i] = 0;
  count = (uint *)&DAT_0064b0b8;
  for (i = 0; i < 0x8c61; ++i) count[i] = 0;
  count = (uint *)&DAT_00627f34;
  for (i = 0; i < 0x8c61; ++i) count[i] = 0;
  count = (uint *)&DAT_0061ff34;
  for (i = 0; i < 0x2000; ++i) count[i] = 0;
}
