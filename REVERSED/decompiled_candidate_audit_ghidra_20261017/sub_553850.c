/* Selected Ghidra export at 00553850. */

void sub_553850(int *param_1)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  for (; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar1 = (uint *)*param_1;
    uVar2 = *puVar1;
    *param_1 = (int)(puVar1 + 1);
    if (((uVar2 & 0xffff) == 0x45) || ((uVar2 & 0xffff) == 0xea)) {
      *param_1 = (int)(puVar1 + 2);
    }
  }
  return;
}

