/* sub_40F220 @ 0040f220   102 bytes */

void sub_40F220(void)

{
  if (DAT_00582a74 != (int *)0x0) {
    (**(code **)(*DAT_00582a74 + 8))(DAT_00582a74);
    DAT_00582a74 = (int *)0x0;
  }
  if (DAT_00582a7c != (int *)0x0) {
    (**(code **)(*DAT_00582a7c + 0x20))(DAT_00582a7c);
    (**(code **)(*DAT_00582a7c + 8))(DAT_00582a7c);
    DAT_00582a7c = (int *)0x0;
  }
  if (DAT_00582a80 != (int *)0x0) {
    (**(code **)(*DAT_00582a80 + 0x20))(DAT_00582a80);
    (**(code **)(*DAT_00582a80 + 8))(DAT_00582a80);
    DAT_00582a80 = (int *)0x0;
  }
  sub_40F3B0();
  return;
}

