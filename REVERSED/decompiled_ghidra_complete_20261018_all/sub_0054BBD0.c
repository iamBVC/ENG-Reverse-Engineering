/* sub_54BBD0 @ 0054bbd0   45 bytes */

void sub_54BBD0(int param_1,undefined4 param_2)

{
  **(undefined4 **)(param_1 + 0x104) = param_2;
  *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x104) + 4;
  *(int *)(param_1 + 0x108) = *(int *)(param_1 + 0x108) + 1;
  return;
}

