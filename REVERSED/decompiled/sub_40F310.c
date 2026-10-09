/* sub_40F310 @ 0040f310   72 bytes */

bool sub_40F310(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_4 = param_5;
  local_c = param_3;
  local_8 = param_4;
  local_14 = 0x14;
  local_10 = 0x10;
  iVar1 = (**(code **)(*param_1 + 0x18))(param_1,param_2,&local_14);
  return iVar1 == 0;
}

