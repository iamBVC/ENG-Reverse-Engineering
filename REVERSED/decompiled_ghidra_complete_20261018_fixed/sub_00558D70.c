/* sub_558D70 @ 00558d70   57 bytes */

void sub_558D70(int param_1,undefined4 param_2)

{
  sub_415AB0(param_2,(int *)(param_1 + 0x24));
  if (*(int *)(param_1 + 0x24) != 0) {
    sub_545350(param_1,param_2,4);
    return;
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  return;
}

