/* sub_5670C5 @ 005670c5   368 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * sub_5670C5(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 *param_4)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  bVar4 = false;
  bVar3 = false;
  cVar1 = *param_2;
  if (cVar1 == 'a') {
    uVar6 = 0x109;
  }
  else {
    if (cVar1 == 'r') {
      uVar6 = 0;
      uVar7 = DAT_006da57c | 1;
      goto LAB_00567106;
    }
    if (cVar1 != 'w') {
      return (undefined4 *)0x0;
    }
    uVar6 = 0x301;
  }
  uVar7 = DAT_006da57c | 2;
LAB_00567106:
  bVar2 = true;
LAB_00567109:
  cVar1 = param_2[1];
  param_2 = param_2 + 1;
  if ((cVar1 == '\0') || (!bVar2)) {
    iVar5 = sub_56A77A(param_1,uVar6,param_3,0x1a4);
    if (iVar5 < 0) {
      return (undefined4 *)0x0;
    }
    _DAT_006da41c = _DAT_006da41c + 1;
    param_4[3] = uVar7;
    param_4[1] = 0;
    *param_4 = 0;
    param_4[2] = 0;
    param_4[7] = 0;
    param_4[4] = iVar5;
    return param_4;
  }
  if (cVar1 < 'U') {
    if (cVar1 == 'T') {
      if ((uVar6 & 0x1000) == 0) {
        uVar6 = uVar6 | 0x1000;
        goto LAB_00567109;
      }
    }
    else if (cVar1 == '+') {
      if ((uVar6 & 2) == 0) {
        uVar6 = uVar6 & 0xfffffffe | 2;
        uVar7 = uVar7 & 0xfffffffc | 0x80;
        goto LAB_00567109;
      }
    }
    else if (cVar1 == 'D') {
      if ((uVar6 & 0x40) == 0) {
        uVar6 = uVar6 | 0x40;
        goto LAB_00567109;
      }
    }
    else if (cVar1 == 'R') {
      if (!bVar3) {
        bVar3 = true;
        uVar6 = uVar6 | 0x10;
        goto LAB_00567109;
      }
    }
    else if ((cVar1 == 'S') && (!bVar3)) {
      bVar3 = true;
      uVar6 = uVar6 | 0x20;
      goto LAB_00567109;
    }
  }
  else {
    if (cVar1 == 'b') {
      if ((uVar6 & 0xc000) != 0) goto LAB_005671e9;
      uVar6 = uVar6 | 0x8000;
      goto LAB_00567109;
    }
    if (cVar1 == 'c') {
      if (!bVar4) {
        bVar4 = true;
        uVar7 = uVar7 | 0x4000;
        goto LAB_00567109;
      }
    }
    else {
      if (cVar1 != 'n') {
        if ((cVar1 != 't') || ((uVar6 & 0xc000) != 0)) goto LAB_005671e9;
        uVar6 = uVar6 | 0x4000;
        goto LAB_00567109;
      }
      if (!bVar4) {
        bVar4 = true;
        uVar7 = uVar7 & 0xffffbfff;
        goto LAB_00567109;
      }
    }
  }
LAB_005671e9:
  bVar2 = false;
  goto LAB_00567109;
}

