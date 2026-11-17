/* sub_54F390 @ 0054f390   95 bytes */

void sub_54F390(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  piVar1 = *(int **)(param_1 + 0x120);
  iVar2 = *piVar1;
  if (iVar2 == 0) {
    iVar2 = *(int *)(param_1 + 0x118);
  }
  iVar3 = piVar1[6];
  iVar6 = piVar1[8];
  iVar5 = *(int *)(iVar2 + 0x18);
  iVar2 = *(int *)(iVar2 + 0x20);
  iVar4 = iVar3;
  if (iVar5 < iVar3) {
    iVar4 = iVar5;
    iVar5 = iVar3;
  }
  iVar3 = iVar2;
  if (iVar6 < iVar2) {
    iVar3 = iVar6;
    iVar6 = iVar2;
  }
  if (*(int *)(param_1 + 0x30) < iVar4) {
    *(int *)(param_1 + 0x30) = iVar4;
  }
  if (iVar5 < *(int *)(param_1 + 0x30)) {
    *(int *)(param_1 + 0x30) = iVar5;
  }
  if (*(int *)(param_1 + 0x38) < iVar3) {
    *(int *)(param_1 + 0x38) = iVar3;
  }
  if (iVar6 < *(int *)(param_1 + 0x38)) {
    *(int *)(param_1 + 0x38) = iVar6;
  }
  return;
}

