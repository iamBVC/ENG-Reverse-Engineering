/* Selected Ghidra export at 00563e08. */

undefined4 sub_563E08(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int extraout_ECX;
  undefined1 *puVar2;
  int iVar3;
  int iStack_c;
  undefined4 uStack_8;
  
  puVar2 = &stack0xfffffffc;
  if ((*(uint *)(param_1 + 4) & 6) == 0) {
    iStack_c = param_1;
    uStack_8 = param_3;
    *(int **)(param_2 + -4) = &iStack_c;
    iVar1 = *(int *)(param_2 + 8);
    for (iVar3 = *(int *)(param_2 + 0xc); iVar3 != -1; iVar3 = *(int *)(iVar1 + iVar3 * 0xc)) {
      if (*(int *)(iVar1 + 4 + iVar3 * 0xc) != 0) {
        iVar1 = (**(code **)(iVar1 + 4 + iVar3 * 0xc))();
        param_2 = *(int *)(puVar2 + 0xc);
        if (iVar1 != 0) {
          if (iVar1 < 0) {
            return 0;
          }
          iVar1 = *(int *)(param_2 + 8);
          __global_unwind2(param_2);
          puVar2 = (undefined1 *)(param_2 + 0x10);
          __local_unwind2(param_2,iVar3);
          sub_5632D2(1);
          *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(iVar1 + extraout_ECX * 4);
          (**(code **)(iVar1 + 8 + extraout_ECX * 4))();
        }
      }
      iVar1 = *(int *)(param_2 + 8);
    }
  }
  else {
    __local_unwind2(param_2,0xffffffff,&stack0xfffffffc,&stack0xfffffffc);
  }
  return 1;
}

