/* Selected Ghidra export at 00418a50. */

undefined4 sub_418A50(void)

{
  if (((byte)DAT_005fcf08 & 0xa0) != 0) {
    sub_546170(0,0xffffff80,8);
    DAT_00585219 = DAT_00585219 ^ 1;
    sub_546170(0,0xffffff80,8);
    DAT_006da2fc = (-(uint)(DAT_00585219 != 0) & 0xfffff000) + 0x10000;
  }
  sub_418970();
  return 0;
}

