/* sub_414160 @ 00414160   512 bytes */

int __thiscall sub_414160(int param_1,int param_2,uint param_3,uint param_4)

{
  char cVar1;
  uint uVar2;
  undefined *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  if (*(uint *)(param_2 + 8) < param_3) {
    sub_56D2CC();
  }
  uVar4 = DAT_0056e1e0;
  uVar6 = *(uint *)(param_2 + 8) - param_3;
  if (param_4 < uVar6) {
    uVar6 = param_4;
  }
  if (param_1 == param_2) {
    uVar6 = uVar6 + param_3;
    if (*(uint *)(param_1 + 8) < uVar6) {
      sub_56D2CC();
    }
    sub_414390();
    uVar2 = *(int *)(param_1 + 8) - uVar6;
    if (uVar2 < uVar4) {
      uVar4 = uVar2;
    }
    if (uVar4 != 0) {
      iVar5 = *(int *)(param_1 + 4) + uVar6;
      sub_563580(iVar5,iVar5 + uVar4,uVar2 - uVar4);
      iVar5 = *(int *)(param_1 + 8) - uVar4;
      cVar1 = sub_413F10(iVar5,0);
      if (cVar1 != '\0') {
        *(int *)(param_1 + 8) = iVar5;
        *(undefined1 *)(iVar5 + *(int *)(param_1 + 4)) = 0;
      }
    }
    sub_414390();
    uVar4 = *(uint *)(param_1 + 8);
    if (uVar4 < param_3) {
      param_3 = uVar4;
    }
    if (param_3 == 0) {
      return param_1;
    }
    sub_563580(*(int *)(param_1 + 4),*(int *)(param_1 + 4) + param_3,uVar4 - param_3);
    iVar5 = *(int *)(param_1 + 8) - param_3;
    cVar1 = sub_413F10(iVar5,0);
    if (cVar1 == '\0') {
      return param_1;
    }
    sub_414360(iVar5);
    return param_1;
  }
  if ((uVar6 != 0) && (uVar6 == *(uint *)(param_2 + 8))) {
    puVar3 = *(undefined **)(param_2 + 4);
    if (puVar3 == (undefined *)0x0) {
      puVar3 = &DAT_0056e1bc;
    }
    if ((byte)puVar3[-1] < 0xfe) {
      iVar5 = *(int *)(param_1 + 4);
      if (iVar5 != 0) {
        cVar1 = *(char *)(iVar5 + -1);
        if ((cVar1 == '\0') || (cVar1 == -1)) {
          sub_562941((char *)(iVar5 + -1));
        }
        else {
          *(char *)(iVar5 + -1) = cVar1 + -1;
        }
      }
      *(undefined4 *)(param_1 + 4) = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined4 *)(param_1 + 0xc) = 0;
      puVar3 = *(undefined **)(param_2 + 4);
      if (puVar3 == (undefined *)0x0) {
        puVar3 = &DAT_0056e1bc;
      }
      *(undefined **)(param_1 + 4) = puVar3;
      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
      *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
      puVar3[-1] = puVar3[-1] + '\x01';
      return param_1;
    }
  }
  uVar4 = sub_414380();
  if (uVar4 < uVar6) {
    sub_56D0A0();
  }
  iVar5 = *(int *)(param_1 + 4);
  if (((iVar5 == 0) || (cVar1 = *(char *)(iVar5 + -1), cVar1 == '\0')) || (cVar1 == -1)) {
    if (uVar6 == 0) {
      sub_413BF0(1);
      return param_1;
    }
    if ((*(uint *)(param_1 + 0xc) < 0x20) && (uVar6 <= *(uint *)(param_1 + 0xc))) goto LAB_0041432c;
    sub_413BF0(1);
  }
  else if (uVar6 == 0) {
    *(char *)(iVar5 + -1) = cVar1 + -1;
    sub_413BF0(0);
    return param_1;
  }
  sub_413C40(uVar6);
LAB_0041432c:
  puVar3 = *(undefined **)(param_2 + 4);
  if (puVar3 == (undefined *)0x0) {
    puVar3 = &DAT_0056e1bc;
  }
  puVar7 = (undefined4 *)(puVar3 + param_3);
  puVar8 = *(undefined4 **)(param_1 + 4);
  for (uVar4 = uVar6 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  for (uVar4 = uVar6 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  }
  *(uint *)(param_1 + 8) = uVar6;
  *(undefined1 *)(uVar6 + *(int *)(param_1 + 4)) = 0;
  return param_1;
}

