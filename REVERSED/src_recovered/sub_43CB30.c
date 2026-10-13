/* Selected Ghidra export at 0043cb30. */

void sub_43CB30(void)

{
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [4];
  undefined4 uStack_1c;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  sub_545270();
  uStack_1c = 0x18;
  uStack_14 = 5;
  uStack_10 = 3;
  uStack_c = 0;
  uStack_8 = 0;
  uStack_4 = 0x1e;
  DAT_006d9494 = operator_new(0x104);
  sub_546EA0(DAT_006d9494,auStack_20);
  if (DAT_006d9490 != 0) {
    uStack_30 = 0x40;
    uStack_2c = 0x100;
    uStack_24 = 0x4000;
    uStack_28 = 0x1e;
    DAT_006d9498 = operator_new(0x6c);
    sub_548650(DAT_006d9498,&uStack_30);
    uStack_2c = 0x30;
    uStack_30 = 0x10;
    uStack_28 = 0x1e;
    uStack_24 = CONCAT22(uStack_24._2_2_,0x10);
    DAT_006d949c = operator_new(0xa8);
    sub_548CF0(DAT_006d949c,&uStack_30);
    sub_545F90(CONCAT22(extraout_var_00,DAT_005834e0),0x80);
    sub_546000(CONCAT22(extraout_var,DAT_005834ec),0x80);
    sub_545140();
  }
  return;
}

