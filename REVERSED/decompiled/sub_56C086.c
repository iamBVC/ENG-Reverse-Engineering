/* sub_56C086 @ 0056c086   137 bytes */

int sub_56C086(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_006da584 == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if (hModule != (HMODULE)0x0) {
      DAT_006da584 = GetProcAddress(hModule,"MessageBoxA");
      if (DAT_006da584 != (FARPROC)0x0) {
        DAT_006da588 = GetProcAddress(hModule,"GetActiveWindow");
        DAT_006da58c = GetProcAddress(hModule,"GetLastActivePopup");
        goto LAB_0056c0d5;
      }
    }
    iVar1 = 0;
  }
  else {
LAB_0056c0d5:
    if (DAT_006da588 != (FARPROC)0x0) {
      iVar1 = (*DAT_006da588)();
      if ((iVar1 != 0) && (DAT_006da58c != (FARPROC)0x0)) {
        iVar1 = (*DAT_006da58c)(iVar1);
      }
    }
    iVar1 = (*DAT_006da584)(iVar1,param_1,param_2,param_3);
  }
  return iVar1;
}

