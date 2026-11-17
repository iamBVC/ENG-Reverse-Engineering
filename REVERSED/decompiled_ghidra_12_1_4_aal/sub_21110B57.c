/* sub_21110B57 @ 21110b57   1185 bytes */

undefined4 __thiscall
sub_21110B57(void *this,ushort *param_1,int *param_2,byte *param_3,int param_4,int param_5,
            int param_6,int param_7)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  byte bVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  byte *pbVar10;
  char local_60 [23];
  char local_49;
  ushort local_44;
  undefined2 uStack_42;
  undefined2 uStack_40;
  byte *local_3e;
  ushort local_3a;
  int local_34;
  int local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  byte *local_20;
  int local_1c;
  undefined4 local_18;
  int local_14;
  char *local_10;
  int local_c;
  uint local_8;
  
  local_10 = local_60;
  local_2c = 0;
  local_1c = 1;
  local_8 = 0;
  local_14 = 0;
  local_28 = 0;
  local_24 = 0;
  local_30 = 0;
  local_34 = 0;
  local_20 = (byte *)0x0;
  local_c = 0;
  local_18 = 0;
  pbVar8 = param_3;
  while( true ) {
    bVar6 = *pbVar8;
    this = (void *)CONCAT31((int3)((uint)this >> 8),bVar6);
    if ((((bVar6 != 0x20) && (bVar6 != 9)) && (bVar6 != 10)) && (bVar6 != 0xd)) break;
    pbVar8 = pbVar8 + 1;
  }
  iVar1 = 4;
  iVar9 = 0;
  iVar5 = local_14;
