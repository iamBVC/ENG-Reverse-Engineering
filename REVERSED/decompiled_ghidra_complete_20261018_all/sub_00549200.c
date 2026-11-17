/* sub_549200 @ 00549200   109 bytes */

void sub_549200(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined1 local_10 [8];
  uint local_8;
  
  uVar1 = *(undefined4 *)(param_2 + 0xc);
  sub_548B60(uVar1,local_10);
  if ((local_8 & 0xff) == 0xf) {
    sub_549270(param_1,uVar1,local_10);
  }
  else if ((local_8 & 0xff) == 0x10) {
    sub_549980(param_1,uVar1,local_10);
    sub_549150(param_1,uVar1);
    return;
  }
  sub_549150(param_1,uVar1);
  return;
}

