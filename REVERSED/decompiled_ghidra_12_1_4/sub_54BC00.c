/* sub_54BC00 @ 0054bc00   37 bytes */

undefined4 sub_54BC00(int param_1)

{
  undefined4 *puVar1;
  
  *(int *)(param_1 + 0x108) = *(int *)(param_1 + 0x108) + -1;
  puVar1 = (undefined4 *)(*(int *)(param_1 + 0x104) + -4);
  *(undefined4 **)(param_1 + 0x104) = puVar1;
  return *puVar1;
}

