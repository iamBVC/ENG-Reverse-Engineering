/* sub_545030 @ 00545030   260 bytes */

void sub_545030(void)

{
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined1 local_20 [4];
  undefined4 local_1c;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  sub_545270();
  local_1c = 0x18;
  local_14 = 5;
  local_10 = 3;
  local_c = 0;
  local_8 = 0;
  local_4 = 0x1e;
  DAT_006d9494 = operator_new(0x104);
  sub_546EA0(DAT_006d9494,local_20);
  if (DAT_006d9490 != 0) {
    local_30 = 0x40;
    local_2c = 0x100;
    local_24 = 0x4000;
    local_28 = 0x1e;
    DAT_006d9498 = operator_new(0x6c);
    sub_548650(DAT_006d9498,&local_30);
    local_2c = 0x30;
    local_30 = 0x10;
    local_28 = 0x1e;
    local_24 = CONCAT22(local_24._2_2_,0x10);
    DAT_006d949c = operator_new(0xa8);
    sub_548CF0(DAT_006d949c,&local_30);
    sub_545F90(CONCAT22(extraout_var_00,DAT_005834e0),0x80);
    sub_546000(CONCAT22(extraout_var,DAT_005834ec),0x80);
    sub_545140();
  }
  return;
}

