/* sub_41AFC0 @ 0041afc0   371 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint sub_41AFC0(void)

{
  uint uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  short *psVar5;
  uint uVar6;
  
  _DAT_00584bec = 0;
  _DAT_005849c8 = 3;
  DAT_00584eb4 = 1;
  if ((DAT_006d94b0 == '\0') || (DAT_0058500c == 8)) {
    DAT_00584bf0 = 0;
    DAT_00584bf4 = 0;
  }
  else {
    DAT_00584c0c = (short)DAT_0058500c + -1;
    DAT_005849a8 = 0;
    DAT_0057235a = (ushort)DAT_00585010;
    DAT_00584bf0 = 1;
    DAT_006d94b0 = '\0';
    DAT_00584bf4 = 0x1e;
  }
  iVar4 = (DAT_00585018 & 0xff) - 1;
  if (iVar4 < DAT_00584c0c) {
    DAT_00584c0c = ((ushort)DAT_00585018 & 0xff) - 1;
  }
  if ((DAT_00584c0c == iVar4) &&
     (uVar2 = (ushort)(DAT_00585018 >> 8) & 0xff, (short)uVar2 < (short)DAT_0057235a)) {
    DAT_0057235a = uVar2;
  }
  _DAT_00584bfc = 0;
  _DAT_00584c00 = 0;
  _DAT_00584a88 = 0;
  sub_415390(2);
  sub_43C220(s_TEST9_TLE_005724a8);
  _DAT_005849cc = 0;
  uVar6 = 0;
  psVar5 = &DAT_005849d6;
  do {
    iVar4 = sub_563C89();
    psVar5[-1] = (short)(iVar4 % 0x3200);
    iVar4 = sub_563C89();
    *psVar5 = (short)(iVar4 % 0xbe0) + 0x78;
    iVar4 = sub_563C89();
    psVar5[1] = -1 - (short)(iVar4 % 5);
    uVar3 = uVar6 / 3;
    psVar5[2] = 0;
    uVar1 = DAT_005849b0;
    if (uVar6 % 3 == 0) {
      *(undefined4 *)(psVar5 + -3) = DAT_005849b4;
    }
    else if (uVar6 % 3 == 1) {
      *(uint *)(psVar5 + -3) = DAT_005849b0;
      uVar3 = uVar1;
    }
    else {
      *(undefined4 *)(psVar5 + -3) = DAT_005849ac;
    }
    _DAT_005849cc = _DAT_005849cc + 1;
    psVar5 = psVar5 + 6;
    uVar6 = uVar6 + 1;
  } while ((int)psVar5 < 0x584a4e);
  return uVar3;
}

