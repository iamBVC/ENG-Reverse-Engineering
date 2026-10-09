/* sub_554FC0 @ 00554fc0   113 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_554FC0(undefined4 param_1)

{
  int iVar1;
  
  DAT_006d9be8 = sub_54BC00(param_1);
  iVar1 = sub_54BC00(param_1);
  DAT_00578ef4 = iVar1 >> 0xc;
  iVar1 = sub_54BC00(param_1);
  DAT_006d9bf4 = iVar1 >> 0xc;
  _DAT_00578ef0 = sub_54BC00(param_1);
  _DAT_00578ef0 = _DAT_00578ef0 >> 0xc;
  if (((_DAT_00578ef0 == 0) && (DAT_006d9bf4 == 0)) && (DAT_00578ef4 == 0)) {
    sub_4284A0();
    DAT_006d9be4 = 0;
    DAT_006d94d0 = 0;
    return;
  }
  DAT_006d9be4 = 1;
  return;
}

