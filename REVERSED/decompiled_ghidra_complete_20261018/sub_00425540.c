/* sub_425540 @ 00425540   95 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_425540(void)

{
  int iVar1;
  uint uVar2;
  
  sub_4255A0();
  uVar2 = 0;
  *(undefined1 *)(DAT_005fcf70 + 0xb) = 0x7f;
  if (DAT_005fcf6c != 0) {
    iVar1 = 0;
    do {
      uVar2 = uVar2 + 1;
      *(undefined1 *)(iVar1 + 0xb + DAT_005fcf70) = 0x7f;
      *(undefined1 *)(iVar1 + 7 + DAT_005fcf70) = 0;
      *(undefined1 *)(iVar1 + 8 + DAT_005fcf70) = 0;
      iVar1 = iVar1 + 0xc;
    } while (uVar2 < DAT_005fcf6c);
  }
  DAT_005fcf64 = 0;
  DAT_005fcf68 = 0;
  _DAT_005fcf14 = 0;
  return;
}

