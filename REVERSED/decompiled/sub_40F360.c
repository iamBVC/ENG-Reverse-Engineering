/* sub_40F360 @ 0040f360   77 bytes */

bool sub_40F360(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_10 = param_2;
  local_8 = param_4;
  local_4 = param_5;
  local_c = param_3;
  local_18 = 0x18;
  local_14 = 0x10;
  iVar1 = (**(code **)(*param_1 + 0x18))(param_1,4,&local_18);
  return iVar1 == 0;
}

