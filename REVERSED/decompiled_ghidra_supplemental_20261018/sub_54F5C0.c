/* Selected Ghidra export at 0054f5c0. */

void sub_54F5C0(void)

{
  if (DAT_005846e4 == 3) {
    if (((byte)DAT_00584710 & 1) == 0) {
      if (DAT_00584e70 != 0) {
        DAT_00584e70 = DAT_00584e70 + -0x1000;
        sub_4268C0(1);
        return;
      }
      DAT_00584638 = 2;
    }
    sub_4268C0(1);
  }
  return;
}

