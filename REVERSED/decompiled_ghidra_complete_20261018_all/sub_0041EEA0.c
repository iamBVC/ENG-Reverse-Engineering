/* sub_41EEA0 @ 0041eea0   56 bytes */

void sub_41EEA0(void)

{
  if (DAT_00586580 != (void *)0x0) {
    sub_562941(DAT_00586580);
  }
  DAT_00586580 = operator_new(0x1000000);
  if (DAT_00586580 != (void *)0x0) {
    DAT_00586588 = 0x1000000;
    DAT_00586584 = DAT_00586580;
  }
  return;
}

