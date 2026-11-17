/* sub_567A6E @ 00567a6e   156 bytes */

undefined4
sub_567A6E(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0056e880;
  puStack_10 = &LAB_00563e08;
  local_14 = ExceptionList;
  DAT_006da420 = param_1;
  DAT_006da424 = param_3;
  local_8 = 1;
  ExceptionList = &local_14;
  uVar1 = sub_562FDF(param_2,param_4,param_5,param_6,param_7);
  local_8 = 0xffffffff;
  sub_567B34();
  ExceptionList = local_14;
  return uVar1;
}

