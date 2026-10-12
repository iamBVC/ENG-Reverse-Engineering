/* sub_40CEE0 @ 0040cee0   37 bytes */

void sub_40CEE0(void)

{
  if ((DAT_006da5a8 & 1) == 0) {
    DAT_006da5a8 = DAT_006da5a8 | 1;
  }
  sub_5626AD(&DAT_00402740);
  return;
}

