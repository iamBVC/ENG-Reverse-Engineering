/* sub_567EA2 @ 00567ea2   79 bytes */

void sub_567EA2(void)

{
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0056e8d0;
  puStack_10 = &LAB_00563e08;
  pvStack_14 = ExceptionList;
  ExceptionList = &pvStack_14;
  if (PTR_sub_567E4C_0057ccc4 != (undefined *)0x0) {
    local_8 = 1;
    ExceptionList = &pvStack_14;
    (*(code *)PTR_sub_567E4C_0057ccc4)();
  }
  local_8 = 0xffffffff;
  sub_567E4C();
  return;
}

