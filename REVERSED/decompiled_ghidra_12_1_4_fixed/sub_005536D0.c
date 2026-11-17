/* sub_5536D0 @ 005536d0   17 bytes */

void sub_5536D0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_006d9e8c;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}

