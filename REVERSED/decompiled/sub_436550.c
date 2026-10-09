/* sub_436550 @ 00436550   458 bytes */

void sub_436550(byte *param_1,int param_2,uint param_3,uint param_4,uint param_5,uint param_6,
               undefined4 param_7,uint param_8)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  undefined1 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  uint uVar12;
  undefined4 local_c;
  
  uVar12 = 0;
  uVar10 = 0x100;
  uVar4 = sub_40C510(&param_3,&param_4,&param_5);
  if (((char)param_3 != (char)param_4) || (local_c = 1, (char)param_4 != (char)param_5)) {
    local_c = 0;
  }
  uVar5 = param_3 & 0xff;
  uVar7 = param_4 & 0xff;
  uVar9 = param_5 & 0xff;
  bVar1 = *param_1;
  pbVar11 = param_1;
  bVar2 = bVar1;
  while (bVar2 != 0) {
    bVar2 = *pbVar11;
    pbVar11 = pbVar11 + 1;
    if (bVar2 == 0x20) {
      uVar12 = uVar12 + 10;
    }
    else {
      uVar12 = uVar12 + *(ushort *)(DAT_006da354 + 4 + (uint)bVar2 * 8);
    }
    bVar2 = *pbVar11;
  }
  uVar3 = uVar12;
  iVar8 = DAT_006da354;
  switch(param_7) {
  case 0:
    uVar3 = (param_6 >> 1) - (uVar12 >> 1);
    break;
  case 1:
    uVar3 = (((param_6 >> 1) - (uVar12 >> 1)) - param_6) + 0x200;
    break;
  case 2:
    uVar3 = param_8;
    if ((0x200 < uVar12 + param_8) && (param_8 < 0x200)) {
      uVar10 = (param_8 * -0x100 + 0x20000) / uVar12;
    }
    break;
  case 4:
    uVar3 = ((param_6 >> 1) - (uVar12 >> 1)) + 0x60;
    break;
  case 5:
    uVar12 = uVar12 >> 1;
  case 3:
    uVar3 = param_8 - uVar12;
    break;
  case 6:
    uVar3 = param_8;
  }
  while (bVar1 != 0) {
    uVar12 = (uint)bVar1;
    param_1 = param_1 + 1;
    if (uVar12 == 0x20) {
      iVar6 = uVar10 * 10;
    }
    else {
      iVar6 = *(ushort *)(iVar8 + 4 + uVar12 * 8) * uVar10;
      sub_435D10(*(undefined2 *)(iVar8 + uVar12 * 8),uVar3,
                 param_2 - (uint)(*(ushort *)(iVar8 + 2 + uVar12 * 8) >> 1),
                 (int)(iVar6 + (iVar6 >> 0x1f & 0xffU)) >> 8,*(undefined2 *)(iVar8 + 6 + uVar12 * 8)
                 ,((uVar5 | 0xffffff00) << 8 | uVar7) << 8 | uVar9,local_c,uVar4,0);
      iVar6 = *(ushort *)(DAT_006da354 + 4 + uVar12 * 8) * uVar10;
      iVar8 = DAT_006da354;
    }
    uVar3 = uVar3 + ((int)(iVar6 + (iVar6 >> 0x1f & 0xffU)) >> 8);
    bVar1 = *param_1;
  }
  return;
}

