/* sub_4137D0 @ 004137d0   67 bytes */

int sub_4137D0(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0xc);
  iVar2 = *(int *)(param_2 + 0xc);
  if (iVar1 == iVar2) {
    iVar1 = *(int *)(param_1 + 0x10);
    if (param_3[1] < iVar1) {
      return *(int *)(param_2 + 0x10) - iVar1;
    }
    return iVar1 - *(int *)(param_2 + 0x10);
  }
  if (*param_3 < iVar1) {
    return iVar2 - iVar1;
  }
  return iVar1 - iVar2;
}

