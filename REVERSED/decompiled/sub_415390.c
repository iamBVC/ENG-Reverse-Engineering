/* sub_415390 @ 00415390   492 bytes */

void sub_415390(undefined4 param_1)

{
  switch(param_1) {
  case 0:
    DAT_00583730 = 0;
    DAT_0058372c = &LAB_00415010;
    DAT_0058370c = 0xff;
    return;
  case 1:
    DAT_0058372c = &LAB_00415070;
    DAT_0058370c = 1;
    DAT_00583710 = 0x10;
    sub_545DE0(0,0xffffff00);
    DAT_00583730 = 0;
    return;
  case 2:
    DAT_0058372c = &LAB_004152e0;
    DAT_0058370c = 0x12f;
    DAT_00583710 = 0x10;
    sub_545DE0(0x1000,0x100);
    DAT_00583730 = 0;
    return;
  case 3:
    DAT_0058372c = &LAB_00415070;
    DAT_0058370c = 0;
    DAT_00583710 = 0x20;
    sub_545DE0(0,0xfffffe00);
    DAT_00583730 = 0;
    return;
  case 4:
    DAT_0058372c = &LAB_004152e0;
    DAT_0058370c = 0x12f;
    DAT_00583710 = 0x20;
    sub_545DE0(0x1000,0x200);
    DAT_00583730 = 0;
    return;
  default:
    DAT_00583730 = 0;
    return;
  case 7:
    DAT_0058372c = &LAB_00415070;
    DAT_0058370c = 0;
    DAT_00583710 = 3;
    sub_545DE0(0,0xffffff80);
    DAT_00583730 = 0;
    return;
  case 8:
    DAT_0058372c = &LAB_004150e0;
    DAT_0058370c = 0;
    DAT_00583710 = 3;
    sub_545DE0(0,0x80);
    DAT_00583730 = 0;
    return;
  case 9:
    DAT_0058372c = &LAB_004151e0;
    break;
  case 10:
    DAT_0058372c = &LAB_00415280;
    DAT_0058370c = 0x14f;
    DAT_00583710 = 0x20;
    sub_545DE0(0x1000,0x200);
    DAT_00583730 = 0;
    return;
  case 0xb:
    DAT_0058372c = &LAB_00415230;
    break;
  case 0xc:
    DAT_0058372c = &LAB_00415160;
    DAT_0058370c = 0;
    DAT_00583710 = 3;
    DAT_00583730 = 0;
    return;
  }
  DAT_0058370c = 0;
  DAT_00583730 = 0;
  DAT_00583710 = 0x20;
  return;
}

