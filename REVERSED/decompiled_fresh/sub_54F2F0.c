/* sub_54F2F0 @ 0054f2f0   149 bytes */

void sub_54F2F0(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  piVar1 = *(int **)(param_1 + 0x120);
  iVar2 = *piVar1;
  if (iVar2 == 0) {
    iVar2 = *(int *)(param_1 + 0x118);
  }
  iVar3 = *(int *)(iVar2 + 0x20);
  iVar6 = piVar1[8];
  iVar5 = piVar1[6];
  iVar2 = *(int *)(iVar2 + 0x18);
  iVar7 = iVar5;
  if (iVar2 < iVar5) {
    iVar7 = iVar2;
    iVar2 = iVar5;
  }
  iVar5 = iVar3;
  if (iVar6 < iVar3) {
    iVar5 = iVar6;
    iVar6 = iVar3;
  }
  iVar3 = sub_54BC00(param_1);
  iVar4 = sub_54BC00(param_1);
  if ((((iVar7 <= iVar4) && (iVar4 <= iVar2)) && (iVar5 <= iVar3)) && (iVar3 <= iVar6)) {
    sub_54BBD0(param_1,1);
    return;
  }
  sub_54BBD0(param_1,0);
  return;
}

