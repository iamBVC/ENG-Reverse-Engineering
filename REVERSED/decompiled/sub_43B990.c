/* sub_43B990 @ 0043b990   1893 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_43B990(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,byte param_6,
               byte param_7,byte param_8)

{
  short sVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int *piVar13;
  int iVar14;
  code *pcVar15;
  float local_cc;
  float local_c4;
  float local_c0;
  float local_bc;
  int local_b8 [4];
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_8;
  float local_4;
  
  if (param_6 < 0x80) {
    _param_6 = (uint)(byte)(param_6 << 1);
  }
  else {
    _param_6 = 0xff;
  }
  if (param_7 < 0x80) {
    _param_7 = (uint)(byte)(param_7 << 1);
  }
  else {
    _param_7 = 0xff;
  }
  if (param_8 < 0x80) {
    _param_8 = (uint)(byte)(param_8 << 1);
  }
  else {
    _param_8 = 0xff;
  }
  sVar1 = *(short *)(param_1 + 0xc);
  fVar3 = (float)(int)*(short *)(param_1 + 4) * _DAT_0056e118 + _DAT_0056e1dc;
  sVar2 = *(short *)(param_1 + 0xe);
  fVar4 = (float)(int)*(short *)(param_1 + 6) * _DAT_0056e118 + _DAT_0056e1dc;
  fVar5 = (float)((int)sVar1 + (int)*(short *)(param_1 + 4)) * _DAT_0056e118 - _DAT_0056e1dc;
  iVar14 = 6;
  piVar13 = local_b8 + 2;
  fVar6 = (float)((int)sVar2 + (int)*(short *)(param_1 + 6)) * _DAT_0056e118 - _DAT_0056e1dc;
  do {
    piVar13[1] = 0;
    *piVar13 = _param_8 + ((_param_6 + 0xff00) * 0x100 + _param_7) * 0x100;
    piVar13[-2] = 0;
    piVar13[-1] = 0x3f800000;
    piVar13 = piVar13 + 8;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  fVar10 = (float)param_2;
  local_cc = (float)param_3;
  fVar8 = (float)(int)sVar1;
  local_c4 = (float)(int)sVar2;
  if (param_4 != 0) {
    fVar7 = (float)_DAT_005fcff0;
    fVar8 = ((float)param_4 * fVar8 * _DAT_0056e118 * _DAT_0056e4c4) / fVar7;
    local_c4 = ((float)param_4 * local_c4 * _DAT_0056e118 * _DAT_0056e4c4) / fVar7;
    fVar10 = (fVar10 * _DAT_0056e4c4) / fVar7 + _DAT_0056e4c0;
    local_cc = (local_cc * _DAT_0056e4c4) / fVar7 + _DAT_0056e4bc;
  }
  fVar9 = (float)DAT_00583374;
  fVar7 = fVar9 * _DAT_0056e1dc * fVar10;
  fVar11 = (float)DAT_00583378;
  fVar12 = fVar11 * _DAT_0056e1d8 * local_cc;
  local_60 = (fVar8 + fVar10) * fVar9 * _DAT_0056e1dc;
  local_3c = (local_c4 + local_cc) * fVar11 * _DAT_0056e1d8;
  if ((((fVar7 < fVar9) && (fVar12 < fVar11)) && (_DAT_0056e00c <= local_60)) &&
     (_DAT_0056e00c <= local_3c)) {
    local_20 = fVar7;
    local_8 = fVar3;
    if (fVar7 < _DAT_0056e00c) {
      local_20 = 0.0;
      local_8 = fVar3 - ((fVar5 - fVar3) * fVar7) / (local_60 - fVar7);
    }
    local_1c = fVar12;
    local_4 = fVar4;
    if (fVar12 < _DAT_0056e00c) {
      local_1c = 0.0;
      local_4 = fVar4 - ((fVar6 - fVar4) * fVar12) / (local_3c - fVar12);
    }
    local_48 = fVar5;
    if (fVar9 < local_60) {
      local_48 = ((fVar5 - local_8) * (fVar9 - local_20)) / (local_60 - local_20) + local_8;
      local_60 = (float)(DAT_00583374 + -1);
    }
    local_24 = fVar6;
    if (fVar11 < local_3c) {
      local_24 = ((fVar6 - local_4) * (fVar11 - local_1c)) / (local_3c - local_1c) + local_4;
      local_3c = (float)(DAT_00583378 + -1);
    }
    local_c0 = local_20;
    local_bc = local_1c;
    local_a8 = local_8;
    local_a4 = local_4;
    local_a0 = local_60;
    local_9c = local_1c;
    local_88 = local_48;
    local_84 = local_4;
    local_80 = local_60;
    local_7c = local_3c;
    local_68 = local_48;
    local_64 = local_24;
    local_5c = local_3c;
    local_44 = local_24;
    local_40 = local_20;
    local_28 = local_8;
    if (DAT_005833e1 != '\0') {
      pcVar15 = sub_4C6CD0;
      if (DAT_00583380 == '\0') {
        pcVar15 = sub_442BD0;
      }
      (*pcVar15)(DAT_0058331c,DAT_005832f0,(&DAT_006d875c)[(uint)*(byte *)(param_1 + 0x11) * 0x25],
                 DAT_00583308 >> 1,DAT_00583374,&local_c0,6,0,0,0x1e);
      return;
    }
    if (DAT_006d7c54 != (&DAT_006d8750)[(uint)*(byte *)(param_1 + 0x11) * 0x25]) {
      (**(code **)(*DAT_00582cd4 + 0x98))
                (DAT_00582cd4,0,(&DAT_006d8750)[(uint)*(byte *)(param_1 + 0x11) * 0x25]);
      DAT_006d7c54 = (&DAT_006d8750)[(uint)*(byte *)(param_1 + 0x11) * 0x25];
    }
    if (DAT_005833f9 == '\0') {
      if (DAT_006d7c4e != '\x01') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,1);
        DAT_006d7c4e = '\x01';
      }
      if (DAT_006d7c34 != 2) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,2);
        DAT_006d7c34 = 2;
      }
      if (DAT_006d7c30 != '\0') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,0);
        DAT_006d7c30 = '\0';
      }
      if (DAT_006d7c4c != '\0') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
        DAT_006d7c4c = '\0';
      }
      if (DAT_006d7c3a != '\0') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
        DAT_006d7c3a = '\0';
      }
      if (DAT_006d7c58 != 4) {
        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,4);
        DAT_006d7c58 = 4;
      }
    }
    else {
      if (DAT_006d7c4e != '\0') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,0);
        DAT_006d7c4e = '\0';
      }
      if (DAT_006d7c34 != 2) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,2);
        DAT_006d7c34 = 2;
      }
      if (DAT_006d7c30 != '\0') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,0);
        DAT_006d7c30 = '\0';
      }
      if (DAT_006d7c3a != '\0') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
        DAT_006d7c3a = '\0';
      }
      if (DAT_006d7c40 != 2) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
        DAT_006d7c40 = 2;
      }
      if (DAT_006d7c44 != 6) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
        DAT_006d7c44 = 6;
      }
      if (DAT_006d7c4c != '\x01') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
        DAT_006d7c4c = '\x01';
      }
      if (DAT_006d7c58 != 4) {
        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,4);
        DAT_006d7c58 = 4;
      }
      if (DAT_006d7c5c != 2) {
        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
        DAT_006d7c5c = 2;
      }
    }
    (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,4,0x1c4,&local_c0,6,0);
    DAT_006d7c74 = 0xd0b070;
  }
  return;
}

