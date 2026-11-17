/* sub_547E80 @ 00547e80   49 bytes */

void sub_547E80(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 8);
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar2;
    sub_546E30(puVar2);
    sub_546E10(puVar2,param_1);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
    puVar2 = puVar1;
  }
  return;
}

