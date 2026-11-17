/* sub_558D30 @ 00558d30   57 bytes */

void sub_558D30(int param_1,undefined4 param_2)

{
  sub_415AB0(param_2,(int *)(param_1 + 0x1c));
  if (*(int *)(param_1 + 0x1c) != 0) {
    sub_545350(param_1,param_2,1);
    return;
  }
  *(undefined4 *)(param_1 + 0x18) = 0;
  return;
}

