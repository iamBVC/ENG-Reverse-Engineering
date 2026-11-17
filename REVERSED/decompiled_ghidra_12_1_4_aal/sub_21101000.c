/* sub_21101000 @ 21101000   136 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall sub_21101000(HMODULE param_1)

{
  BOOL BVar1;
  int iVar2;
  
  BVar1 = QueryPerformanceFrequency((LARGE_INTEGER *)&DAT_21115578);
  if (BVar1 != 0) {
    _DAT_21115570 = _DAT_21115570 | 1;
    QueryPerformanceCounter((LARGE_INTEGER *)&DAT_21115580);
  }
  DAT_21115588 = operator_new(0x7f);
  GetModuleFileNameA(param_1,DAT_21115588,0x7f);
  for (iVar2 = lstrlenA(DAT_21115588);
      ((iVar2 != 0 && (DAT_21115588[iVar2] != '\\')) && (DAT_21115588[iVar2] != ':'));
      iVar2 = iVar2 + -1) {
  }
  DAT_21115588[iVar2] = '\0';
  lstrcatA(DAT_21115588,&DAT_21114030);
  return 1;
}

