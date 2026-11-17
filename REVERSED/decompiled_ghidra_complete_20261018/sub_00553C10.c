/* sub_553C10 @ 00553c10   113 bytes */

void sub_553C10(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = sub_54BC00(param_1);
  *(int *)(param_1 + 0x10) = iVar1;
  if ((iVar1 == 0) || ((*(short *)(iVar1 + 0x78) == 0 && (*(short *)(iVar1 + 0x7a) == 0)))) {
    uVar2 = *(uint *)(param_1 + 0xec) & 0xffffffdf;
  }
  else {
    uVar2 = *(uint *)(param_1 + 0xec) | 0x20;
  }
  *(uint *)(param_1 + 0xec) = uVar2;
  if (((iVar1 != 0) && (*(short *)(iVar1 + 0x6e) != 0)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x74) + 1) & 1) != 0)) {
    *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 0x80;
    return;
  }
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) & 0xffffff7f;
  return;
}

