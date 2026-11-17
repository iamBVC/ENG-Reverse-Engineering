/* sub_437290 @ 00437290   157 bytes */

int sub_437290(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = (param_1[3] + param_1[5] * 0x21) * 0x21;
  iVar1 = param_1[1];
  iVar2 = *param_1;
  iVar4 = (param_1[4] * 0x21 + param_1[3]) * 0x21;
  iVar5 = (param_1[5] * 0x21 + param_1[2]) * 0x21;
  iVar6 = (param_1[4] * 0x21 + param_1[2]) * 0x21;
  return ((((*(int *)(param_2 + (iVar2 + iVar5) * 4) - *(int *)(param_2 + (iVar6 + iVar2) * 4)) -
           *(int *)(param_2 + (iVar2 + iVar3) * 4)) - *(int *)(param_2 + (iVar5 + iVar1) * 4)) -
         *(int *)(param_2 + (iVar4 + iVar1) * 4)) + *(int *)(param_2 + (iVar2 + iVar4) * 4) +
         *(int *)(param_2 + (iVar6 + iVar1) * 4) + *(int *)(param_2 + (iVar1 + iVar3) * 4);
}

