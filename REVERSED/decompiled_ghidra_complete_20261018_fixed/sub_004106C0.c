/* sub_4106C0 @ 004106c0   51 bytes */

void sub_4106C0(void)

{
  if (DAT_00582cd0 != (int *)0x0) {
    (**(code **)(*DAT_00582cd0 + 8))(DAT_00582cd0);
    DAT_00582cd0 = (int *)0x0;
  }
  if (DAT_00582ccc != (int *)0x0) {
    (**(code **)(*DAT_00582ccc + 8))(DAT_00582ccc);
    DAT_00582ccc = (int *)0x0;
  }
  return;
}

