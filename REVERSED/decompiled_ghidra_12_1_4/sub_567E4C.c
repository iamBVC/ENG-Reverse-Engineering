/* sub_567E4C @ 00567e4c   79 bytes */

void sub_567E4C(void)

{
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0056e8b8;
  puStack_10 = &LAB_00563e08;
  pvStack_14 = ExceptionList;
  ExceptionList = &pvStack_14;
  if (DAT_006da42c != (code *)0x0) {
    local_8 = 1;
    ExceptionList = &pvStack_14;
    (*DAT_006da42c)();
  }
  local_8 = 0xffffffff;
  sub_56AB58();
  return;
}

