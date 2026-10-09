/* sub_40ECD0 @ 0040ecd0   175 bytes */

void sub_40ECD0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x68) = 0xffffffff;
    *(undefined4 *)(param_1 + 100) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x60) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x5c) = 0xffffffff;
    (**(code **)(**(int **)(param_1 + 8) + 0x10))(*(int **)(param_1 + 8),&LAB_0040ed80,param_1,3);
    if (((((*(uint *)(param_1 + 0x5c) & 0x80000000) != 0) ||
         ((*(uint *)(param_1 + 0x60) & 0x80000000) != 0)) ||
        ((*(uint *)(param_1 + 100) & 0x80000000) != 0)) ||
       ((*(uint *)(param_1 + 0x68) & 0x80000000) != 0)) {
      (**(code **)(**(int **)(param_1 + 8) + 0x10))(*(int **)(param_1 + 8),&LAB_0040ee30,param_1,3);
    }
    if (((*(uint *)(param_1 + 0x5c) & 0x80000000) != 0) ||
       ((*(uint *)(param_1 + 0x60) & 0x80000000) != 0)) {
      (**(code **)(**(int **)(param_1 + 8) + 0x10))(*(int **)(param_1 + 8),&LAB_0040ef50,param_1,3);
    }
    puVar2 = &DAT_00584790;
    puVar3 = *(undefined4 **)(param_1 + 0x70);
    for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    (**(code **)(**(int **)(param_1 + 8) + 0x10))(*(int **)(param_1 + 8),&LAB_0040ef90,param_1,0xc);
    return;
  }
  puVar2 = &DAT_005847c8;
  puVar3 = &DAT_00584758;
  for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return;
}

