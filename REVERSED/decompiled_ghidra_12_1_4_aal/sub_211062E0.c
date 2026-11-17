/* sub_211062E0 @ 211062e0   180 bytes */

undefined4 __thiscall sub_211062E0(void *this,LPCSTR param_1)

{
  HANDLE hFile;
  HANDLE hFileMappingObject;
  LPVOID pvVar1;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_21112340;
  puStack_10 = &LAB_2110d648;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  hFile = sub_21106280(param_1,0x80000000,0x8000080);
  local_8 = 0xffffffff;
  if (hFile != (HANDLE)0xffffffff) {
    hFileMappingObject = CreateFileMappingA(hFile,(LPSECURITY_ATTRIBUTES)0x0,2,0,0,(LPCSTR)0x0);
    CloseHandle(hFile);
    if (hFileMappingObject != (HANDLE)0xffffffff) {
      pvVar1 = MapViewOfFile(hFileMappingObject,4,0,0,0);
      *(LPVOID *)((int)this + 0x10) = pvVar1;
      CloseHandle(hFileMappingObject);
      ExceptionList = local_14;
      return *(undefined4 *)((int)this + 0x10);
    }
  }
  ExceptionList = local_14;
  return 0;
}

