/* sub_436A80 @ 00436a80   480 bytes */

void sub_436A80(byte *param_1,int param_2,int param_3,uint param_4,char param_5)

{
  byte bVar1;
  byte *pbVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint local_10;
  uint local_c;
  undefined4 local_8;
  uint local_4;
  
  uVar3 = (undefined1)param_4;
  uVar7 = 0;
  local_c = CONCAT31(local_c._1_3_,(undefined1)param_4);
  local_10 = CONCAT31(local_10._1_3_,(undefined1)param_4);
  uVar4 = sub_40C510(&param_4,&local_10,&local_c);
  local_8 = CONCAT31(local_8._1_3_,uVar4);
  bVar1 = *param_1;
  uVar6 = ((param_4 & 0xff | 0xffffff00) << 8 | local_10 & 0xff) << 8 | local_c & 0xff;
  local_4 = CONCAT31(local_4._1_3_,1);
  iVar5 = DAT_006da354;
  pbVar2 = param_1;
  while ((bVar1 != 0 && (param_5 != '\0'))) {
    param_5 = param_5 + -1;
    if (uVar7 == 0x3a) {
      param_4._1_3_ = (undefined3)(param_4 >> 8);
      param_4 = CONCAT31(param_4._1_3_,uVar3);
      local_c._1_3_ = (undefined3)(local_c >> 8);
      local_c = CONCAT31(local_c._1_3_,uVar3);
      local_10._1_3_ = (undefined3)(local_10 >> 8);
      local_10 = CONCAT31(local_10._1_3_,uVar3);
      uVar4 = sub_40C510(&param_4,&local_10,&local_c);
      local_8 = CONCAT31(local_8._1_3_,uVar4);
      local_4 = CONCAT31(local_4._1_3_,1);
      uVar6 = ((param_4 & 0xff | 0xffffff00) << 8 | local_10 & 0xff) << 8 | local_c & 0xff;
      iVar5 = DAT_006da354;
    }
    uVar7 = (uint)*pbVar2;
    param_1 = pbVar2 + 1;
    if (uVar7 == 0x3d) {
      param_4 = CONCAT31(param_4._1_3_,uVar3);
      local_c = local_c & 0xffffff00;
      local_10 = local_10 & 0xffffff00;
      uVar4 = sub_40C510(&param_4,&local_10,&local_c);
      local_8 = CONCAT31(local_8._1_3_,uVar4);
      local_4 = local_4 & 0xffffff00;
      uVar6 = ((param_4 & 0xff | 0xffffff00) << 8 | local_10 & 0xff) << 8 | local_c & 0xff;
      iVar5 = DAT_006da354;
    }
    else if (uVar7 == 0x23) {
      param_1 = pbVar2 + 4;
    }
    else if (uVar7 == 0x20) {
      param_2 = param_2 + 10;
    }
    else {
      sub_435D10(*(undefined2 *)(iVar5 + uVar7 * 8),param_2,
                 param_3 - (uint)(*(ushort *)(iVar5 + 2 + uVar7 * 8) >> 1),
                 *(undefined2 *)(iVar5 + 4 + uVar7 * 8),*(undefined2 *)(iVar5 + 6 + uVar7 * 8),uVar6
                 ,local_4,local_8,0);
      param_2 = param_2 + (uint)*(ushort *)(DAT_006da354 + 4 + uVar7 * 8);
      iVar5 = DAT_006da354;
    }
    bVar1 = *param_1;
    pbVar2 = param_1;
  }
  return;
}

