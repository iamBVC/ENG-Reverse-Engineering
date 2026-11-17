/* sub_41A440 @ 0041a440   60 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41A440(ushort param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)fpatan((float10)_DAT_0056e280 / (float10)param_1,(float10)1);
  *(float *)(DAT_00581168 + 0x20) = (float)(fVar1 + fVar1);
  sub_402910(0x3f800000,0x3f800000);
  return;
}

