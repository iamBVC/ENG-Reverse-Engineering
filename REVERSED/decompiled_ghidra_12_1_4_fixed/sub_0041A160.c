/* sub_41A160 @ 0041a160   179 bytes */

void sub_41A160(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  do {
    if (5 < param_1) {
      return;
    }
    if ((*(uint *)(&DAT_00571fbc + (*(int *)(&DAT_0058483c + param_1 * 4) + param_1 * 9) * 4) &
        DAT_005fcf30) == 0) {
LAB_0041a1fe:
      *(undefined4 *)(&DAT_0058483c + param_1 * 4) = 0;
    }
    else {
      iVar1 = *(int *)(&DAT_0058483c + param_1 * 4) + 1;
      *(int *)(&DAT_0058483c + param_1 * 4) = iVar1;
      if (*(int *)(&DAT_00571fbc + (iVar1 + param_1 * 9) * 4) == 0) {
        uVar2 = 1 << ((byte)param_1 & 0x1f);
        if ((uVar2 & DAT_00584710) == 0) {
          DAT_00584710 = DAT_00584710 | uVar2;
          sub_546170(0,0xffffff81,8);
          if (param_1 == 2) {
            sub_415390(1);
            DAT_00584700 = 10;
            DAT_00584638 = 4;
          }
        }
        else {
          DAT_00584710 = DAT_00584710 & ~uVar2;
        }
        goto LAB_0041a1fe;
      }
    }
    param_1 = param_1 + 1;
  } while( true );
}

