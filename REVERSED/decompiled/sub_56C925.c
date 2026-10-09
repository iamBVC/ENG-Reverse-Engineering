/* sub_56C925 @ 0056c925   301 bytes */

undefined4 sub_56C925(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  code *pcVar6;
  
  iVar2 = param_1;
  if (param_1 == 2) {
    puVar3 = &DAT_006da594;
    pcVar6 = DAT_006da594;
  }
  else if (((param_1 == 4) || (param_1 == 8)) || (param_1 == 0xb)) {
    iVar4 = sub_56CA52(param_1);
    pcVar6 = *(code **)(iVar4 + 8);
    puVar3 = (undefined4 *)(iVar4 + 8);
  }
  else if (param_1 == 0xf) {
    puVar3 = &DAT_006da5a0;
    pcVar6 = DAT_006da5a0;
  }
  else if (param_1 == 0x15) {
    puVar3 = &DAT_006da598;
    pcVar6 = DAT_006da598;
  }
  else {
    if (param_1 != 0x16) {
      return 0xffffffff;
    }
    puVar3 = &DAT_006da59c;
    pcVar6 = DAT_006da59c;
  }
  iVar1 = DAT_006da434;
  iVar4 = DAT_0057cf64;
  if (pcVar6 == (code *)0x1) {
    return 0;
  }
  if (pcVar6 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  if (((param_1 == 8) || (param_1 == 0xb)) || (iVar5 = param_1, param_1 == 4)) {
    DAT_006da434 = 0;
    iVar5 = iVar1;
    if (param_1 == 8) {
      DAT_0057cf64 = 0x8c;
      param_1 = iVar4;
      goto LAB_0056c9e9;
    }
LAB_0056ca15:
    *puVar3 = 0;
    if (iVar2 != 8) {
      (*pcVar6)(iVar2);
      if ((iVar2 != 0xb) && (iVar2 != 4)) {
        return 0;
      }
      goto LAB_0056ca38;
    }
  }
  else {
LAB_0056c9e9:
    if (iVar2 != 8) goto LAB_0056ca15;
    if (DAT_0057cf58 < DAT_0057cf5c + DAT_0057cf58) {
      iVar4 = (DAT_0057cf5c + DAT_0057cf58) - DAT_0057cf58;
      puVar3 = (undefined4 *)(DAT_0057cf58 * 0xc + 0x57cee8);
      do {
        *puVar3 = 0;
        puVar3 = puVar3 + 3;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  (*pcVar6)(8,DAT_0057cf64);
LAB_0056ca38:
  if (iVar2 == 8) {
    DAT_0057cf64 = param_1;
  }
  DAT_006da434 = iVar5;
  return 0;
}

