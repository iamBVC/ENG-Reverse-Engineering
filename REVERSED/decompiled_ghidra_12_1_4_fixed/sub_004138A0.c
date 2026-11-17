/* sub_4138A0 @ 004138a0   378 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_4138A0(float param_1,int param_2,int param_3,int param_4)

{
  float fVar1;
  uint uVar2;
  
  _DAT_00583398 = (float)(int)param_1 * DAT_00583390 * _DAT_0056e1dc;
  _DAT_005833a0 = (float)param_2 * DAT_00583394 * _DAT_0056e1d8;
  _DAT_005833a8 = (float)param_3 * DAT_00583390 * _DAT_0056e1dc;
  _DAT_005833ac = (float)param_4 * DAT_00583394 * _DAT_0056e1d8;
  fVar1 = _DAT_005833a8 + _DAT_00583398;
  uVar2 = ((uint)fVar1 >> 0x17 & 0xff) - 0x17;
  if ((int)uVar2 < 1) {
    if (uVar2 == 0xffffffe9) {
      param_1 = (float)CONCAT31((uint3)((uint)fVar1 >> 8) & 0x800000,1);
    }
    else {
      param_1 = (float)(0x400000 >> (-(char)uVar2 & 0x1fU) | (uint)fVar1 & 0x80000000);
    }
  }
  else {
    param_1 = (float)((uVar2 & 0xff) << 0x17 | (uint)fVar1 & 0x80000000);
  }
  _DAT_0058339c = fVar1 - param_1;
  fVar1 = _DAT_005833ac + _DAT_005833a0;
  uVar2 = ((uint)fVar1 >> 0x17 & 0xff) - 0x17;
  if ((int)uVar2 < 1) {
    if (uVar2 == 0xffffffe9) {
      param_1 = (float)CONCAT31((uint3)((uint)fVar1 >> 8) & 0x800000,1);
    }
    else {
      param_1 = (float)(0x400000 >> (-(char)uVar2 & 0x1fU) | (uint)fVar1 & 0x80000000);
    }
  }
  else {
    param_1 = (float)((uVar2 & 0xff) << 0x17 | (uint)fVar1 & 0x80000000);
  }
  _DAT_005833a4 = fVar1 - param_1;
  _DAT_005833b0 = (_DAT_005833a8 * _DAT_0056e158 + _DAT_00583398) - _DAT_0056e028;
  _DAT_005833b4 = (_DAT_005833ac * _DAT_0056e158 + _DAT_005833a0) - _DAT_0056e028;
  _DAT_005833b8 = _DAT_005833a8 * _DAT_0056e158;
  _DAT_005833bc = _DAT_005833ac * _DAT_0056e1d4;
  return;
}

