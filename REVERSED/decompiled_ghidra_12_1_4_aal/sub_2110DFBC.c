/* sub_2110DFBC @ 2110dfbc   117 bytes */

void sub_2110DFBC(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  if (0 < DAT_21115a38) {
    puVar2 = (undefined4 *)((int)DAT_21115a3c + 0xc);
    do {
      VirtualFree((LPVOID)*puVar2,0x100000,0x4000);
      VirtualFree((LPVOID)*puVar2,0,0x8000);
      HeapFree(DAT_21115b44,0,(LPVOID)puVar2[1]);
      puVar2 = puVar2 + 5;
      iVar1 = iVar1 + 1;
    } while (iVar1 < DAT_21115a38);
  }
  HeapFree(DAT_21115b44,0,DAT_21115a3c);
  HeapDestroy(DAT_21115b44);
  return;
}

