/* sub_546B70 @ 00546b70   324 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_546B70(int param_1)

{
  int iVar1;
  undefined4 local_108;
  undefined1 local_104 [260];
  
  local_108 = 0xffffffff;
  if (DAT_005834dc != 0) {
    if (param_1 == 0) {
      sub_546CC0();
      return;
    }
    if (DAT_006d94a4 != 0) {
      sub_546CC0();
      sub_426500(s_Stream__Music_is_already_playing_00578e58);
    }
    if ((undefined *)(*(int *)(&DAT_00578960 + param_1 * 0x14) + 8) == &DAT_0057f834) {
      sub_426500(s_Stream__Invalid_stream_file_00578e84);
      return;
    }
    sub_562717(local_104,s__s_ASF_00578e7c,
               (undefined *)(*(int *)(&DAT_00578960 + param_1 * 0x14) + 8));
    iVar1 = sub_415690(s_Music_00578e48,local_104);
    if (iVar1 != 0) {
      DAT_006d948c = _AAL_LoadFile_8(iVar1,0x40);
      if (DAT_006d948c != 0) {
        _DAT_006d9478 = _AAL_GetDataSize_4(DAT_006d948c);
        iVar1 = _AAL_GetSampleRate_4(DAT_006d948c);
        iVar1 = iVar1 << 0xc;
        _DAT_006d947e = 0x7f;
        _DAT_006d947c =
             ((short)(iVar1 / 0xac44) + (short)(iVar1 >> 0x1f)) -
             (short)((longlong)iVar1 * 0x2f8df18f >> 0x3f);
        _DAT_006d9480 = 0x2400;
        _DAT_006d9482 = 1;
        DAT_006d94a4 = sub_5487A0(&DAT_006d9478,0,0x2400,&local_108);
        if (DAT_006d94a4 != 0) {
          sub_5489C0(DAT_006d9498 + 0x10,DAT_006d94a4);
        }
      }
    }
  }
  return;
}

