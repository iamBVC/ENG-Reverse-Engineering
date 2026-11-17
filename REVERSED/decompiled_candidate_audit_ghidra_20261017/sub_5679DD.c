/* Selected Ghidra export at 005679dd. */

undefined4 sub_5679DD(undefined4 *param_1)

{
  undefined4 uVar1;
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 uStack_8;
  
  if (*(int *)*param_1 != -0x1f928c9d) {
    return 0;
  }
  puStack_c = &DAT_0056e8b8;
  puStack_10 = &LAB_00563e08;
  pvStack_14 = ExceptionList;
  ExceptionList = &pvStack_14;
  if (DAT_006da42c != (code *)0x0) {
    uStack_8 = 1;
    ExceptionList = &pvStack_14;
    (*DAT_006da42c)();
  }
  uStack_8 = 0xffffffff;
  uVar1 = sub_56AB58();
  return uVar1;
}

