/* Selected Ghidra export at 004189f0. */

undefined4 sub_4189F0(void)

{
  if (((byte)DAT_005fcf08 & 0xa0) != 0) {
    sub_546170(0,0xffffff80,8);
    DAT_00585218 = DAT_00585218 ^ 1;
    if (DAT_005846e4 != 5) {
      sub_546170(0,0xffffff80,8);
      sub_418970();
      return 0;
    }
    DAT_006da2fc = (-(uint)(DAT_00585218 != 0) & 0xffff3000) + 0xe000;
  }
  sub_418970();
  return 0;
}

