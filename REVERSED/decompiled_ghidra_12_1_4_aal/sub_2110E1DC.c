/* sub_2110E1DC @ 2110e1dc   35 bytes */

void sub_2110E1DC(void)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_21115a40;
  do {
    if ((LPVOID)*puVar1 != (LPVOID)0x0) {
      sub_2110D99D((LPVOID)*puVar1);
      *puVar1 = 0;
    }
    puVar1 = puVar1 + 1;
  } while ((int)puVar1 < 0x21115b40);
  return;
}

