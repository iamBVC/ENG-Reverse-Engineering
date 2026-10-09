/* sub_404C10 @ 00404c10   63 bytes */

int sub_404C10(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *param_1 - *param_2 >> 6;
  iVar2 = param_1[1] - param_2[1] >> 6;
  iVar3 = param_1[2] - param_2[2] >> 6;
  return iVar2 * iVar2 + iVar3 * iVar3 + iVar1 * iVar1;
}

