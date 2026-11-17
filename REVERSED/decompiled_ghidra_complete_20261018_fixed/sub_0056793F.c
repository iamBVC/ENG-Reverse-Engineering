/* sub_56793F @ 0056793f   132 bytes */

void sub_56793F(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0056e870;
  puStack_10 = &LAB_00563e08;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  for (iVar2 = *(int *)(param_1 + 8); local_8 = 0xffffffff, iVar2 != param_4;
      iVar2 = *(int *)(*(int *)(param_3 + 8) + iVar2 * 8)) {
    if ((iVar2 < 0) || (*(int *)(param_3 + 4) <= iVar2)) {
      sub_567EA2();
    }
    local_8 = 0;
    iVar1 = *(int *)(*(int *)(param_3 + 8) + 4 + iVar2 * 8);
    if (iVar1 != 0) {
      __CallSettingFrame_12(iVar1,param_1,0x103);
    }
  }
  *(int *)(param_1 + 8) = iVar2;
  ExceptionList = local_14;
  return;
}

