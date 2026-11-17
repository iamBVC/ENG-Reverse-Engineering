/* sub_546830 @ 00546830   170 bytes */

LPVOID sub_546830(undefined4 param_1)

{
  HANDLE hFile;
  HANDLE hFileMappingObject;
  LPVOID pvVar1;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0056e500;
  puStack_10 = &LAB_00563e08;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  hFile = (HANDLE)sub_546900(param_1,0x8000080);
  local_8 = 0xffffffff;
  if (hFile != (HANDLE)0xffffffff) {
    hFileMappingObject = CreateFileMappingA(hFile,(LPSECURITY_ATTRIBUTES)0x0,2,0,0,(LPCSTR)0x0);
    CloseHandle(hFile);
    if (hFileMappingObject != (HANDLE)0xffffffff) {
      pvVar1 = MapViewOfFile(hFileMappingObject,4,0,0,0);
      CloseHandle(hFileMappingObject);
      ExceptionList = local_14;
      return pvVar1;
    }
  }
  ExceptionList = local_14;
  return (LPVOID)0x0;
}

