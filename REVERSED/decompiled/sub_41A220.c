/* sub_41A220 @ 0041a220   256 bytes */

void sub_41A220(void)

{
  DAT_005fcf44 = 0;
  DAT_005fcf20 = 0;
  if (0 < DAT_0058258c) {
    DAT_005fcf44 = 0x10;
    DAT_005fcf20 = 0x10;
  }
  if (0 < DAT_005825ac) {
    DAT_005fcf44 = DAT_005fcf44 | 0x40;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_00582598) {
    DAT_005fcf44 = DAT_005fcf44 | 0x80;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_005825a0) {
    DAT_005fcf44 = DAT_005fcf44 | 0x20;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_005822dc) {
    DAT_005fcf44 = DAT_005fcf44 | 0x4000;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_00582350) {
    DAT_005fcf44 = DAT_005fcf44 | 0x8000;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_00582324) {
    DAT_005fcf44 = DAT_005fcf44 | 0x2000;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_005822a8) {
    DAT_005fcf44 = DAT_005fcf44 | 8;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_00582318) {
    DAT_005fcf44 = DAT_005fcf44 | 1;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_005822e4) {
    DAT_005fcf44 = DAT_005fcf44 | 0x400;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_005822e8) {
    DAT_005fcf44 = DAT_005fcf44 | 0x800;
    DAT_005fcf20 = DAT_005fcf44;
  }
  if (0 < DAT_00582270) {
    DAT_005fcf44 = DAT_005fcf44 | 0x1000;
    DAT_005fcf20 = DAT_005fcf44;
  }
  DAT_005fcf30 = ~DAT_005fcf38 & DAT_005fcf44;
  DAT_005fcf34 = ~DAT_005fcf44 & DAT_005fcf38;
  return;
}

