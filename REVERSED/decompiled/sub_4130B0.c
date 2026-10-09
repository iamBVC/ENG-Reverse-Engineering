/* sub_4130B0 @ 004130b0   179 bytes */

undefined4 * __thiscall
sub_4130B0(undefined4 *param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0056d7c3;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[9] = param_1 + 7;
  param_1[7] = param_1 + 8;
  param_1[8] = 0;
  local_4 = 1;
  uVar1 = sub_56D4ED(param_2);
  param_1[2] = uVar1;
  if (param_3 == (undefined4 *)0x0) {
    param_1[3] = 0;
  }
  else {
    puVar2 = operator_new(0x10);
    param_1[3] = puVar2;
    *puVar2 = *param_3;
    puVar2[1] = param_3[1];
    puVar2[2] = param_3[2];
    puVar2[3] = param_3[3];
  }
  param_1[4] = param_4;
  param_1[5] = 0;
  param_1[6] = 0;
  ExceptionList = local_c;
  return param_1;
}

