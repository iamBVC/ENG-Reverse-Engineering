/* sub_54FE40 @ 0054fe40   85 bytes */

void sub_54FE40(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = sub_54BC00(param_1);
  if (iVar1 == 1) {
    *(uint *)(param_1 + 0xec) = *(uint *)(param_1 + 0xec) | 0x80000;
  }
  else {
    uVar2 = *(uint *)(param_1 + 0xec) & 0xfff7ffff;
    *(uint *)(param_1 + 0xec) = uVar2;
    if (iVar1 == 2) {
      *(uint *)(param_1 + 0xec) = uVar2 | 0x100000;
      return;
    }
  }
  *(uint *)(param_1 + 0xec) = *(uint *)(param_1 + 0xec) & 0xffefffff;
  return;
}

