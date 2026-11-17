/* sub_41A480 @ 0041a480   337 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41A480(void)

{
  int iVar1;
  
  if (((DAT_005846e4 == 3) || (DAT_005846e4 == 4)) && (DAT_0057f8bc == 0)) {
    iVar1 = __ftol();
    _DAT_005865c8 = iVar1;
    DAT_0058658c = __ftol();
    _DAT_0057f8fc =
         ((float)DAT_0058658c * DAT_005848cc +
         (float)DAT_0058658c * (_DAT_0056e008 - DAT_005848cc) * _DAT_0056e158) * _DAT_0056e28c;
    _DAT_0057f8f8 =
         ((float)_DAT_005865c8 * DAT_005848cc +
         (float)_DAT_005865c8 * (_DAT_0056e008 - DAT_005848cc) * _DAT_0056e158) * _DAT_0056e28c;
    _DAT_0057f914 = _DAT_0056e288 / (_DAT_0057f8fc - DAT_0057f910);
    _DAT_0057f904 = _DAT_0056e008 / (_DAT_0057f8fc - _DAT_0057f8f8);
    DAT_0057f90c = _DAT_0057f8fc;
    DAT_00586590 = DAT_0058658c;
    _DAT_00586594 = iVar1;
    *(float *)(DAT_00581168 + 0x1c) = _DAT_0057f8fc;
    *(float *)(DAT_00581168 + 0x18) = DAT_0057f910;
    sub_424BB0(DAT_0057f910,DAT_0057f90c);
  }
  return;
}

