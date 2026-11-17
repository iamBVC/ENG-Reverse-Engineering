/* sub_2110EE7B @ 2110ee7b   177 bytes */

undefined4 * sub_2110EE7B(void)

{
  undefined4 *puVar1;
  LPVOID pvVar2;
  
  if (DAT_21115a38 == DAT_21115a28) {
    pvVar2 = HeapReAlloc(DAT_21115b44,0,DAT_21115a3c,(DAT_21115a28 * 5 + 0x50) * 4);
    if (pvVar2 == (LPVOID)0x0) {
      return (undefined4 *)0x0;
    }
    DAT_21115a28 = DAT_21115a28 + 0x10;
    DAT_21115a3c = pvVar2;
  }
  puVar1 = (undefined4 *)((int)DAT_21115a3c + DAT_21115a38 * 0x14);
  pvVar2 = HeapAlloc(DAT_21115b44,8,0x41c4);
  puVar1[4] = pvVar2;
  if (pvVar2 != (LPVOID)0x0) {
    pvVar2 = VirtualAlloc((LPVOID)0x0,0x100000,0x2000,4);
    puVar1[3] = pvVar2;
    if (pvVar2 != (LPVOID)0x0) {
      puVar1[2] = 0xffffffff;
      *puVar1 = 0;
      puVar1[1] = 0;
      DAT_21115a38 = DAT_21115a38 + 1;
      *(undefined4 *)puVar1[4] = 0xffffffff;
      return puVar1;
    }
    HeapFree(DAT_21115b44,0,(LPVOID)puVar1[4]);
  }
  return (undefined4 *)0x0;
}

