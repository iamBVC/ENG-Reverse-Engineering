/* Selected Ghidra export at 0054d620. */

void sub_54D620(undefined4 param_1)

{
  int iVar1;
  byte bVar2;
  
  DAT_00585008 = DAT_00584eb4;
  DAT_0058500c = DAT_00584eb8;
  DAT_00585010 = DAT_00584ebc;
  DAT_00585014 = DAT_00584ec0;
  iVar1 = sub_54BC00(param_1);
  DAT_00584ebc = iVar1 >> 0xc;
  iVar1 = sub_54BC00(param_1);
  DAT_00584eb8 = iVar1 >> 0xc;
  iVar1 = sub_54BC00(param_1);
  DAT_00584ec0 = 0;
  DAT_00584eb4 = iVar1 >> 0xc;
  DAT_00584638 = 10;
  if (*(uint *)(&DAT_00584f1c + (DAT_00585010 + DAT_0058500c * 6) * 2) >> 0xc ==
      (uint)*(ushort *)(s_ITS_NOT_USED___08x_005722e5 + (DAT_00585010 + DAT_0058500c * 5) * 2 + 0xf)
     ) {
    sub_414600(s_______All_coins_collected________0057999c);
    (&DAT_00584ec8)[DAT_0058500c * 6 + DAT_00585010] =
         (&DAT_00584ec8)[DAT_0058500c * 6 + DAT_00585010] | 2;
  }
  if (((byte)DAT_00584710 & 8) != 0) {
    (&DAT_00584ec8)[DAT_0058500c * 6 + DAT_00585010] =
         (&DAT_00584ec8)[DAT_0058500c * 6 + DAT_00585010] | 3;
  }
  sub_41CD70();
  if (((DAT_00585018 & 0xff) <= DAT_0058500c) && ((DAT_00585018 >> 8 & 0xff) <= DAT_00585010)) {
    DAT_00585018._0_2_ = CONCAT11((char)DAT_00585010 + '\x01',(char)DAT_0058500c);
    if ((DAT_0058500c == 8) && (DAT_00585010 == 5)) {
      DAT_00585018 = CONCAT22(DAT_00585018._2_2_,0x508);
    }
  }
  if (((DAT_00584eb4 == 7) && (DAT_00584eb8 == 7)) && (DAT_00584ebc == 7)) {
    DAT_00584eb4 = 1;
    DAT_00584eb8 = DAT_0058500c;
    DAT_00584ebc = DAT_00585010;
    DAT_006d94b0 = 1;
    if ((DAT_00585018 & 0xff) <= DAT_0058500c) {
      bVar2 = (char)DAT_0058500c + 1;
      DAT_00585018 = CONCAT22(DAT_00585018._2_2_,0x100);
      DAT_00585018 = CONCAT31(DAT_00585018._1_3_,bVar2);
      DAT_00584eb8 = (uint)bVar2;
      DAT_00584ebc = 1;
    }
    if ((DAT_0058500c == 8) && (DAT_00585010 == 6)) {
      DAT_00585018 = CONCAT22(DAT_00585018._2_2_,0x508);
      DAT_00584eb8 = 1;
      DAT_00584ebc = 1;
      sub_415390(1);
      return;
    }
  }
  else {
    DAT_006d94b0 = 0;
  }
  sub_415390(1);
  return;
}