LAB_21110bae:
  local_14 = iVar5;
  pbVar7 = pbVar8;
  iVar5 = 1;
  bVar6 = *pbVar7;
  pbVar8 = pbVar7 + 1;
  iVar2 = local_14;
  switch(iVar9) {
  case 0:
    if (('0' < (char)bVar6) && ((char)bVar6 < ':')) {
LAB_21110bcb:
      local_14 = iVar2;
      iVar9 = 3;
      goto LAB_21110df0;
    }
    if (bVar6 == DAT_21114ed0) goto LAB_21110bda;
    if (bVar6 == 0x2b) {
      local_2c = 0;
      iVar9 = 2;
      iVar5 = local_14;
    }
    else if (bVar6 == 0x2d) {
      local_2c = 0x8000;
      iVar9 = 2;
      iVar5 = local_14;
    }
    else {
      iVar9 = iVar5;
      iVar5 = local_14;
      if (bVar6 != 0x30) goto LAB_21110eca;
    }
    goto LAB_21110bae;
  case 1:
    local_14 = 1;
    if (('0' < (char)bVar6) && (iVar2 = iVar5, (char)bVar6 < ':')) goto LAB_21110bcb;
    iVar9 = iVar1;
    if (bVar6 != DAT_21114ed0) {
      iVar9 = iVar5;
      if ((bVar6 == 0x2b) || (iVar9 = local_14, bVar6 == 0x2d)) goto LAB_21110c5f;
      iVar9 = iVar5;
      local_14 = iVar5;
      if (bVar6 != 0x30) goto LAB_21110c38;
    }
    goto LAB_21110bae;
  case 2:
    if (('0' < (char)bVar6) && ((char)bVar6 < ':')) goto LAB_21110bcb;
    if (bVar6 == DAT_21114ed0) {
LAB_21110bda:
      iVar9 = 5;
      iVar5 = local_14;
    }
    else {
      iVar9 = iVar5;
      pbVar7 = param_3;
      iVar5 = local_14;
      if (bVar6 != 0x30) goto LAB_21110ecf;
    }
    goto LAB_21110bae;
  case 3:
    local_14 = iVar5;
    while( true ) {
      if (DAT_21114ecc < 2) {
        uVar3 = (byte)PTR_DAT_21114ed8[(uint)bVar6 * 2] & 4;
        this = PTR_DAT_21114ed8;
      }
      else {
        pbVar7 = (byte *)0x4;
        uVar3 = sub_2110F18D(this,(uint)bVar6,4);
        this = pbVar7;
      }
      if (uVar3 == 0) break;
      if (local_8 < 0x19) {
        local_8 = local_8 + 1;
        pcVar4 = local_10 + 1;
        *local_10 = bVar6 - 0x30;
        local_10 = pcVar4;
      }
      else {
        local_c = local_c + 1;
      }
      bVar6 = *pbVar8;
      pbVar8 = pbVar8 + 1;
    }
    iVar9 = iVar1;
    iVar5 = local_14;
    if (bVar6 != DAT_21114ed0) goto LAB_21110d4c;
    goto LAB_21110bae;
  case 4:
    local_14 = 1;
    local_28 = 1;
    iVar9 = iVar5;
    if (local_8 == 0) {
      while (iVar5 = local_28, iVar9 = local_14, bVar6 == 0x30) {
        local_c = local_c + -1;
        bVar6 = *pbVar8;
        pbVar8 = pbVar8 + 1;
      }
    }
    while( true ) {
      local_14 = iVar9;
      local_28 = iVar5;
      if (DAT_21114ecc < 2) {
        uVar3 = (byte)PTR_DAT_21114ed8[(uint)bVar6 * 2] & 4;
        this = PTR_DAT_21114ed8;
      }
      else {
        pbVar7 = (byte *)0x4;
        uVar3 = sub_2110F18D(this,(uint)bVar6,4);
        this = pbVar7;
      }
      if (uVar3 == 0) break;
      if (local_8 < 0x19) {
        local_8 = local_8 + 1;
        local_c = local_c + -1;
        pcVar4 = local_10 + 1;
        *local_10 = bVar6 - 0x30;
        local_10 = pcVar4;
      }
      bVar6 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      iVar5 = local_28;
      iVar9 = local_14;
    }
LAB_21110d4c:
    iVar9 = local_14;
    if ((bVar6 == 0x2b) || (bVar6 == 0x2d)) {
LAB_21110c5f:
      local_14 = iVar9;
      iVar9 = 0xb;
      pbVar8 = pbVar8 + -1;
      iVar5 = local_14;
    }
    else {
LAB_21110c38:
      if (((char)bVar6 < 'D') ||
         (('E' < (char)bVar6 && (((char)bVar6 < 'd' || ('e' < (char)bVar6)))))) goto LAB_21110eca;
      iVar9 = 6;
      iVar5 = local_14;
    }
    goto LAB_21110bae;
  case 5:
    local_28 = iVar5;
    if (DAT_21114ecc < 2) {
      uVar3 = (byte)PTR_DAT_21114ed8[(uint)bVar6 * 2] & 4;
      this = PTR_DAT_21114ed8;
    }
    else {
      pbVar7 = (byte *)0x4;
      uVar3 = sub_2110F18D(this,(uint)bVar6,4);
      this = pbVar7;
    }
    iVar9 = iVar1;
    pbVar7 = param_3;
    if (uVar3 != 0) goto LAB_21110df0;
    goto LAB_21110ecf;
  case 6:
    pbVar7 = pbVar7 + -1;
    this = pbVar7;
    param_3 = pbVar7;
    if (((char)bVar6 < '1') || ('9' < (char)bVar6)) {
      if (bVar6 == 0x2b) goto LAB_21110e25;
      if (bVar6 == 0x2d) goto LAB_21110e19;
      if (bVar6 != 0x30) goto LAB_21110ecf;
LAB_21110dbe:
      iVar9 = 8;
      iVar5 = local_14;
      goto LAB_21110bae;
    }
    break;
  case 7:
    if (((char)bVar6 < '1') || ('9' < (char)bVar6)) {
      pbVar7 = param_3;
      if (bVar6 == 0x30) goto LAB_21110dbe;
      goto LAB_21110ecf;
    }
    break;
  case 8:
    local_24 = 1;
    while (bVar6 == 0x30) {
      bVar6 = *pbVar8;
      pbVar8 = pbVar8 + 1;
    }
    if (((char)bVar6 < '1') || ('9' < (char)bVar6)) goto LAB_21110eca;
    break;
  case 9:
    local_24 = 1;
    pbVar7 = (byte *)0x0;
    goto LAB_21110e50;
  default:
    goto switchD_21110bba_caseD_a;
  case 0xb:
    if (param_7 != 0) {
      if (bVar6 == 0x2b) {
LAB_21110e25:
        iVar9 = 7;
        this = pbVar7;
        param_3 = pbVar7;
        iVar5 = local_14;
      }
      else {
        param_3 = pbVar7;
        if (bVar6 != 0x2d) goto LAB_21110ecf;
LAB_21110e19:
        local_1c = -1;
        iVar9 = 7;
        this = pbVar7;
        param_3 = pbVar7;
        iVar5 = local_14;
      }
      goto LAB_21110bae;
    }
    iVar9 = 10;
    pbVar8 = pbVar7;
switchD_21110bba_caseD_a:
    pbVar7 = pbVar8;
    iVar5 = local_14;
    if (iVar9 != 10) goto LAB_21110bae;
    goto LAB_21110ecf;
  }
  iVar9 = 9;
