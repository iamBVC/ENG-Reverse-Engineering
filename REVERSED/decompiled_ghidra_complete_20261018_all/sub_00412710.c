/* sub_412710 @ 00412710 546 bytes */
/* Selected Ghidra export at 00412710. */

undefined4 sub_412710(undefined4 *param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  char *pcVar7;
  undefined4 *puVar8;
  char acStack_100 [256];
  
  uVar3 = param_1[1];
  if ((uVar3 & 0x20) == 0) {
    if ((uVar3 & 0x40) == 0) {
      uVar3 = 0xffffffff;
      pcVar5 = s_unknown_format_00571cbc;
      do {
        pcVar7 = pcVar5;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar7 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar7;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      pcVar5 = pcVar7 + -uVar3;
      pcVar7 = acStack_100;
      for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar7 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar7 = pcVar7 + 1;
      }
    }
    else {
      uVar2 = param_1[6];
      if ((uVar3 & 1) == 0) {
        for (; uVar2 != 0; uVar2 = uVar2 >> 1) {
        }
        for (uVar3 = param_1[5]; uVar3 != 0; uVar3 = uVar3 >> 1) {
        }
        for (uVar3 = param_1[4]; uVar3 != 0; uVar3 = uVar3 >> 1) {
        }
        sub_562717(acStack_100);
      }
      else {
        for (; uVar2 != 0; uVar2 = uVar2 >> 1) {
        }
        for (uVar3 = param_1[5]; uVar3 != 0; uVar3 = uVar3 >> 1) {
        }
        for (uVar3 = param_1[4]; uVar3 != 0; uVar3 = uVar3 >> 1) {
        }
        for (uVar3 = param_1[7]; uVar3 != 0; uVar3 = uVar3 >> 1) {
        }
        sub_562717(acStack_100,s_argb__d_d_d_d_00571cd8);
      }
    }
  }
  else {
    sub_562717();
  }
  if (DAT_005834d4 != 0) {
    sub_562B75();
    if (&stack0x00000000 != (undefined1 *)0x100) {
      iVar4 = -1;
      pcVar5 = acStack_100;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      sub_562B75();
    }
    if (param_1 != (undefined4 *)0x0) {
      sub_562B75();
    }
  }
  cVar1 = sub_412D70();
  if (cVar1 != '\0') {
    puVar6 = param_1;
    puVar8 = (undefined4 *)(*(int *)(param_2 + 8) + 0x58);
    for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
  }
  cVar1 = sub_412D90();
  if (cVar1 != '\0') {
    puVar6 = param_1;
    puVar8 = (undefined4 *)(*(int *)(param_2 + 8) + 0x78);
    for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
  }
  cVar1 = sub_412F10();
  if (cVar1 != '\0') {
    puVar6 = param_1;
    puVar8 = (undefined4 *)(*(int *)(param_2 + 8) + 0x98);
    for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
  }
  cVar1 = sub_412FF0();
  if (cVar1 != '\0') {
    puVar6 = (undefined4 *)(*(int *)(param_2 + 8) + 0xb8);
    for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *param_1;
      param_1 = param_1 + 1;
      puVar6 = puVar6 + 1;
    }
  }
  return 1;
}

