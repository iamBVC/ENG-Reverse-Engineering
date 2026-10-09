/* sub_5497F0 @ 005497f0   52 bytes */

void sub_5497F0(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = param_1 + param_3 * 0xc;
  *(int *)(iVar1 + 0x4c) = param_2;
  *(undefined1 *)(iVar1 + 0x52) = *(undefined1 *)(param_2 + 4);
  *(undefined1 *)(param_1 + (param_3 * 3 + 0x15) * 4) = *(undefined1 *)(param_2 + 1);
  *(char *)(iVar1 + 0x53) = -1 - *(char *)(param_2 + 2);
  return;
}

