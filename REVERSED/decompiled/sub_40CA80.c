/* sub_40CA80 @ 0040ca80   37 bytes */

void sub_40CA80(void)

{
  if ((DAT_006da5a8 & 1) == 0) {
    DAT_006da5a8 = DAT_006da5a8 | 1;
  }
  sub_5626AD(&DAT_00402740);
  return;
}

