/* sub_41CC70 @ 0041cc70   73 bytes */

undefined4 sub_41CC70(void)

{
  DAT_006d9e74 = 0;
  DAT_00584c1c = 9;
  if ((&DAT_00585274)[DAT_00584c28 * 0x100] != '\0') {
    sub_41C640();
    return 1;
  }
  sub_41CA10(0x100);
  sub_41CBE0();
  return 1;
}

