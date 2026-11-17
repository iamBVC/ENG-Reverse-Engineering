/* sub_21108E50 @ 21108e50   220 bytes */

void __thiscall sub_21108E50(void *this,LPCSTR param_1)

{
  int iVar1;
  int iVar2;
  HANDLE hFindFile;
  BOOL BVar3;
  CHAR local_244 [260];
  _WIN32_FIND_DATAA local_140;
  
  iVar1 = lstrlenA(DAT_21115588);
  iVar2 = lstrlenA(param_1);
  if (iVar1 + iVar2 < 0x104) {
    lstrcpyA(local_244,DAT_21115588);
    lstrcatA(local_244,param_1);
    hFindFile = FindFirstFileA(local_244,&local_140);
    if ((hFindFile != (HANDLE)0x0) && (hFindFile != (HANDLE)0xffffffff)) {
      do {
        lstrcpyA(local_244,DAT_21115588);
        lstrcatA(local_244,local_140.cFileName);
        sub_21108F30(this,local_244);
        BVar3 = FindNextFileA(hFindFile,&local_140);
      } while (BVar3 != 0);
      FindClose(hFindFile);
    }
    return;
  }
  OutputDebugStringA(s_Provider_search_path_exceeds_max_21114634);
  return;
}

