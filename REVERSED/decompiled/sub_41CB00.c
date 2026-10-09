/* sub_41CB00 @ 0041cb00   150 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41CB00(void)

{
  undefined2 extraout_var;
  
  DAT_00584ea6 = 1;
  sub_4057C0(s_SoundVolume_00571f30,0x43000000,0);
  DAT_00584ea0 = __ftol();
  sub_4057C0(s_MusicVolume_00571f48,0x43000000,0);
  DAT_00584ea2 = __ftol();
  _DAT_00584ea4 = 0x80;
  DAT_00585218 = 0;
  _DAT_00584f08 = 0;
  DAT_00585219 = 0;
  sub_545F90(DAT_00584ea0,0x80);
  sub_5460A0((int)DAT_00584ea6);
  sub_546000(CONCAT22(extraout_var,DAT_00584ea2),0x80);
  return;
}

