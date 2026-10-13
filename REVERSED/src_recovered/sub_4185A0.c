/* Selected Ghidra export at 004185a0. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_4185A0(void)

{
  undefined2 extraout_var;
  undefined4 uVar1;
  
  DAT_00584ea6 = 1;
  DAT_00584ea0 = 0x7f;
  DAT_00584ea2 = 0x60;
  _DAT_00584ea4 = 0x7f;
  sub_545F90(0x7f,0x80);
  sub_546000(CONCAT22(extraout_var,DAT_00584ea2),0x80);
  sub_405870(s_SoundVolume_00571f30,(int)DAT_00584ea0,0);
  sub_405870(s_MusicVolume_00571f48,(int)DAT_00584ea2,0);
  sub_405870(s_SpeakerMode_00571f3c,(int)DAT_00584ea6,0);
  sub_5460A0(1);
  uVar1 = sub_5460C0();
  sub_4184E0(uVar1);
  return 0;
}

