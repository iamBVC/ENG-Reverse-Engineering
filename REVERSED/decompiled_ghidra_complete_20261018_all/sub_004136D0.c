/* sub_4136D0 @ 004136d0   37 bytes */

int sub_4136D0(int param_1,int param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xc);
  if (*param_3 < iVar1) {
    return *(int *)(param_2 + 0xc) - iVar1;
  }
  return iVar1 - *(int *)(param_2 + 0xc);
}

