/* sub_41A920 @ 0041a920   457 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41A920(int *param_1,int param_2,ushort param_3)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar9 = *(int *)(param_2 + 0x10) - param_1[4];
  iVar7 = *(int *)(param_2 + 0x18) - param_1[6];
  iVar8 = *(int *)(param_2 + 0x14) - param_1[5];
  _DAT_005848b8 = __ftol();
  fpatan((float10)iVar8,(float10)_DAT_005848b8);
  _DAT_005848bc = iVar9;
  _DAT_005848c0 = iVar8;
  _DAT_005848c4 = iVar7;
  if (_DAT_005848b8 < 0x180) {
    iVar8 = __ftol();
    fpatan((float10)iVar9,(float10)iVar7);
    uVar4 = __ftol();
    uVar5 = uVar4 - param_1[1];
    uVar6 = (int)uVar5 >> 0x1f;
    if (0x10 < (int)((uVar5 ^ uVar6) - uVar6)) {
      uVar4 = param_1[1];
    }
  }
  else {
    iVar8 = __ftol();
    fpatan((float10)iVar9,(float10)iVar7);
    uVar4 = __ftol();
  }
  pfVar3 = DAT_00581168;
  iVar9 = param_1[6];
  fVar2 = (float)_DAT_0056e020;
  iVar7 = param_1[5];
  fVar1 = (float)_DAT_0056e020;
  DAT_00581168[3] = (float)param_1[4] * (float)_DAT_0056e020;
  pfVar3[4] = (float)iVar7 * fVar1;
  pfVar3[5] = (float)-iVar9 * fVar2;
  *pfVar3 = (float)-iVar8 * (float)_DAT_0056e018;
  pfVar3[1] = (float)(int)(uVar4 ^ 0x800) * (float)_DAT_0056e018;
  pfVar3[2] = (float)(int)(short)(param_3 ^ 0x800) * (float)_DAT_0056e018;
  sub_402960();
  _DAT_006d8400 = DAT_00581168[3];
  _DAT_006d8404 = DAT_00581168[4];
  _DAT_006d8408 = DAT_00581168[5];
  *param_1 = iVar8;
  param_1[1] = uVar4;
  param_1[2] = 0;
  if (DAT_006d9e28 != 0) {
    *(int *)(DAT_006d9e28 + 0x20) = iVar8 << 0xc;
    *(int *)(DAT_006d9e28 + 0x24) = param_1[1] << 0xc;
    *(int *)(DAT_006d9e28 + 0x28) = param_1[2] << 0xc;
  }
  return;
}

