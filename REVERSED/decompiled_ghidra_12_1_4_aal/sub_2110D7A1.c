/* sub_2110D7A1 @ 2110d7a1   184 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_2110D7A1(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 1) {
    DAT_2111562c = GetVersion();
    iVar1 = sub_2110DF80(0);
    if (iVar1 == 0) {
      return 0;
    }
    _DAT_21115638 = DAT_2111562c >> 8 & 0xff;
    _DAT_21115634 = DAT_2111562c & 0xff;
    DAT_2111562c = DAT_2111562c >> 0x10;
    _DAT_21115630 = _DAT_21115634 * 0x100 + _DAT_21115638;
    DAT_21115b58 = GetCommandLineA();
    DAT_21115600 = sub_2110E505();
    sub_2110E031();
    sub_2110E2B8();
    sub_2110E1FF();
    sub_2110DE80();
    DAT_211155fc = DAT_211155fc + 1;
  }
  else if (param_2 == 0) {
    if (DAT_211155fc < 1) {
      return 0;
    }
    DAT_211155fc = DAT_211155fc + -1;
    if (DAT_21115664 == 0) {
      sub_2110DEBE();
    }
    sub_2110E1DC();
    sub_2110DFBC();
  }
  return 1;
}

