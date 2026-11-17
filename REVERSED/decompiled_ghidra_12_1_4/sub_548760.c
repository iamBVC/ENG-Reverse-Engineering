/* sub_548760 @ 00548760   61 bytes */

undefined4 sub_548760(int param_1,uint param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  if ((param_2 & 0x80) == 0) {
    if (*(uint *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x50) + 4) <= param_2) {
      return 0;
    }
    iVar1 = *(int *)(PTR_DAT_00571f58 + 0x18);
    if (iVar1 == 0) {
      return 0;
    }
  }
  else {
    iVar1 = *(int *)(*(int *)(param_1 + 0x3c) + 0x44);
    if (iVar1 == 0) {
      return 0;
    }
    param_2 = param_2 & 0x7f;
  }
  return *(undefined4 *)(iVar1 + param_2 * 4);
}

