/* sub_2110D1D7 @ 2110d1d7   399 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
sub_2110D1D7(void *this,uint *param_1,uint *param_2,uint param_3,uint *param_4,uint param_5,
            undefined4 *param_6,undefined4 *param_7,uint param_8,undefined4 param_9,
            undefined4 param_10,uint param_11)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  void *extraout_ECX;
  uint uVar13;
  uint extraout_EDX;
  uint uVar14;
  
  uVar12 = DAT_211148bc;
  uVar11 = DAT_211148b8;
  uVar10 = DAT_211148b4;
  uVar9 = DAT_211148b0;
  uVar8 = DAT_211148ac;
  uVar7 = DAT_211148a8;
  uVar6 = DAT_211148a4;
  uVar5 = DAT_211148a0;
  uVar4 = DAT_2111489c;
  uVar3 = DAT_21114898;
  uVar2 = DAT_21114894;
  _DAT_2111489c = param_8 >> 0x10;
  DAT_21114894 = param_8 << 0x10;
  DAT_21114898 = _DAT_2111489c + 1;
  if ((param_11 & 8) != 0) {
    _DAT_2111489c = _DAT_2111489c << 1;
    DAT_21114898 = DAT_21114898 * 2;
  }
  if ((param_11 & 2) != 0) {
    _DAT_2111489c = _DAT_2111489c << 1;
    DAT_21114898 = DAT_21114898 << 1;
  }
  uVar13 = *param_2;
  if (((param_11 & 4) == 0) || ((int)param_8 < 0x10001)) {
    uVar13 = uVar13 << 0x10;
  }
  DAT_211148b8 = *param_6;
  DAT_211148bc = *param_7;
  uVar1 = *param_1;
  uVar14 = 0;
  if ((uVar1 < param_3) && (uVar14 = *param_4, this = (void *)param_5, uVar14 < param_5)) {
    DAT_211148a4 = param_9;
    DAT_211148a8 = param_10;
    DAT_211148ac = param_3;
    DAT_211148b0 = param_5;
    DAT_211148b4 = param_8;
    DAT_211148a0 = param_11;
    (*(code *)(&PTR_LAB_2110a7b0)[param_11 >> 3])();
    this = extraout_ECX;
    uVar13 = extraout_EDX;
  }
  if (((param_11 & 4) == 0) || ((int)param_8 < 0x10001)) {
    this = (void *)(uVar13 >> 0x10);
  }
  *param_1 = uVar1;
  *param_4 = uVar14;
  *param_2 = (uint)this;
  *param_6 = DAT_211148b8;
  *param_7 = DAT_211148bc;
  DAT_211148bc = uVar12;
  DAT_211148b8 = uVar11;
  DAT_211148b4 = uVar10;
  DAT_211148b0 = uVar9;
  DAT_211148ac = uVar8;
  DAT_211148a8 = uVar7;
  DAT_211148a4 = uVar6;
  DAT_211148a0 = uVar5;
  _DAT_2111489c = CONCAT31(DAT_2111489c_1,uVar4);
  DAT_21114898 = uVar3;
  DAT_21114894 = uVar2;
  return;
}