LAB_21110df0:
  pbVar8 = pbVar8 + -1;
  iVar5 = local_14;
  goto LAB_21110bae;
LAB_21110e50:
  if (DAT_21114ecc < 2) {
    uVar3 = (byte)PTR_DAT_21114ed8[(uint)bVar6 * 2] & 4;
    this = PTR_DAT_21114ed8;
  }
  else {
    pbVar10 = (byte *)0x4;
    uVar3 = sub_2110F18D(this,(uint)bVar6,4);
    this = pbVar10;
  }
  if (uVar3 == 0) goto LAB_21110e9a;
  this = (void *)(int)(char)bVar6;
  pbVar7 = (byte *)((int)this + (int)pbVar7 * 10 + -0x30);
  if (0x1450 < (int)pbVar7) goto LAB_21110e92;
  bVar6 = *pbVar8;
  pbVar8 = pbVar8 + 1;
  goto LAB_21110e50;
LAB_21110e92:
  pbVar7 = (byte *)0x1451;
LAB_21110e9a:
  while( true ) {
    local_20 = pbVar7;
    if (DAT_21114ecc < 2) {
      uVar3 = (byte)PTR_DAT_21114ed8[(uint)bVar6 * 2] & 4;
      this = PTR_DAT_21114ed8;
    }
    else {
      pbVar7 = (byte *)0x4;
      uVar3 = sub_2110F18D(this,(uint)bVar6,4);
      this = pbVar7;
    }
    if (uVar3 == 0) break;
    bVar6 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar7 = local_20;
  }
LAB_21110eca:
  pbVar7 = pbVar8 + -1;
LAB_21110ecf:
  *param_2 = (int)pbVar7;
  if (local_14 == 0) {
    local_44 = 0;
    local_3a = 0;
    local_3e = (byte *)0x0;
    param_3 = (byte *)0x0;
    local_18 = 4;
    goto LAB_21110fdd;
  }
  pcVar4 = local_10;
  if (0x18 < local_8) {
    if ('\x04' < local_49) {
      local_49 = local_49 + '\x01';
    }
    local_8 = 0x18;
    local_c = local_c + 1;
    pcVar4 = local_10 + -1;
  }
  if (local_8 == 0) {
    local_44 = 0;
    local_3a = 0;
    local_3e = (byte *)0x0;
    param_3 = (byte *)0x0;
  }
  else {
    while (pcVar4 = pcVar4 + -1, *pcVar4 == '\0') {
      local_8 = local_8 - 1;
      local_c = local_c + 1;
    }
    sub_21110A90(local_60,local_8,(uint *)&local_44);
    pbVar8 = local_20;
    if (local_1c < 0) {
      pbVar8 = (byte *)-(int)local_20;
    }
    pbVar8 = pbVar8 + local_c;
    if (local_24 == 0) {
      pbVar8 = pbVar8 + param_5;
    }
    if (local_28 == 0) {
      pbVar8 = pbVar8 + -param_6;
    }
    if ((int)pbVar8 < 0x1451) {
      if (-0x1451 < (int)pbVar8) {
        sub_2111150F((int *)&local_44,(uint)pbVar8,param_4);
        param_3 = (byte *)CONCAT22(uStack_40,uStack_42);
        goto LAB_21110f62;
      }
      local_34 = 1;
    }
    else {
      local_30 = 1;
    }
    local_3a = (ushort)param_3;
    local_3e = param_3;
    local_44 = local_3a;
  }
LAB_21110f62:
  if (local_30 == 0) {
    if (local_34 != 0) {
      local_44 = 0;
      local_3a = 0;
      local_3e = (byte *)0x0;
      param_3 = (byte *)0x0;
      local_18 = 1;
    }
  }
  else {
    param_3 = (byte *)0x0;
    local_3a = 0x7fff;
    local_3e = (byte *)0x80000000;
    local_44 = 0;
    local_18 = 2;
  }
LAB_21110fdd:
  *(byte **)(param_1 + 3) = local_3e;
  *(byte **)(param_1 + 1) = param_3;
  param_1[5] = local_3a | (ushort)local_2c;
  *param_1 = local_44;
  return local_18;
}

