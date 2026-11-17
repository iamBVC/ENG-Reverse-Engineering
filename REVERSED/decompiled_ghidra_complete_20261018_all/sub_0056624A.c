/* sub_56624A @ 0056624a   177 bytes */

undefined4 * sub_56624A(void)

{
  undefined4 *puVar1;
  LPVOID pvVar2;
  
  if (DAT_006db914 == DAT_006db904) {
    pvVar2 = HeapReAlloc(DAT_006db91c,0,DAT_006db918,(DAT_006db904 * 5 + 0x50) * 4);
    if (pvVar2 == (LPVOID)0x0) {
      return (undefined4 *)0x0;
    }
    DAT_006db904 = DAT_006db904 + 0x10;
    DAT_006db918 = pvVar2;
  }
  puVar1 = (undefined4 *)((int)DAT_006db918 + DAT_006db914 * 0x14);
  pvVar2 = HeapAlloc(DAT_006db91c,8,0x41c4);
  puVar1[4] = pvVar2;
  if (pvVar2 != (LPVOID)0x0) {
    pvVar2 = VirtualAlloc((LPVOID)0x0,0x100000,0x2000,4);
    puVar1[3] = pvVar2;
    if (pvVar2 != (LPVOID)0x0) {
      puVar1[2] = 0xffffffff;
      *puVar1 = 0;
      puVar1[1] = 0;
      DAT_006db914 = DAT_006db914 + 1;
      *(undefined4 *)puVar1[4] = 0xffffffff;
      return puVar1;
    }
    HeapFree(DAT_006db91c,0,(LPVOID)puVar1[4]);
  }
  return (undefined4 *)0x0;
}

