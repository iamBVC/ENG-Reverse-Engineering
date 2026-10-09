/* sub_435D10 @ 00435d10   1056 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_435D10(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
               char param_7,char param_8,char param_9)

{
  ushort *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  float *pfVar8;
  int iVar9;
  undefined4 *puVar10;
  uint uVar11;
  int iVar12;
  int local_8;
  uint local_4;
  
  if (((param_1 != -NAN) && (param_4 != 0.0)) && (param_5 != 0.0)) {
    puVar1 = (ushort *)(DAT_00581154 + (int)param_1 * 0x14);
    iVar12 = *(char *)(DAT_00581154 + 2 + (int)param_1 * 0x14) * 0x20 + DAT_0058114c;
    uVar7 = *puVar1 >> 8 & 7;
    uVar11 = (*puVar1 & 0x7000) >> 0xc;
    if (param_9 == '\0') {
      iVar9 = uVar11 + uVar7 * 5;
      local_4 = (&DAT_00573ef8)[iVar9 * 3];
      local_8 = (&DAT_00573efc)[iVar9 * 3];
    }
    else {
      iVar9 = uVar11 + uVar7 * 5;
      local_4 = (&DAT_005740a0)[iVar9 * 3];
      local_8 = (&DAT_005740a4)[iVar9 * 3];
    }
    pfVar8 = (float *)sub_41ED90(0x80);
    if (pfVar8 != (float *)0x0) {
      if ((DAT_005833f0 == '\0') && (((uint)param_6 & 0xf0f0f0) == 0xf0f0f0)) {
        param_2 = (float)((int)param_2 + -2);
        param_3 = (float)((int)param_3 + -2);
        param_4 = (float)((int)param_4 + 4);
        param_5 = (float)((int)param_5 + 4);
      }
      _param_9 = (float)(int)param_2 * (float)DAT_00583374 * _DAT_0056e1dc;
      iVar9 = (int)param_5 / 2;
      fVar3 = *(float *)(puVar1 + 4);
      param_5 = *(float *)(puVar1 + 2);
      param_2 = (float)((int)param_2 + (int)param_4) * (float)DAT_00583374 * _DAT_0056e1dc;
      param_4 = (float)(int)param_3 * (float)DAT_00583378 * _DAT_0056e1d8;
      param_1 = *(float *)(puVar1 + 6);
      fVar4 = (float)(iVar9 + (int)param_3) * (float)DAT_00583378 * _DAT_0056e1d8;
      fVar2 = *(float *)(puVar1 + 8);
      if (((_param_9 < DAT_005ff71c) && (DAT_005ff718 < param_2)) &&
         ((param_4 < _DAT_005ff724 && (DAT_005ff720 < fVar4)))) {
        if (_param_9 < DAT_005ff718) {
          fVar5 = DAT_005ff718 - _param_9;
          fVar6 = param_2 - _param_9;
          _param_9 = DAT_005ff718;
          param_5 = ((fVar3 - param_5) * fVar5) / fVar6 + param_5;
        }
        param_3 = fVar3;
        if (DAT_005ff71c < param_2) {
          fVar5 = DAT_005ff71c - param_2;
          fVar6 = param_2 - _param_9;
          param_2 = DAT_005ff71c;
          param_3 = ((fVar3 - param_5) * fVar5) / fVar6 + fVar3;
        }
        if (param_4 < DAT_005ff720) {
          fVar5 = DAT_005ff720 - param_4;
          fVar3 = fVar4 - param_4;
          param_4 = DAT_005ff720;
          param_1 = ((fVar2 - param_1) * fVar5) / fVar3 + param_1;
        }
        if (_DAT_005ff724 < fVar4) {
          fVar2 = ((fVar2 - param_1) * (_DAT_005ff724 - fVar4)) / (fVar4 - param_4) + fVar2;
          fVar4 = _DAT_005ff724;
        }
        pfVar8[0x1c] = param_6;
        pfVar8[0x18] = _param_9;
        *pfVar8 = _param_9;
        pfVar8[0x10] = param_2;
        pfVar8[8] = param_2;
        pfVar8[9] = param_4;
        pfVar8[0x19] = fVar4;
        pfVar8[0x11] = fVar4;
        pfVar8[1] = param_4;
        pfVar8[0x1b] = 1.0;
        pfVar8[0x13] = 1.0;
        pfVar8[0xb] = 1.0;
        pfVar8[3] = 1.0;
        pfVar8[0x1f] = fVar2;
        pfVar8[0x14] = param_6;
        pfVar8[0xc] = param_6;
        pfVar8[4] = param_6;
        pfVar8[0x1e] = param_5;
        pfVar8[0x17] = fVar2;
        pfVar8[6] = param_5;
        pfVar8[0xe] = param_3;
        pfVar8[0x16] = param_3;
        pfVar8[0x1a] = 0.0;
        pfVar8[0x12] = 0.0;
        pfVar8[10] = 0.0;
        pfVar8[2] = 0.0;
        pfVar8[0x1d] = 0.0;
        pfVar8[0x15] = 0.0;
        pfVar8[0xd] = 0.0;
        pfVar8[5] = 0.0;
        pfVar8[0xf] = param_1;
        pfVar8[7] = param_1;
        if ((param_8 != '\0') &&
           (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar10 != (undefined4 *)0x0)) {
          *puVar10 = DAT_005f6ef8;
          puVar10[1] = pfVar8;
          puVar10[2] = 4;
          puVar10[3] = 0;
          puVar10[4] = 0;
          puVar10[5] = iVar12;
          puVar10[6] = 0;
          puVar10[7] = (local_8 * 4 | local_4) << 0xc | -(uint)(param_7 != '\0') & 4 | 0x207b;
          DAT_005f6ef8 = puVar10;
        }
        puVar10 = (undefined4 *)sub_41ED90(0x20);
        if (puVar10 != (undefined4 *)0x0) {
          *puVar10 = DAT_005f6ef8;
          puVar10[1] = pfVar8;
          puVar10[3] = 0;
          puVar10[4] = 0;
          puVar10[6] = 0;
          puVar10[5] = iVar12;
          puVar10[2] = 4;
          puVar10[7] = (local_8 * 4 | local_4) << 0xc | -(uint)(param_7 != '\0') & 4 | 0x7b;
          DAT_005f6ef8 = puVar10;
          return;
        }
      }
    }
  }
  return;
}

