/* sub_41C5A0 @ 0041c5a0   122 bytes */

void sub_41C5A0(void)

{
  char *pcVar1;
  
  if (DAT_00584c28 == 0xffffffff) {
    DAT_00584c28 = 0;
    pcVar1 = &DAT_00585274;
    do {
      if (*pcVar1 != '\0') {
        if (DAT_00584c28 != 0xffffffff) goto LAB_0041c5db;
        break;
      }
      pcVar1 = pcVar1 + 0x100;
      DAT_00584c28 = DAT_00584c28 + 1;
    } while ((int)pcVar1 < 0x585574);
    DAT_00584c28 = 1;
  }
LAB_0041c5db:
  if ((((byte)DAT_005fcf30 & 0x80) == 0) || (DAT_00584c28 == 0)) {
    if ((((byte)DAT_005fcf30 & 0x20) == 0) || (1 < DAT_00584c28)) goto LAB_0041c610;
    DAT_00584c28 = DAT_00584c28 + 1;
  }
  else {
    DAT_00584c28 = DAT_00584c28 - 1;
  }
  sub_546170(0,0xffffff80,8);
LAB_0041c610:
  DAT_006da2fc = (DAT_00584c28 + 1) * 0x1000;
  return;
}

