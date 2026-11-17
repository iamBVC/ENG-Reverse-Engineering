/* sub_410ED0 @ 00410ed0   297 bytes */

void sub_410ED0(void)

{
  undefined4 local_64 [20];
  undefined4 local_14;
  
  local_64[0] = 100;
  local_14 = 0;
  if (DAT_00582cec != (int *)0x0) {
    (**(code **)(*DAT_00582cec + 0x10))(DAT_00582cec,0,&DAT_00582cf0);
    (**(code **)(*DAT_00582cec + 8))(DAT_00582cec);
    DAT_00582cec = (int *)0x0;
  }
  if (DAT_005832f0 != 0) {
    sub_5628BC(DAT_005832f0);
    DAT_005832f0 = 0;
  }
  if (DAT_00582ce8 != (int *)0x0) {
    (**(code **)(*DAT_00582ce8 + 8))(DAT_00582ce8);
    DAT_00582ce8 = (int *)0x0;
  }
  if (DAT_00582ce4 != (int *)0x0) {
    (**(code **)(*DAT_00582ce4 + 0x14))(DAT_00582ce4,0,0,0,0x400,local_64);
    (**(code **)(*DAT_00582ce4 + 8))(DAT_00582ce4);
    DAT_00582ce4 = (int *)0x0;
  }
  if (DAT_00582ce0 != (int *)0x0) {
    (**(code **)(*DAT_00582ce0 + 0x14))(DAT_00582ce0,0,0,0,0x400,local_64);
    (**(code **)(*DAT_00582ce0 + 8))(DAT_00582ce0);
    DAT_00582ce0 = (int *)0x0;
  }
  if (DAT_00582cdc != (int *)0x0) {
    (**(code **)(*DAT_00582cdc + 0x14))(DAT_00582cdc,0,0,0,0x400,local_64);
    (**(code **)(*DAT_00582cdc + 8))(DAT_00582cdc);
    DAT_00582cdc = (int *)0x0;
  }
  if (DAT_005832f4 != (int *)0x0) {
    (**(code **)(*DAT_005832f4 + 8))(DAT_005832f4);
    DAT_005832f4 = (int *)0x0;
  }
  if (DAT_00582ccc != (int *)0x0) {
    (**(code **)(*DAT_00582ccc + 0x4c))(DAT_00582ccc);
    (**(code **)(*DAT_00582ccc + 0x50))(DAT_00582ccc,DAT_00580168,8);
  }
  return;
}

