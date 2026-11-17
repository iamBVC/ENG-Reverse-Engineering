/* sub_21109D50 @ 21109d50   44 bytes */

void __fastcall sub_21109D50(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_1[1]) {
    iVar1 = 0;
    do {
      *(undefined4 *)(iVar1 + *param_1) = 0;
      *(undefined4 *)(iVar1 + 8 + *param_1) = 0;
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0x14;
    } while (iVar2 < param_1[1]);
  }
  return;
}

