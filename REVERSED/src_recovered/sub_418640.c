/* Selected Ghidra export at 00418640. */

undefined4 sub_418640(void)

{
  undefined2 extraout_var;
  
  if (DAT_00571e6c == 2) {
    if (((byte)DAT_005fcf08 & 0x80) == 0) {
      if (DAT_00584ea0 < 0x80) {
        DAT_00584ea0 = DAT_00584ea0 + 0x10;
        if (DAT_005846e4 == 5) {
          DAT_006da2fc = 0x6000;
        }
        else {
          sub_546170(0,0xffffff80,8);
        }
      }
    }
    else {
      DAT_00584ea0 = DAT_00584ea0 + -0x10;
      if (DAT_005846e4 == 5) {
        DAT_006da2fc = 0x7000;
      }
      else {
        sub_546170(0,0xffffff80,8);
      }
    }
    if (DAT_00584ea0 < 0) {
      DAT_006da2fc = 0x8000;
      DAT_00584ea0 = 0;
    }
    else if (0x80 < DAT_00584ea0) {
      DAT_00584ea0 = 0x80;
    }
    sub_545F90(DAT_00584ea0,0x80);
    sub_405870(s_SoundVolume_00571f30,(int)DAT_00584ea0,0);
  }
  if (DAT_00571e6c == 3) {
    if (((byte)DAT_005fcf08 & 0x80) == 0) {
      if (DAT_00584ea2 < 0x80) {
        DAT_00584ea2 = DAT_00584ea2 + 0x10;
        if (DAT_005846e4 == 5) {
          DAT_006da2fc = 0x9000;
        }
        else {
          sub_546170(0,0xffffff80,8);
        }
      }
    }
    else {
      DAT_00584ea2 = DAT_00584ea2 + -0x10;
      if (DAT_005846e4 == 5) {
        DAT_006da2fc = 0xa000;
      }
      else {
        sub_546170(0,0xffffff80,8);
      }
    }
    if (DAT_00584ea2 < 0) {
      DAT_006da2fc = 0xb000;
      DAT_00584ea2 = 0;
    }
    else if (0x80 < DAT_00584ea2) {
      DAT_00584ea2 = 0x80;
    }
    sub_546000(DAT_00584ea2,0x80);
    sub_405870(s_MusicVolume_00571f48,(int)DAT_00584ea2,0);
    sub_545F90(CONCAT22(extraout_var,DAT_00584ea2),0x80);
  }
  return 0;
}

