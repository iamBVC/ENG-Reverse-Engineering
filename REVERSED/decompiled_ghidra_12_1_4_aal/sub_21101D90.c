/* sub_21101D90 @ 21101d90   107 bytes */

void sub_21101D90(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = DAT_21115598;
  while (puVar2 != (undefined4 *)0x0) {
    if ((LPVOID)puVar2[6] != (LPVOID)0x0) {
      sub_2110D4F4((LPVOID)puVar2[6]);
    }
    puVar1 = (undefined4 *)*puVar2;
    sub_2110D4F4(puVar2);
    puVar2 = puVar1;
  }
  DAT_21115598 = (undefined4 *)0x0;
  puVar2 = DAT_2111559c;
  while (puVar2 != (undefined4 *)0x0) {
    if ((LPVOID)puVar2[6] != (LPVOID)0x0) {
      sub_2110D4F4((LPVOID)puVar2[6]);
    }
    puVar1 = (undefined4 *)*puVar2;
    sub_2110D4F4(puVar2);
    puVar2 = puVar1;
  }
  DAT_2111559c = (undefined4 *)0x0;
  return;
}

