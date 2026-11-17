/* sub_21101200 @ 21101200   195 bytes */

undefined4 sub_21101200(void)

{
  int iVar1;
  UINT uMode;
  bool bVar2;
  
  iVar1 = DAT_2111558c + 1;
  bVar2 = DAT_2111558c == 0;
  DAT_2111558c = iVar1;
  if (bVar2) {
    uMode = SetErrorMode(0x8000);
    DAT_21115590 = LoadLibraryA(s_DSOUND_DLL_21114080);
    SetErrorMode(uMode);
    Sleep(1);
    if (DAT_21115590 == (HMODULE)0x0) {
      GetLastError();
      DAT_2111558c = DAT_2111558c + -1;
      return 0;
    }
    DAT_211155a0 = GetProcAddress(DAT_21115590,s_DirectSoundCreate_2111406c);
    DAT_211155a4 = GetProcAddress(DAT_21115590,s_DirectSoundEnumerateA_21114054);
    DAT_211155a8 = GetProcAddress(DAT_21115590,s_DirectSoundCaptureEnumerateA_21114034);
    if ((DAT_211155a0 == (FARPROC)0x0) || (DAT_211155a4 == (FARPROC)0x0)) {
      FreeLibrary(DAT_21115590);
      DAT_2111558c = DAT_2111558c + -1;
      return 0;
    }
  }
  return 1;
}

