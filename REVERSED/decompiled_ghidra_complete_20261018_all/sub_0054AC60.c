/* sub_54AC60 @ 0054ac60   97 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_54AC60(void)

{
  if (DAT_005833e1 == '\0') {
    (**(code **)(*DAT_00582cd4 + 0x24))(DAT_00582cd4);
  }
  else {
    _DAT_005832f8 = 0x7c;
    (**(code **)(*DAT_00582ce4 + 100))(DAT_00582ce4,0,&DAT_005832f8,1,0);
  }
  sub_424BE0();
  if (DAT_005833e1 != '\0') {
    (**(code **)(*DAT_00582ce4 + 0x80))(DAT_00582ce4,0);
    return;
  }
  (**(code **)(*DAT_00582cd4 + 0x28))(DAT_00582cd4);
  return;
}

