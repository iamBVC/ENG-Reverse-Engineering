/* Selected Ghidra export at 0054fc40. */

void sub_54FC40(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  piVar1 = (int *)*param_1;
  iVar2 = *piVar1;
  piVar4 = piVar1 + 1;
  *param_1 = (int)piVar4;
  iVar3 = *piVar4;
  *param_1 = (int)(piVar1 + 2);
  iVar3 = iVar3 * 0x10;
  *(int *)(param_1[0x3e] + iVar3) = piVar4[iVar2];
  *(int *)(param_1[0x3e] + 4 + iVar3) = piVar1[iVar2 + 2];
  *(int *)(param_1[0x3e] + 8 + iVar3) = *param_1 + -4 + (piVar1 + iVar2 + 2)[1] * 4;
  *(undefined4 *)(param_1[0x3e] + iVar3 + 0xc) = *(undefined4 *)(param_1[0x3e] + iVar3 + 4);
  piVar4 = (int *)(param_1[0x3e] + iVar3);
  if (*piVar4 == 0x40) {
    piVar4[1] = piVar4[1] - 1U >> 0xc;
  }
  if ((*(int *)(param_1[0x3e] + iVar3) == 0x80) || (*(int *)(param_1[0x3e] + iVar3) == 0x100)) {
    param_1[0x3b] = param_1[0x3b] | 0x4000;
  }
  return;
}

