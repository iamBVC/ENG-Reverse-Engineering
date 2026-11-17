/* sub_5471F0 @ 005471f0   161 bytes */

void sub_5471F0(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  *(undefined1 *)(DAT_006d949c + 0x72) = 0;
  param_2 = param_2 + 6;
  uVar1 = sub_41EF00(param_3 * 4);
  *(undefined4 *)(DAT_006d949c + 0x68) = uVar1;
  if (*(int *)(DAT_006d949c + 0x68) != 0) {
    uVar3 = 0;
    if (param_3 != 0) {
      do {
        iVar2 = sub_41EF00(0x10c);
        if (iVar2 == 0) {
          return;
        }
        param_2 = sub_548A20(iVar2,param_2);
        *(int *)(*(int *)(DAT_006d949c + 0x68) + uVar3 * 4) = iVar2;
        uVar3 = uVar3 + 1;
        *(int *)(iVar2 + 0x38) = (param_1 + 5) * 0x10 + DAT_006d949c;
      } while (uVar3 < param_3);
    }
    *(char *)(DAT_006d949c + 0x72) = (char)param_3;
  }
  return;
}

