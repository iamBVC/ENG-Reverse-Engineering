/* sub_556340 @ 00556340   113 bytes */

undefined4 sub_556340(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  int iVar2;
  int *piVar3;
  int local_4;
  
  hModule = LoadLibraryA(s_DDRAW_DLL_00579a7c);
  if (hModule == (HMODULE)0x0) {
    FreeLibrary((HMODULE)0x0);
    return 0;
  }
  pFVar1 = GetProcAddress(hModule,s_DirectDrawCreateEx_00579a68);
  if (pFVar1 == (FARPROC)0x0) {
    FreeLibrary(hModule);
    return 0;
  }
  piVar3 = &local_4;
  iVar2 = (*pFVar1)(0,piVar3,&DAT_0056e70c,0);
  if (iVar2 < 0) {
    FreeLibrary(hModule);
    return 0;
  }
  (**(code **)(*piVar3 + 8))(piVar3);
  FreeLibrary(hModule);
  return 1;
}

