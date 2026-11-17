/* sub_54C3F0 @ 0054c3f0   74 bytes */

void sub_54C3F0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(DAT_006d9e1c + 0x30);
  iVar2 = *(int *)(DAT_006d9e1c + 0x34);
  iVar3 = *(int *)(DAT_006d9e1c + 0x38);
  *(undefined4 *)(param_1 + 0x1c) = 0;
  iVar2 = iVar2 - *(int *)(param_1 + 0x34) >> 6;
  iVar3 = iVar3 - *(int *)(param_1 + 0x38) >> 6;
  iVar1 = iVar1 - *(int *)(param_1 + 0x30) >> 6;
  *(int *)(param_1 + 0x148) = iVar3 * iVar3 + iVar2 * iVar2 + iVar1 * iVar1;
  return;
}

