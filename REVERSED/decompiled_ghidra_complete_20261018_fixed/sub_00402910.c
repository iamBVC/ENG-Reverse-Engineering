/* sub_402910 @ 00402910   72 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall sub_402910(int param_1,float param_2,float param_3)

{
  float10 fVar1;
  
  fVar1 = (float10)fptan((float10)*(float *)(param_1 + 0x20) * (float10)_DAT_0056e050 *
                         (float10)param_2);
  _DAT_0057dbe0 = (float)fVar1;
  DAT_0057dc68 = _DAT_0056e008 / _DAT_0057dbe0;
  DAT_0057dbe4 = _DAT_0056e008 / (_DAT_00583384 * _DAT_0057dbe0 * param_3);
  return;
}

