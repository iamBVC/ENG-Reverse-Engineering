/* sub_4387E0 @ 004387e0   230 bytes */

void sub_4387E0(void)

{
  if ((DAT_005833f0 == '\0') || (DAT_005833f2 == '\0')) {
    DAT_00573d4c = 0;
  }
  else {
    DAT_00573d4c = 1;
    DAT_00573d4d = 1;
    if (DAT_005833e1 == '\0') goto LAB_00438818;
  }
  DAT_00573d4d = 0;
LAB_00438818:
  DAT_00573d50 = DAT_005833e2;
  DAT_00573d51 = DAT_005833e9;
  DAT_00573d4e = DAT_005833e8;
  DAT_00573d4f = DAT_005833ed;
  if (((DAT_005833f3 != '\0') || (DAT_005833f4 != '\0')) || (DAT_00573d52 = 0, DAT_005833f7 != '\0')
     ) {
    DAT_00573d52 = 1;
  }
  if ((DAT_005833ec == '\0') || (DAT_005833ea == '\0')) {
    DAT_00573d53 = 0;
  }
  else {
    DAT_00573d53 = 1;
    if ((DAT_005833ed != '\0') && (DAT_005833fb != '\0')) {
      DAT_00573d53 = 1;
      DAT_00573d54 = 1;
      DAT_00573d55 = DAT_005833f4;
      DAT_00573d56 = 1;
      DAT_00573d57 = DAT_005833f3;
      return;
    }
  }
  DAT_00573d54 = 0;
  DAT_00573d55 = DAT_005833f4;
  DAT_00573d56 = 1;
  DAT_00573d57 = DAT_005833f3;
  return;
}

