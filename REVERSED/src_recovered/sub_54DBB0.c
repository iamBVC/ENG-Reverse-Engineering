/* Selected Ghidra export at 0054dbb0. */

void sub_54DBB0(void)

{
  undefined4 uVar1;
  
  uVar1 = DAT_006d9e30;
  *(undefined4 *)(&DAT_006d9dcc + DAT_006d9e40 * 4) = DAT_006d9e28;
  *(undefined4 *)(&DAT_006d9dcc + (DAT_006d9e40 + 1) * 4) = uVar1;
  DAT_006d9e40 = DAT_006d9e40 + 2;
  return;
}

