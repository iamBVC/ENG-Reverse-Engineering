/* sub_21110495 @ 21110495   137 bytes */

int __cdecl sub_21110495(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_211157b4 == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if (hModule != (HMODULE)0x0) {
      DAT_211157b4 = GetProcAddress(hModule,"MessageBoxA");
      if (DAT_211157b4 != (FARPROC)0x0) {
        DAT_211157b8 = GetProcAddress(hModule,"GetActiveWindow");
        DAT_211157bc = GetProcAddress(hModule,"GetLastActivePopup");
        goto LAB_211104e4;
      }
    }
    iVar1 = 0;
  }
  else {
LAB_211104e4:
    if (DAT_211157b8 != (FARPROC)0x0) {
      iVar1 = (*DAT_211157b8)();
      if ((iVar1 != 0) && (DAT_211157bc != (FARPROC)0x0)) {
        iVar1 = (*DAT_211157bc)(iVar1);
      }
    }
    iVar1 = (*DAT_211157b4)(iVar1,param_1,param_2,param_3);
  }
  return iVar1;
}

