/* sub_4114A0 @ 004114a0   69 bytes */

void sub_4114A0(void)

{
  if (DAT_00582cd8 != (int *)0x0) {
    (**(code **)(*DAT_00582cd4 + 0x18))(DAT_00582cd4,DAT_00582cd8);
    (**(code **)(*DAT_00582cd8 + 8))(DAT_00582cd8);
    DAT_00582cd8 = (int *)0x0;
  }
  if (DAT_00582cd4 != (int *)0x0) {
    (**(code **)(*DAT_00582cd4 + 8))(DAT_00582cd4);
    DAT_00582cd4 = (int *)0x0;
  }
  return;
}

