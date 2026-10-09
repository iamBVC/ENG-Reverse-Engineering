/* sub_5691E5 @ 005691e5   57 bytes */

void sub_5691E5(void)

{
  if ((DAT_006da3b8 == 1) || ((DAT_006da3b8 == 0 && (DAT_0057c7c4 == 1)))) {
    sub_56921E(0xfc);
    if (DAT_006da540 != (code *)0x0) {
      (*DAT_006da540)();
    }
    sub_56921E(0xff);
  }
  return;
}

