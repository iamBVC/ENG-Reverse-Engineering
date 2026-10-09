/* sub_41CCC0 @ 0041ccc0   65 bytes */

undefined4 sub_41CCC0(void)

{
  if ((&DAT_00585274)[DAT_00584c28 * 0x100] != '\0') {
    DAT_006d9e74 = 0;
    DAT_00584c1c = 9;
    sub_41CA10(0x100);
    sub_41CBE0();
    return 1;
  }
  return 0;
}

