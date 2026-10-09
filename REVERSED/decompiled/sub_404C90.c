/* sub_404C90 @ 00404c90   39 bytes */

int sub_404C90(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1 - *param_2 >> 6;
  iVar2 = param_1[2] - param_2[2] >> 6;
  return iVar1 * iVar1 + iVar2 * iVar2;
}

