/* sub_41D980 @ 0041d980   59 bytes */

bool sub_41D980(void)

{
  int iVar1;
  DWORD *pDVar2;
  _OSVERSIONINFOA local_94;
  
  pDVar2 = &local_94.dwMajorVersion;
  for (iVar1 = 0x24; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pDVar2 = 0;
    pDVar2 = pDVar2 + 1;
  }
  local_94.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_94);
  return local_94.dwPlatformId == 2;
}

