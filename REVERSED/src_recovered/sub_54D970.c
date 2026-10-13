/* Selected Ghidra export at 0054d970. */

void sub_54D970(int *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  if (iVar1 != 0) {
    sub_4155B0();
    return;
  }
  sub_4155E0();
  return;
}

