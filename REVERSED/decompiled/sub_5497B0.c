/* sub_5497B0 @ 005497b0   51 bytes */

undefined4 sub_5497B0(int param_1,int param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = (0x80 - *(short *)(*(int *)(param_2 + 8) + 0x16)) * 0x10 +
          *(int *)(*(int *)(param_1 + 0x38) + 4);
  if (param_3 != (int *)0x0) {
    *param_3 = (int)*(char *)(iVar1 + 5);
  }
  return *(undefined4 *)(iVar1 + 0xc);
}

