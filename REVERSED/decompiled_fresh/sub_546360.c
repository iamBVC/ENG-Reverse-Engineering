/* sub_546360 @ 00546360   71 bytes */

void sub_546360(int param_1,int param_2,undefined2 param_3)

{
  int iVar1;
  
  if (DAT_006d9498 != 0) {
    if ((((-1 < param_2) && (param_2 < *(int *)(DAT_006d9498 + 0x48))) &&
        (iVar1 = *(int *)(DAT_006d9498 + 0x44) + param_2 * 0x9c,
        *(int *)(*(int *)(DAT_006d9498 + 0x44) + 4 + param_2 * 0x9c) != 0)) &&
       (*(int *)(iVar1 + 0x20) == param_1)) {
      *(undefined2 *)(iVar1 + 0x6a) = param_3;
    }
  }
  return;
}

