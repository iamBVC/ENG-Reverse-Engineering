/* sub_41BCF0 @ 0041bcf0   114 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall sub_41BCF0(int param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  *(float *)(param_1 + 0x10) = (float)param_2 * _DAT_0056e0c8;
  *(float *)(param_1 + 0x14) = (float)param_3 * _DAT_0056e0c8;
  *(float *)(param_1 + 0x18) = (float)param_4 * _DAT_0056e0c8;
  *(float *)(param_1 + 0x1c) = (float)param_5 * _DAT_0056e0c8;
  sub_41BEE0();
  return;
}

