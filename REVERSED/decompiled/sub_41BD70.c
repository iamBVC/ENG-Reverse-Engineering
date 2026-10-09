/* sub_41BD70 @ 0041bd70   64 bytes */

void __thiscall sub_41BD70(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 != 0) {
    if (*(int *)(param_1 + 0x20) == 0) {
      uVar1 = sub_41BF80();
      *(undefined4 *)(param_1 + 0x20) = uVar1;
      *(undefined4 *)(param_1 + 0x24) = 1;
      return;
    }
    uVar1 = sub_41BFA0(*(int *)(param_1 + 0x20),param_2);
    *(undefined4 *)(param_1 + 0x20) = uVar1;
    *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 1;
  }
  return;
}

