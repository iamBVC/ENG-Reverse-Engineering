/* sub_5490C0 @ 005490c0   141 bytes */

void sub_5490C0(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (int)((int)*(char *)(param_2 + 0x52 + (uint)*(byte *)(param_3 + 0x7d) * 0xc) +
               (uint)*(byte *)(*(int *)(param_3 + 8) + 3)) >> 1;
  iVar1 = (int)(((int)((uint)*(byte *)(param_2 + ((uint)*(byte *)(param_3 + 0x7d) * 3 + 0x15) * 4) *
                       (uint)*(byte *)(*(int *)(param_3 + 8) + 2) * (uint)*(byte *)(param_3 + 0x7a))
                >> 0xe) * (int)*(short *)(param_1 + 0x6e) * (uint)*(byte *)(param_2 + 0x4b)) >> 7;
  iVar3 = iVar2 + -0x40;
  if (-1 < iVar3) {
    *(short *)(param_3 + 0x66) = (short)iVar1;
    *(undefined2 *)(param_3 + 100) = (short)((0x3f - iVar3) * iVar1 >> 6);
    return;
  }
  *(short *)(param_3 + 0x66) = (short)(iVar2 * iVar1 >> 6);
  *(undefined2 *)(param_3 + 100) = (short)iVar1;
  return;
}

