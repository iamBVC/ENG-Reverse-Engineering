/* sub_547990 @ 00547990   21 bytes */

undefined4 sub_547990(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_2 != 0) {
    uVar1 = _AAL_GetPlayStatus_4(*(undefined4 *)(param_2 + 0x14));
  }
  return uVar1;
}

