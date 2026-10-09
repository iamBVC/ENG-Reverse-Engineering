/* sub_54AE20 @ 0054ae20   455 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_54AE20(void)

{
  undefined1 local_20 [32];
  
  _DAT_00573958 = (-(uint)(DAT_00584eb8 != 3) & 0xfffff600) + 0xc00;
  if (DAT_005846e4 == 3) {
    DAT_00584c0c = (short)DAT_00584eb8 + -1;
    DAT_0057235a = (undefined2)DAT_00584ebc;
    if ((DAT_00584eb8 != (DAT_00585018 & 0xff)) || (DAT_00584ebc != (DAT_00585018 >> 8 & 0xff))) {
      DAT_00584e60 = 0;
    }
  }
  sub_5536D0();
  sub_562717(local_20,s__d_d_dINTRO_DAT_00578fd0,DAT_00584eb4,DAT_00584eb8,DAT_00584ebc);
  if (DAT_005846e4 == 4) {
    DAT_005865e8 = 0;
  }
  else {
    sub_41F630(local_20,3000);
    if ((DAT_005846e4 == 4) && (DAT_005865e8 == 1)) {
      PTR_DAT_00571f54[0x54] = 1;
      DAT_005846e4 = 2;
      return;
    }
  }
  if (DAT_00584638 == 5) {
    sub_41E190();
    sub_54D0D0(DAT_00584648);
    sub_426500();
    sub_546300();
  }
  else {
    if (((DAT_005846e4 == 3) || (DAT_005846e4 == 4)) && (DAT_00584ec0 != 3)) {
      sub_54ACD0();
    }
    sub_426500();
    _DAT_00585740 = 0;
    _DAT_005846fc = 0;
    DAT_00584ec0 = 0;
    sub_419510(DAT_00584eb4,DAT_00584eb8,DAT_00584ebc,0);
    _DAT_00585740 = 0;
    sub_426500();
  }
  DAT_00584638 = 0;
  if (DAT_00584648 != 0) {
    sub_54D0D0(DAT_00584648);
    sub_54BA90(DAT_00584648);
    sub_41CBA0();
  }
  DAT_00584640 = 0;
  DAT_00584634 = 0;
  DAT_005fd08c = 0;
  DAT_005fd090 = 0;
  sub_4268C0(0);
  sub_415390(2);
  DAT_005863f4 = DAT_00584650;
  return;
}

