/* sub_40FD80 @ 0040fd80   140 bytes */

undefined4 sub_40FD80(void)

{
  char cVar1;
  
  sub_40FE10();
  cVar1 = sub_410550(DAT_00583420);
  if (cVar1 != '\0') {
    cVar1 = sub_410700(DAT_00583428,DAT_0058342c,DAT_00583420,DAT_00583424);
    if (cVar1 != '\0') {
      cVar1 = sub_411000(DAT_00583424);
      if (cVar1 != '\0') {
        DAT_00582cc8 = 1;
        sub_4114F0(DAT_00583420,DAT_00583424,DAT_00583428,DAT_0058342c,0);
        sub_411620();
        return 1;
      }
    }
  }
  sub_40FE10();
  return 0;
}

