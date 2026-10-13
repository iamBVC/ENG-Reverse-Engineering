/* Selected Ghidra export at 0054db00. */

void sub_54DB00(void)

{
  if (DAT_006d9e40 != 0) {
    DAT_006d9e30 = (&DAT_006d9dc8)[DAT_006d9e40];
    DAT_006d9e40 = DAT_006d9e40 + -2;
    DAT_006d9e28 = *(undefined4 *)(&DAT_006d9dcc + DAT_006d9e40 * 4);
    DAT_006d9d34 = DAT_006d9d34 + 1;
  }
  return;
}

