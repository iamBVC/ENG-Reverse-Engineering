/* sub_5679F3 @ 005679f3   123 bytes */

void sub_5679F3(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,int param_6,int param_7,undefined4 *param_8,undefined4 param_9,
               int param_10)

{
  int iVar1;
  
  if (param_7 != 0) {
    sub_567BA4(param_1,param_2,param_6,param_7);
  }
  if (param_10 == 0) {
    param_10 = param_2;
  }
  sub_562F5A(param_10,param_1);
  sub_56793F(param_2,param_4,param_5,*param_8);
  *(int *)(param_2 + 8) = param_8[1] + 1;
  iVar1 = sub_567A6E(param_1,param_2,param_3,param_5,*(undefined4 *)(param_6 + 0xc),param_9,0x100);
  if (iVar1 != 0) {
    sub_562F18(iVar1,param_2);
  }
  return;
}

