/* sub_546990 @ 00546990   127 bytes */

void sub_546990(void)

{
  int iVar1;
  
  if (DAT_006d94a0 != 0) {
    sub_547E40(DAT_006d9498 + 0x10,0,DAT_006d94a0,0);
    if ((DAT_006d94a0 != -0x80) && (iVar1 = *(int *)(DAT_006d94a0 + 0x88), iVar1 != 0)) {
      _AAL_StopVoice_4(*(undefined4 *)(iVar1 + 0x14));
      _AAL_FreeVoice_4(*(undefined4 *)(iVar1 + 0x14));
      *(undefined4 *)(iVar1 + 0x14) = 0;
    }
    sub_545C00();
    DAT_006d94a0 = 0;
    if (DAT_006d91d8 != (LPCVOID)0x0) {
      UnmapViewOfFile(DAT_006d91d8);
      DAT_006d91d8 = (LPCVOID)0x0;
    }
  }
  return;
}

