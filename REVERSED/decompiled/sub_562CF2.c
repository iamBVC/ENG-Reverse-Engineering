/* sub_562CF2 @ 00562cf2   81 bytes */

undefined4 sub_562CF2(undefined1 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  local_1c = param_1;
  local_24 = param_1;
  local_18 = 0x42;
  local_20 = 0x7fffffff;
  uVar1 = sub_564731(&local_24,param_2,param_3);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    sub_56461C(0,&local_24);
  }
  else {
    *local_24 = 0;
  }
  return uVar1;
}

