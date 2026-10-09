/* sub_4137B0 @ 004137b0   28 bytes */

int sub_4137B0(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0xc);
  iVar2 = *param_2;
  if (iVar1 == iVar2) {
    iVar1 = *(int *)(param_1 + 0x10);
    iVar2 = param_2[1];
  }
  return iVar1 - iVar2;
}

