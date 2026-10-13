/* Selected Ghidra export at 00417370. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_417370(void)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = DAT_00573d2c._1_1_;
  uVar2 = _DAT_00573d34 & 0xff;
  DAT_00573d2c._1_1_ = DAT_005833e1 == '\0';
  if ((bool)DAT_00573d2c._1_1_) {
    _DAT_00573d34 = 0x101;
    DAT_005848cc = 0x3f800000;
  }
  else {
    _DAT_00573d34 = 0x100;
    DAT_005848cc = 0;
  }
  _DAT_00573d34 = CONCAT13(DAT_00573d34_3,(uint3)_DAT_00573d34);
  DAT_006d8731 = 1;
  DAT_00573d30 = DAT_00573d2c._1_1_;
  sub_438180();
  if (cVar1 != DAT_00573d2c._1_1_) {
    sub_417260();
    DAT_00583b78 = 1;
    return 0;
  }
  if (uVar2 != (_DAT_00573d34 & 0xff)) {
    sub_439600();
    sub_417260();
    sub_408300();
    sub_4071D0();
    sub_437D00();
    return 0;
  }
  sub_439600();
  sub_417260();
  return 0;
}

