/* sub_546A10 @ 00546a10   27 bytes */

void sub_546A10(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  sub_546990(0xffffffff);
  puVar2 = &DAT_006d91c0;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}

