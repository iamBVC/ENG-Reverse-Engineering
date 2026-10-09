/* sub_4284A0 @ 004284a0   42 bytes */

void sub_4284A0(void)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (DAT_006da320 != 0) {
    iVar1 = 0;
    do {
      uVar2 = uVar2 + 1;
      *(undefined1 *)(iVar1 + 0x10 + DAT_006d94b8) = 0;
      iVar1 = iVar1 + 0x20;
    } while (uVar2 < DAT_006da320);
  }
  return;
}

