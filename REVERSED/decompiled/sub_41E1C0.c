/* sub_41E1C0 @ 0041e1c0   521 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41E1C0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  
  pfVar6 = DAT_00581168;
  fVar5 = _DAT_0057f92c;
  fVar4 = _DAT_0057f928;
  fVar3 = _DAT_0057f924;
  fVar2 = DAT_0057f920;
  fVar1 = DAT_0057f91c;
  DAT_0058641c = 0;
  if (DAT_00584644 != 0) {
    DAT_005865cc = *(undefined4 *)(DAT_00584644 + 0x34);
    _DAT_00586594 = *(int *)(DAT_00584644 + 0x3c);
    DAT_0058658c = *(int *)(DAT_00584644 + 0x40);
    DAT_005865b4 = *(undefined4 *)(DAT_00584644 + 0x44);
    DAT_0058659c = *(undefined4 *)(DAT_00584644 + 0x48);
    _DAT_0057f8fc = (float)DAT_0058658c * _DAT_0056e28c;
    _DAT_0057f8f8 = (float)_DAT_00586594 * _DAT_0056e28c;
    _DAT_0057f914 = _DAT_0056e288 / (_DAT_0057f8fc - DAT_0057f910);
    _DAT_0057f904 = _DAT_0056e008 / (_DAT_0057f8fc - _DAT_0057f8f8);
    DAT_0057f90c = _DAT_0057f8fc;
    DAT_00586590 = DAT_0058658c;
    DAT_005865a4 = DAT_0058658c;
    DAT_005865b0 = _DAT_00586594;
    _DAT_005865c8 = _DAT_00586594;
    DAT_00581168[3] = DAT_0057f918;
    pfVar6[4] = fVar1;
    pfVar6[5] = fVar2;
    *pfVar6 = fVar3 * (float)_DAT_0056e358 * (float)_DAT_0056e368;
    pfVar6[1] = fVar4 * (float)_DAT_0056e358 * (float)_DAT_0056e368;
    pfVar6[2] = fVar5 * (float)_DAT_0056e358 * (float)_DAT_0056e368;
    DAT_00581168[8] = _DAT_0057f908 * (float)_DAT_0056e358 * (float)_DAT_0056e368;
    sub_402910(0x3f800000,0x3f800000);
    DAT_00581168[6] = DAT_0057f910;
    DAT_00581168[7] = DAT_0057f90c;
    sub_402960();
    sub_424B90(DAT_006da330 & 0x800,1);
    sub_424BB0(DAT_0057f910,DAT_0057f90c);
    sub_41A440(0xc0);
    if (param_1 == 0) {
      sub_439110(DAT_00584644 + 0x50);
    }
    sub_41BCF0(*(undefined1 *)(DAT_00584644 + 0x4c),*(undefined1 *)(DAT_00584644 + 0x4d),
               *(undefined1 *)(DAT_00584644 + 0x4e),0xff);
    sub_438180();
    sub_5460D0(*(ushort *)(DAT_00584644 + 0x56) & 0xf,
               (byte)(*(ushort *)(DAT_00584644 + 0x56) >> 8) & 0x7f);
  }
  return;
}

