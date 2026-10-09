/* sub_40E0A0 @ 0040e0a0   29 bytes */

void sub_40E0A0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_0058226c;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_005821e0;
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}

