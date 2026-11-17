/* sub_41C9F0 @ 0041c9f0   32 bytes */

void sub_41C9F0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (DAT_00584c28 != -1) {
    puVar2 = (undefined4 *)(&DAT_00585274 + DAT_00584c28 * 0x100);
    for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
  }
  return;
}

