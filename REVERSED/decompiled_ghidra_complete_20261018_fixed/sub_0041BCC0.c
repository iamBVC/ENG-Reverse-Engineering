/* sub_41BCC0 @ 0041bcc0   38 bytes */

void __thiscall sub_41BCC0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x20) != 0) {
    uVar1 = sub_41BFC0(*(int *)(param_1 + 0x20),param_2);
    *(undefined4 *)(param_1 + 0x20) = uVar1;
    *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + -1;
  }
  return;
}

