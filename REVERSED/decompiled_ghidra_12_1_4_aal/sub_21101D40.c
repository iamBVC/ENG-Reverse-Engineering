/* sub_21101D40 @ 21101d40   65 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint sub_21101D40(void)

{
  if (DAT_211155a4 != (code *)0x0) {
    (*DAT_211155a4)(sub_21101C20,&DAT_21115598);
    _DAT_21115570 = _DAT_21115570 | 4;
  }
  if (DAT_211155a8 != (code *)0x0) {
    (*DAT_211155a8)(sub_21101C20,&DAT_2111559c);
    _DAT_21115570 = _DAT_21115570 | 8;
  }
  return _DAT_21115570 & 6;
}

