/* sub_546CC0 @ 00546cc0   131 bytes */

void sub_546CC0(void)

{
  int iVar1;
  
  if (DAT_006d94a4 != 0) {
    sub_547E40(DAT_006d9498 + 0x10,0,DAT_006d94a4,0);
    sub_545C00();
    if (((DAT_006d94a4 != 0) && (DAT_006d94a4 != -0x80)) &&
       (iVar1 = *(int *)(DAT_006d94a4 + 0x88), iVar1 != 0)) {
      _AAL_StopVoice_4(*(undefined4 *)(iVar1 + 0x14));
      _AAL_FreeVoice_4(*(undefined4 *)(iVar1 + 0x14));
      *(undefined4 *)(iVar1 + 0x14) = 0;
    }
    if (DAT_006d948c != 0) {
      _AAL_UnloadFile_4(DAT_006d948c);
      DAT_006d948c = 0;
    }
    DAT_006d94a4 = 0;
  }
  return;
}

