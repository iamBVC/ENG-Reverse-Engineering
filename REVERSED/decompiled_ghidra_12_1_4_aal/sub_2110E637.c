/* sub_2110E637 @ 2110e637   57 bytes */

void sub_2110E637(void)

{
  if ((DAT_21115608 == 1) || ((DAT_21115608 == 0 && (DAT_2111560c == 1)))) {
    sub_2110E670(0xfc);
    if (DAT_21115774 != (code *)0x0) {
      (*DAT_21115774)();
    }
    sub_2110E670(0xff);
  }
  return;
}

