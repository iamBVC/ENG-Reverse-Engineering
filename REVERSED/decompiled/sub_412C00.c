/* sub_412C00 @ 00412c00   169 bytes */

undefined4 sub_412C00(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if (((((*(uint *)(param_3 + 4) & 0x1006) == 0x1006) && (0x13f < *(uint *)(param_3 + 0xc))) &&
      (199 < *(uint *)(param_3 + 8))) && ((*(uint *)(param_3 + 0x4c) & 0x40) != 0)) {
    if (param_2 == 0) {
      if (((*(uint *)(param_3 + 0x4c) == 0x40) && (*(int *)(param_3 + 0x54) == 0x10)) &&
         (((*(int *)(param_3 + 0x58) == 0x7c00 && (*(int *)(param_3 + 0x5c) == 0x3e0)) ||
          ((*(int *)(param_3 + 0x58) == 0xf800 && (*(int *)(param_3 + 0x5c) == 0x7e0)))))) {
        if (*(int *)(param_3 + 0x60) == 0x1f) {
          return 1;
        }
        return 0;
      }
    }
    else {
      iVar1 = *(int *)(param_3 + 0x54);
      if (iVar1 == 0x10) {
        uVar2 = *(uint *)(param_2 + 0x9c) & 0x400;
      }
      else if (iVar1 == 0x18) {
        uVar2 = *(uint *)(param_2 + 0x9c) & 0x200;
      }
      else {
        if (iVar1 != 0x20) {
          return 0;
        }
        uVar2 = *(uint *)(param_2 + 0x9c) & 0x100;
      }
      if (uVar2 != 0) {
        return 1;
      }
    }
  }
  return 0;
}

