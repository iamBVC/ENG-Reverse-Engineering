/* sub_5463B0 @ 005463b0   76 bytes */

void sub_5463B0(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (DAT_006d9498 != 0) {
    if ((((-1 < param_2) && (param_2 < *(int *)(DAT_006d9498 + 0x48))) &&
        (iVar1 = *(int *)(DAT_006d9498 + 0x44) + param_2 * 0x9c,
        *(int *)(*(int *)(DAT_006d9498 + 0x44) + 4 + param_2 * 0x9c) != 0)) &&
       (*(int *)(iVar1 + 0x20) == param_1)) {
      *(undefined4 *)(iVar1 + 0x34) = param_3;
      *(undefined4 *)(iVar1 + 0x38) = param_4;
    }
  }
  return;
}

