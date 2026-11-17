/* sub_439490 @ 00439490   358 bytes */

void sub_439490(void)

{
  int iVar1;
  int iVar2;
  
  if (DAT_005833e0 == '\0') {
    iVar1 = (**(code **)(*DAT_00582cdc + 0x2c))(DAT_00582cdc,DAT_00582ce4,1);
    if (iVar1 == -0x7789fe3e) {
      (**(code **)(*DAT_00582ccc + 100))(DAT_00582ccc);
      sub_439160();
      (**(code **)(*DAT_00582cdc + 0x2c))(DAT_00582cdc,DAT_00582ce4,1);
    }
  }
  else {
    (**(code **)(*DAT_00582ce4 + 0x94))(DAT_00582ce4,0);
    iVar1 = (**(code **)(*DAT_00582ce0 + 0x14))(DAT_00582ce0,0,DAT_00582ce4,0,0x1000000,0);
    iVar2 = (**(code **)(*DAT_00582ce0 + 0x34))(DAT_00582ce0,2);
    while (iVar2 == -0x7789fde4) {
      iVar2 = (**(code **)(*DAT_00582ce0 + 0x34))(DAT_00582ce0,2);
    }
    (**(code **)(*DAT_00582ce4 + 0x98))(DAT_00582ce4,0);
    if (iVar1 == 0) {
      iVar1 = (**(code **)(*DAT_00582cdc + 0x2c))(DAT_00582cdc,DAT_00582ce0,1);
    }
    if (iVar1 == -0x7789fe3e) {
      (**(code **)(*DAT_00582ccc + 100))(DAT_00582ccc);
      sub_439160();
      (**(code **)(*DAT_00582ce4 + 0x94))(DAT_00582ce4,0);
      (**(code **)(*DAT_00582ce0 + 0x14))(DAT_00582ce0,0,DAT_00582ce4,0,0x1000000,0);
      iVar1 = (**(code **)(*DAT_00582ce0 + 0x34))(DAT_00582ce0,2);
      while (iVar1 == -0x7789fde4) {
        iVar1 = (**(code **)(*DAT_00582ce0 + 0x34))(DAT_00582ce0,2);
      }
      (**(code **)(*DAT_00582ce4 + 0x98))(DAT_00582ce4,0);
      (**(code **)(*DAT_00582cdc + 0x2c))(DAT_00582cdc,DAT_00582ce4,1);
      return;
    }
  }
  return;
}

