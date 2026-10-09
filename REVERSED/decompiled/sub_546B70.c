/* sub_546B70 @ 00546b70   324 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_546B70(int param_1)

{
  int iVar1;
  undefined1 *puStack_118;
  char *pcStack_114;
  char *pcStack_110;
  undefined1 local_104 [260];
  
  if (DAT_005834dc != 0) {
    if (param_1 == 0) {
      pcStack_110 = (char *)0x546b9c;
      sub_546CC0();
      return;
    }
    if (DAT_006d94a4 != 0) {
      pcStack_110 = (char *)0x546bb2;
      sub_546CC0();
      pcStack_110 = s_Stream__Music_is_already_playing_00578e58;
      pcStack_114 = (char *)0x546bbc;
      sub_426500();
    }
    pcStack_110 = (char *)(*(int *)(&DAT_00578960 + param_1 * 0x14) + 8);
    if (pcStack_110 == &DAT_0057f834) {
      pcStack_110 = s_Stream__Invalid_stream_file_00578e84;
      pcStack_114 = (char *)0x546bdd;
      sub_426500();
      return;
    }
    puStack_118 = local_104;
    pcStack_114 = s__s_ASF_00578e7c;
    sub_562717();
    pcStack_114 = (char *)sub_415690(s_Music_00578e48,local_104);
    if (pcStack_114 != (char *)0x0) {
      pcStack_110 = (char *)0x40;
      puStack_118 = (undefined1 *)0x546c1b;
      DAT_006d948c = (undefined1 *)_AAL_LoadFile_8();
      if (DAT_006d948c != (undefined1 *)0x0) {
        puStack_118 = DAT_006d948c;
        _DAT_006d9478 = _AAL_GetDataSize_4();
        iVar1 = _AAL_GetSampleRate_4(DAT_006d948c);
        iVar1 = iVar1 << 0xc;
        _DAT_006d947e = 0x7f;
        _DAT_006d947c =
             ((short)(iVar1 / 0xac44) + (short)(iVar1 >> 0x1f)) -
             (short)((longlong)iVar1 * 0x2f8df18f >> 0x3f);
        _DAT_006d9480 = 0x2400;
        _DAT_006d9482 = 1;
        DAT_006d94a4 = sub_5487A0(&DAT_006d9478,0,0x2400,&puStack_118);
        if (DAT_006d94a4 != 0) {
          sub_5489C0(DAT_006d9498 + 0x10,DAT_006d94a4);
        }
      }
    }
  }
  return;
}

