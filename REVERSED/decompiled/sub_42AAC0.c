/* sub_42AAC0 @ 0042aac0   74 bytes */

undefined4 sub_42AAC0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = param_2;
  param_2 = (undefined4 *)sub_41EF00(param_2);
  if (param_2 == (undefined4 *)0x0) {
    return 0;
  }
  sub_415A90(param_1,param_2,uVar1);
  uVar1 = *param_2;
  param_2 = param_2 + 1;
  sub_5563F0(&param_2,uVar1,&DAT_005846ec);
  return 1;
}

