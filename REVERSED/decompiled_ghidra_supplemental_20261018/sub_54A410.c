/* Selected Ghidra export at 0054a410. */

undefined4 sub_54A410(void)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (((DAT_005fcf08 & 0x10) != 0) && (DAT_006d9c00 != '\0')) {
    DAT_006d9c00 = '\0';
    DAT_005863f4 = DAT_00584650;
    sub_546170(0,0xffffff80,8);
  }
  if ((DAT_005fcf08 & 0x40) == 0) {
LAB_0054a474:
    if (DAT_006d9c00 == '\0') {
      sub_436740((&PTR_s_Continua_0057bb90)[DAT_00584f04],0x82,0xa0,0xa0,0xa0);
      uVar5 = 0x50;
      uVar4 = 0x50;
      uVar3 = 0x50;
      puVar2 = (&PTR_DAT_0057bba0)[DAT_00584f04];
      goto LAB_0054a4fe;
    }
  }
  else if (DAT_006d9c00 == '\0') {
    DAT_006d9c00 = '\x01';
    DAT_005863f4 = DAT_00584650;
    sub_546170(0,0xffffff80,8);
    goto LAB_0054a474;
  }
  sub_436740((&PTR_s_Continua_0057bb90)[DAT_00584f04],0x82,0x50,0x50,0x50);
  uVar5 = 0xa0;
  uVar4 = 0xa0;
  uVar3 = 0xa0;
  puVar2 = (&PTR_DAT_0057bba0)[DAT_00584f04];
LAB_0054a4fe:
  sub_436740(puVar2,0x96,uVar3,uVar4,uVar5);
  if (DAT_0058372c == 0) {
    if ((DAT_005fcf08 & 0x4000) != 0) {
      sub_415390(1);
      sub_546170(0,0xffffff81,8);
    }
  }
  else {
    iVar1 = sub_414FB0();
    if (iVar1 != 0) {
      sub_546CC0();
      DAT_00586430 = 0;
      sub_546990(DAT_006d94b4);
      sub_5464D0();
      sub_43C940();
      if (DAT_006d9c00 == '\x01') {
        DAT_005846e4 = 2;
        DAT_00584700 = 2;
        sub_415390(1);
        return 1;
      }
      DAT_005846e4 = 3;
      DAT_00584700 = 3;
      return 1;
    }
  }
  return 0;
}

