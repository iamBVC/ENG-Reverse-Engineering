/* sub_4170E0 @ 004170e0   110 bytes */

void sub_4170E0(void)

{
  if (((DAT_00583b7c != 0) && (DAT_00583b70 == &DAT_00571e60)) && (DAT_00571e6c == 3)) {
    DAT_00583b7c = 0;
    if (DAT_005846e4 == 5) {
      sub_546CC0();
      DAT_00586430 = 0;
    }
    else {
      sub_546DB0();
    }
  }
  sub_545F90(DAT_00584ea0,0x80);
  sub_405870(s_SoundVolume_00571f30,(int)DAT_00584ea0,0);
  return;
}

