/* sub_546400 @ 00546400   86 bytes */

void sub_546400(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if (DAT_006d9498 != 0) {
    if ((((-1 < param_2) && (param_2 < *(int *)(DAT_006d9498 + 0x48))) &&
        (iVar1 = *(int *)(DAT_006d9498 + 0x44) + param_2 * 0x9c,
        *(int *)(*(int *)(DAT_006d9498 + 0x44) + 4 + param_2 * 0x9c) != 0)) &&
       ((*(int *)(iVar1 + 0x20) == param_1 && (*(int *)(iVar1 + 0x10) == 2)))) {
      sub_547E40(DAT_006d9498 + 0x10,4,iVar1,param_3);
    }
  }
  return;
}

