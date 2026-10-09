/* sub_4195D0 @ 004195d0   128 bytes */

void sub_4195D0(void)

{
  if ((((DAT_005846e4 == 9) || (DAT_005846e4 == 7)) || (DAT_005846e4 == 6)) || (DAT_005846e4 == 0xc)
     ) {
    sub_546CC0();
    DAT_00586430 = 0;
  }
  else {
    if (DAT_005846e4 == 0xf) {
      DAT_00586430 = 0x23;
      sub_546B70(0x23,0);
      return;
    }
    if ((DAT_005846e4 == 10) ||
       ((DAT_00584644 != 0 && (*(int *)(DAT_00584644 + 0x58) != DAT_00586430)))) {
      DAT_00586430 = 0x27;
      if (DAT_005846e4 != 10) {
        DAT_00586430 = *(undefined4 *)(DAT_00584644 + 0x58);
      }
      sub_546B70(DAT_00586430,0);
      return;
    }
  }
  return;
}

