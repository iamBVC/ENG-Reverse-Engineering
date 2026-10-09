/* sub_428D60 @ 00428d60   25 bytes */

void sub_428D60(void)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_005fd598;
  do {
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1 = puVar1 + 0x10b;
  } while ((int)puVar1 < 0x5fe648);
  return;
}

