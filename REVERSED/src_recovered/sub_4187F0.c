/* Selected Ghidra export at 004187f0. */

undefined4 sub_4187F0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = sub_5460C0();
  if (((byte)DAT_005fcf08 & 0x80) == 0) {
    sub_546170(0,0xffffff80,8);
    iVar3 = 0;
    do {
      switch(iVar1) {
      case 1:
        iVar1 = 2;
        break;
      case 2:
        iVar1 = 6;
        break;
      case 3:
        iVar1 = 1;
        break;
      case 4:
        iVar1 = 3;
        break;
      case 5:
        iVar1 = 4;
        break;
      case 6:
        iVar1 = 5;
      }
      sub_5460A0(iVar1);
      iVar2 = sub_5460C0();
    } while ((iVar2 != iVar1) && (iVar3 = iVar3 + 1, iVar3 < 6));
  }
  else {
    sub_546170(0,0xffffff80,8);
    iVar3 = 0;
    do {
      switch(iVar1) {
      case 1:
        iVar1 = 3;
        break;
      case 2:
        iVar1 = 1;
        break;
      case 3:
        iVar1 = 4;
        break;
      case 4:
        iVar1 = 5;
        break;
      case 5:
        iVar1 = 6;
        break;
      case 6:
        iVar1 = 2;
      }
      sub_5460A0(iVar1);
      iVar2 = sub_5460C0();
    } while ((iVar2 != iVar1) && (iVar3 = iVar3 + 1, iVar3 < 6));
  }
  sub_405870(s_SpeakerMode_00571f3c,(int)DAT_00584ea6,0);
  sub_4184E0(iVar1);
  return 0;
}

