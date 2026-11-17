/* Selected Ghidra export at 00554280. */

void sub_554280(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  uStack_8 = sub_54BC00(param_1);
  uStack_c = sub_54BC00(param_1);
  uStack_10 = sub_54BC00(param_1);
  iVar2 = 0;
  uVar3 = 0;
  uVar5 = 1000000;
  iVar4 = DAT_00586598;
  if (DAT_005865d0 != 0) {
    do {
      if (*(char *)(iVar4 + 0xf) == '\x02') {
        uVar1 = sub_404C10(iVar4,&uStack_10);
        if (uVar1 < uVar5) {
          iVar2 = iVar4;
          uVar5 = uVar1;
        }
      }
      iVar4 = iVar4 + 0x1c;
      uVar3 = uVar3 + 1;
    } while (uVar3 < DAT_005865d0);
  }
  sub_54BBD0(param_1,iVar2);
  return;
}

