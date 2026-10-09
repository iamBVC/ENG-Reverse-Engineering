/* sub_41EE10 @ 0041ee10   48 bytes */

void sub_41EE10(void)

{
  if (DAT_00586574 != (void *)0x0) {
    sub_562941(DAT_00586574);
  }
  DAT_00586574 = operator_new(0x200000);
  sub_41AF00(DAT_00586574,0x800000);
  return;
}

