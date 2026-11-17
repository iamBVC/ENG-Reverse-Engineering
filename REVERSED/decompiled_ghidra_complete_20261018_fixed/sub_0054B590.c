/* sub_54B590 @ 0054b590   606 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_54B590(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 auStack_60 [17];
  undefined4 uStack_1c;
  undefined4 uStack_18;
  uint uStack_14;
  undefined4 uStack_10;
  
  if (DAT_00584640 == 0) {
    uStack_10 = 0x54b5a1;
    sub_40C6E0();
  }
  uStack_10 = 1;
  puVar2 = (undefined4 *)(PTR_DAT_005724dc + 0x118);
  puVar3 = auStack_60;
  for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  sub_40E0C0(PTR_DAT_005724dc + 0x18);
  if (DAT_005846e4 == 3) {
    if (DAT_00584640 == 0) {
      uStack_10 = 0;
      uStack_14 = 0x54b5f3;
      sub_419E00();
    }
    else {
      uStack_10 = 1;
      uStack_14 = 0x54b5e7;
      sub_419E00();
    }
  }
  else {
    uStack_10 = 0x54b5fd;
    sub_41A220();
  }
  uStack_10 = 0x54b602;
  sub_427C40();
  if (DAT_006da294 != '\0') {
    uStack_10 = 1;
    uStack_14 = 0x54b611;
    sub_40DD60();
  }
  uStack_10 = 0x54b619;
  sub_41E020();
  if ((DAT_005846e4 != 4) && (DAT_005846e4 == 3)) {
    if ((DAT_005fcf08 & 0xf000) != 0) {
      uStack_10 = 0x54b642;
      iVar1 = sub_414FB0();
      if (((iVar1 != 0) && (DAT_00581d74 == 0)) &&
         ((DAT_006d9858 != '\0' || (DAT_006d94e8 != '\0')))) {
        _DAT_006d9bb4 = 1;
        _DAT_006d9844 = 1;
      }
    }
    if (((DAT_005fcf08 & 8) != 0) && (DAT_00584634 == 0)) {
      uStack_10 = 0x54b68c;
      iVar1 = sub_4152D0();
      if ((iVar1 != 0) && (DAT_00584640 != 2)) {
        if (DAT_006d94e8 == '\0') {
          if (((DAT_00584ec0 != 3) && (DAT_006da294 == '\0')) && (DAT_005fd08c == 0)) {
            if (DAT_005846e4 != 5) {
              uStack_14 = (uint)DAT_00584ea0;
              uStack_10 = 0x80;
              uStack_18 = 0x54b6ef;
              sub_545F90();
            }
            uStack_10 = 8;
            uStack_14 = 0xffffff81;
            uStack_18 = 0;
            uStack_1c = 0x54b6fd;
            sub_546170();
            if (DAT_00584640 == 0) {
              DAT_00584640 = 1;
              uStack_10 = 0x54b7b8;
              sub_4267E0();
              if (DAT_00584640 != 0) {
                uStack_10 = 0x54b7ca;
                sub_545E30();
                DAT_005863fc = DAT_005fcf20;
                goto LAB_0054b728;
              }
            }
            else {
              DAT_00584640 = 0;
            }
            DAT_005fcf20 = DAT_005863fc;
            uStack_10 = 0x54b728;
            sub_545EB0();
          }
        }
        else if (DAT_00581d74 == 0) {
          _DAT_006d9844 = 1;
        }
      }
    }
  }
LAB_0054b728:
  uStack_10 = 0x54b72d;
  sub_40DB70();
  if (DAT_005fd090 != 0) {
    DAT_00584640 = 0;
  }
  uStack_10 = 0x54b745;
  sub_425BB0();
  if (DAT_00584640 == 0) {
    iVar1 = 0;
    DAT_006d9ce8 = 0;
    if (0 < DAT_005724d4) {
      do {
        if (DAT_005846e4 == 4) {
          uStack_10 = 0;
          uStack_14 = 0x54b776;
          sub_419E00();
        }
        uStack_10 = 0x54b77e;
        sub_425C00();
        uStack_10 = 0x54b783;
        sub_54C4A0();
        uStack_10 = 0x54b788;
        sub_4287C0();
        DAT_006d9ce8 = DAT_006d9ce8 + 1;
        iVar1 = iVar1 + 1;
      } while (iVar1 < DAT_005724d4);
      uStack_10 = 0x54b7a4;
      sub_54BAD0();
      uStack_10 = 0x54b7a9;
      sub_41E020();
      return;
    }
  }
  else {
    uStack_10 = 0x54b7e0;
    sub_425C00();
  }
  uStack_10 = 0x54b7e5;
  sub_54BAD0();
  uStack_10 = 0x54b7ea;
  sub_41E020();
  return;
}

