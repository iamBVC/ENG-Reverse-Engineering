/* sub_412940 @ 00412940   197 bytes */

undefined4 sub_412940(undefined1 *param_1,int param_2)

{
  undefined1 uVar1;
  
  if (((*(uint *)(param_2 + 4) & 0x8000) == 0) || ((*(byte *)(param_2 + 0x18) & 4) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *param_1 = uVar1;
  param_1[1] = (byte)(*(uint *)(param_2 + 0x18) >> 10) & 1;
  param_1[2] = (byte)(*(uint *)(param_2 + 8) >> 0x11) & 1;
  param_1[3] = (byte)(*(uint *)(param_2 + 0xac) >> 6) & 1;
  if (((*(uint *)(param_2 + 0xb4) & 0xc000) == 0) || ((*(uint *)(param_2 + 0xb4) & 0x30000) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  param_1[4] = uVar1;
  if (((*(uint *)(param_2 + 0xb4) & 0x4000) == 0) || ((*(uint *)(param_2 + 0xb4) & 0x10000) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  param_1[5] = uVar1;
  if (((*(uint *)(param_2 + 0xb4) & 0xc00) == 0) || ((*(uint *)(param_2 + 0xb4) & 0x3000) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  param_1[6] = uVar1;
  if (((*(uint *)(param_2 + 0xb4) & 0x400) != 0) && ((*(uint *)(param_2 + 0xb4) & 0x1000) != 0)) {
    param_1[7] = 1;
    return 1;
  }
  param_1[7] = 0;
  return 1;
}

