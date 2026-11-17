/* sub_21106280 @ 21106280   86 bytes */

HANDLE sub_21106280(LPCSTR param_1,DWORD param_2,DWORD param_3)

{
  HANDLE pvVar1;
  bool bVar2;
  DWORD dwCreationDisposition;
  
  bVar2 = param_2 != 0x80000000;
  if (bVar2) {
    dwCreationDisposition = 2;
  }
  else {
    dwCreationDisposition = 3;
    param_2 = 0x80000000;
  }
  pvVar1 = CreateFileA(param_1,param_2,(uint)!bVar2,(LPSECURITY_ATTRIBUTES)0x0,dwCreationDisposition
                       ,param_3,(HANDLE)0x0);
  if (pvVar1 == (HANDLE)0xffffffff) {
    AAL_SetError(s_Unable_to_open_file_21114530);
  }
  return pvVar1;
}

