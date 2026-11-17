/* sub_56921E @ 0056921e   339 bytes */

void sub_56921E(DWORD param_1)

{
  undefined4 *puVar1;
  DWORD *pDVar2;
  DWORD DVar3;
  size_t sVar4;
  HANDLE hFile;
  int iVar5;
  char acStackY_1e3 [7];
  undefined1 *puStackY_1dc;
  char *pcStackY_1d8;
  undefined4 uStackY_1d4;
  undefined1 *puStackY_1d0;
  undefined4 uStackY_1cc;
  undefined1 *puStackY_1c8;
  undefined *puStackY_1c4;
  LPCVOID lpBuffer;
  LPDWORD lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  CHAR local_1a8 [260];
  undefined1 local_a4 [160];
  
  iVar5 = 0;
  pDVar2 = &DAT_0057cf68;
  do {
    if (param_1 == *pDVar2) break;
    pDVar2 = pDVar2 + 2;
    iVar5 = iVar5 + 1;
  } while ((int)pDVar2 < 0x57cff8);
  if (param_1 == (&DAT_0057cf68)[iVar5 * 2]) {
    if ((DAT_006da3b8 == 1) || ((DAT_006da3b8 == 0 && (DAT_0057c7c4 == 1)))) {
      lpNumberOfBytesWritten = &param_1;
      puVar1 = (undefined4 *)(iVar5 * 8 + 0x57cf6c);
      lpOverlapped = (LPOVERLAPPED)0x0;
      sVar4 = _strlen((char *)*puVar1);
      lpBuffer = (LPCVOID)*puVar1;
      puStackY_1c4 = (undefined *)0x569367;
      hFile = GetStdHandle(0xfffffff4);
      puStackY_1c4 = (undefined *)0x56936e;
      WriteFile(hFile,lpBuffer,sVar4,lpNumberOfBytesWritten,lpOverlapped);
    }
    else if (param_1 != 0xfc) {
      DVar3 = GetModuleFileNameA((HMODULE)0x0,local_1a8,0x104);
      if (DVar3 == 0) {
        sub_569990();
      }
      sVar4 = _strlen(local_1a8);
      if (0x3c < sVar4 + 1) {
        sVar4 = _strlen(local_1a8);
        puStackY_1c4 = (undefined *)0x5692e8;
        _strncpy(acStackY_1e3 + sVar4,"...",3);
      }
      sub_569990();
      puStackY_1c4 = (undefined *)0x569309;
      sub_5699A0();
      puStackY_1c8 = local_a4;
      puStackY_1c4 = &DAT_0056ebe8;
      uStackY_1cc = 0x56931a;
      sub_5699A0();
      uStackY_1cc = *(undefined4 *)(iVar5 * 8 + 0x57cf6c);
      puStackY_1d0 = local_a4;
      uStackY_1d4 = 0x56932c;
      sub_5699A0();
      uStackY_1d4 = 0x12010;
      puStackY_1dc = local_a4;
      pcStackY_1d8 = "Microsoft Visual C++ Runtime Library";
      acStackY_1e3[3] = 'B';
      acStackY_1e3[4] = -0x6d;
      acStackY_1e3[5] = 'V';
      acStackY_1e3[6] = '\0';
      sub_56C086();
    }
  }
  return;
}

