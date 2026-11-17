/* sub_425D40 @ 00425d40   1901 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_425D40(byte *param_1,float param_2)

{
  ushort *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  byte bVar7;
  char cVar8;
  char cVar9;
  int iVar10;
  uint uVar11;
  float *pfVar12;
  float *pfVar13;
  undefined4 *puVar14;
  int iVar15;
  uint uVar16;
  float *pfVar17;
  float *pfVar18;
  undefined4 uVar19;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 uStack_1c;
  uint local_18;
  int local_14;
  int local_10;
  uint local_c;
  uint local_8;
  int local_4;
  
  if (*(short *)param_1 == 0) {
    return;
  }
  local_18 = (uint)param_1[8];
  uVar16 = (uint)param_2 >> 1;
  if (param_1[0x2c] == 0) {
    uVar11 = (uint)param_1[5] << 1;
  }
  else {
    uVar11 = (uint)param_1[(uint)param_1[5] * 2 + 0x2f];
  }
  iVar10 = DAT_005ff728 + *(int *)(param_1 + 0xc) * 2 + uVar11;
  if ((((uint)param_2 & 1) != 0) && (local_18 == 0)) {
    iVar10 = iVar10 + 1;
  }
  puVar1 = (ushort *)(DAT_00581154 + iVar10 * 0x14);
  local_4 = (char)puVar1[1] * 0x20 + DAT_0058114c;
  uVar11 = (*puVar1 & 0x7000) >> 0xc;
  iVar10 = uVar11 + (*puVar1 >> 8 & 7) * 5;
  local_8 = (&DAT_00573ef8)[iVar10 * 3];
  local_10 = (&DAT_00573efc)[iVar10 * 3];
  local_c = (&DAT_005740a0)[iVar10 * 3];
  local_14 = (&DAT_005740a4)[iVar10 * 3];
  cVar8 = *(char *)(&DAT_00573f00 + iVar10 * 3);
  if ((uVar16 != 1) && (uVar16 != 0xb)) {
    if (uVar16 < 0xc) {
      if (uVar16 == 0) {
        local_44._0_1_ = *param_1;
      }
      else if (uVar16 != 10) {
        uStack_1c = 0;
        local_20 = (float)uVar16;
      }
    }
    else if (((uVar16 != 0x12) && (uVar16 != 0x13)) && (uVar16 != 0x14)) {
      if (*(int *)(param_1 + 0x28) == 0) {
        local_20 = (float)(0xb - uVar16);
        sub_563360();
      }
      local_20 = (float)(0xb - uVar16);
      sub_563360();
    }
  }
  if (local_18 == 0) {
    local_44._0_1_ = 0xff;
  }
  else {
    if (local_44._0_1_ < 0x80) {
      local_44._0_1_ = local_44._0_1_ << 1;
    }
    else if (local_44._0_1_ == 0x80) {
      local_44._0_1_ = 0xff;
      local_18 = 0;
      goto LAB_00425fc8;
    }
    if (local_44._0_1_ == 0xff) {
      local_18 = 0;
    }
  }
LAB_00425fc8:
  if (cVar8 != '\0') {
    local_44._0_1_ = (byte)(*(int *)(&DAT_00574280 + uVar11 * 4) * (uint)local_44._0_1_ >> 8);
  }
  if (param_1[0x1d] == 0) {
    cVar9 = -1;
    local_38 = CONCAT31(local_38._1_3_,0xff);
    local_30 = CONCAT31(local_30._1_3_,0xff);
    local_34 = CONCAT31(local_34._1_3_,0xff);
    cVar8 = '\0';
  }
  else {
    local_30 = CONCAT31(local_30._1_3_,param_1[0x1e]);
    local_38 = CONCAT31(local_38._1_3_,param_1[0x1f]);
    local_34 = CONCAT31(local_34._1_3_,param_1[0x20]);
    cVar8 = sub_40C510(&local_30,&local_38,&local_34);
    cVar9 = (char)local_30;
    if (((char)local_30 != (char)local_38) || ((char)local_38 != (char)local_34)) {
      bVar7 = 0;
      goto LAB_0042604f;
    }
  }
  bVar7 = 1;
LAB_0042604f:
  if ((DAT_006d7c6f != '\0') && (local_44._0_1_ != 0xff)) {
    uVar16 = (uint)local_44._0_1_;
    cVar9 = (char)((local_30 & 0xff) * uVar16 >> 8);
    local_30 = CONCAT31(local_30._1_3_,cVar9);
    local_38 = CONCAT31(local_38._1_3_,(char)((local_38 & 0xff) * uVar16 >> 8));
    local_34 = CONCAT31(local_34._1_3_,(char)((local_34 & 0xff) * uVar16 >> 8));
  }
  local_20 = (float)(((uint)CONCAT11(local_44._0_1_,cVar9) << 8 | local_38 & 0xff) << 8 |
                    local_34 & 0xff);
  if (cVar8 == '\0') {
    uVar19 = 0x80;
  }
  else {
    uVar19 = 0x100;
  }
  pfVar12 = (float *)sub_41ED90(uVar19);
  if (pfVar12 != (float *)0x0) {
    pfVar12[0x1d] = 0.0;
    pfVar12[0x1c] = local_20;
    pfVar12[0x14] = local_20;
    pfVar12[0xc] = local_20;
    pfVar12[4] = local_20;
    pfVar12[0x15] = 0.0;
    pfVar12[0xd] = 0.0;
    pfVar12[5] = 0.0;
    pfVar12[0x1a] = 0.0;
    pfVar12[0x12] = 0.0;
    pfVar12[10] = 0.0;
    pfVar12[2] = 0.0;
    pfVar12[0x1b] = 1.0;
    pfVar12[0x13] = 1.0;
    pfVar12[0xb] = 1.0;
    pfVar12[3] = 1.0;
    local_28 = (float)DAT_00583374;
    local_20 = (float)DAT_00583378;
    local_24 = (float)*(int *)(param_1 + 0x18) * local_20 * _DAT_0056e1d8;
    local_2c = (float)__ftol();
    local_44 = (float)(int)local_2c + _DAT_0056e158;
    local_2c = (float)__ftol();
    local_40 = (float)(int)local_2c + _DAT_0056e158;
    iVar10 = __ftol();
    local_24 = (float)iVar10 + _DAT_0056e158;
    iVar10 = __ftol();
    param_2 = (float)iVar10 + _DAT_0056e158;
    if (param_1[0x23] == 0) {
      local_2c = *(float *)(puVar1 + 2);
      local_3c = *(float *)(puVar1 + 4);
    }
    else {
      local_2c = *(float *)(puVar1 + 4);
      local_3c = *(float *)(puVar1 + 2);
    }
    if (param_1[0x24] == 0) {
      local_48 = *(float *)(puVar1 + 8);
      fVar2 = *(float *)(puVar1 + 6);
    }
    else {
      local_48 = *(float *)(puVar1 + 6);
      fVar2 = *(float *)(puVar1 + 8);
    }
    fVar3 = local_2c;
    if (local_44 < _DAT_0056e00c) {
      fVar4 = -local_44;
      fVar3 = local_40 - local_44;
      local_44 = 0.0;
      fVar3 = (fVar4 * (local_3c - local_2c)) / fVar3 + local_2c;
    }
    if (local_28 < local_40) {
      fVar5 = local_28 - local_40;
      fVar4 = local_40 - local_44;
      local_40 = local_28;
      local_3c = ((local_3c - fVar3) * fVar5) / fVar4 + local_3c;
    }
    fVar4 = local_24;
    if (local_24 < _DAT_0056e00c) {
      fVar2 = (-local_24 * (local_48 - fVar2)) / (param_2 - local_24) + fVar2;
      fVar4 = _DAT_0056e00c;
    }
    if (local_20 < param_2) {
      fVar6 = local_20 - param_2;
      fVar5 = param_2 - fVar4;
      param_2 = local_20;
      local_48 = ((local_48 - fVar2) * fVar6) / fVar5 + local_48;
    }
    if (_DAT_0056e00c < param_2) {
      if (fVar4 < _DAT_0056e00c) {
        fVar2 = param_2 - ((local_48 - fVar2) * fVar4) / (param_2 - fVar4);
        fVar4 = _DAT_0056e00c;
      }
      pfVar12[9] = fVar4;
      pfVar12[0x18] = local_44;
      pfVar12[1] = fVar4;
      *pfVar12 = local_44;
      pfVar12[0x1e] = fVar3;
      pfVar12[0x10] = local_40;
      pfVar12[6] = fVar3;
      pfVar12[8] = local_40;
      pfVar12[0x11] = param_2;
      pfVar12[0x19] = param_2;
      pfVar12[0xf] = fVar2;
      pfVar12[7] = fVar2;
      pfVar12[0x16] = local_3c;
      pfVar12[0xe] = local_3c;
      pfVar12[0x17] = local_48;
      pfVar12[0x1f] = local_48;
      if (cVar8 != '\0') {
        iVar10 = 4;
        pfVar13 = pfVar12 + 0x20;
        do {
          iVar10 = iVar10 + -1;
          pfVar17 = pfVar13 + -0x20;
          pfVar18 = pfVar13;
          for (iVar15 = 8; iVar15 != 0; iVar15 = iVar15 + -1) {
            *pfVar18 = *pfVar17;
            pfVar17 = pfVar17 + 1;
            pfVar18 = pfVar18 + 1;
          }
          pfVar13 = pfVar13 + 8;
        } while (iVar10 != 0);
        uVar16 = local_8;
        iVar10 = local_10;
        if (local_18 != 0) {
          uVar16 = local_c;
          iVar10 = local_14;
        }
        puVar14 = (undefined4 *)sub_41ED90(0x20);
        if (puVar14 != (undefined4 *)0x0) {
          *puVar14 = DAT_005f6ef8;
          puVar14[1] = pfVar12 + 0x20;
          puVar14[3] = 0;
          puVar14[4] = 0;
          puVar14[6] = 0;
          puVar14[5] = local_4;
          puVar14[2] = 4;
          puVar14[7] = (iVar10 * 4 | uVar16) << 0xc | -(uint)bVar7 & 4 | 0x207b;
          DAT_005f6ef8 = puVar14;
        }
      }
      uVar16 = local_8;
      iVar10 = local_10;
      if (local_18 != 0) {
        uVar16 = local_c;
        iVar10 = local_14;
      }
      puVar14 = (undefined4 *)sub_41ED90(0x20);
      if (puVar14 != (undefined4 *)0x0) {
        puVar14[3] = 0;
        puVar14[4] = 0;
        puVar14[6] = 0;
        *puVar14 = DAT_005f6ef8;
        puVar14[1] = pfVar12;
        puVar14[2] = 4;
        puVar14[5] = local_4;
        puVar14[7] = (iVar10 * 4 | uVar16) << 0xc | -(uint)bVar7 & 4 | 0x7b;
        DAT_005f6ef8 = puVar14;
        return;
      }
    }
  }
  return;
}

