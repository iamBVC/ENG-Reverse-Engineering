/* sub_425CB0 @ 00425cb0   135 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_425CB0(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
               undefined4 param_6)

{
  if (param_4 != 0) {
    _DAT_00573840 = (undefined2)param_4;
    DAT_00573848 = (undefined1)param_5;
    if (param_5 != 0) {
      DAT_00573860 = 0;
    }
    else {
      _DAT_00573840 = 0xff;
      DAT_00573860 = (undefined1)param_4;
    }
    DAT_0057385d = param_5 == 0;
    _DAT_0057384c = param_3;
    _DAT_00573854 = param_1;
    _DAT_00573858 = param_2;
    DAT_0057385e = DAT_00573860;
    DAT_0057385f = DAT_00573860;
    sub_425D40(&DAT_00573840,param_6);
  }
  return;
}

