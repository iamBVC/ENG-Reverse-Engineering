/* sub_554D50 @ 00554d50   69 bytes */

void sub_554D50(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = sub_54BC00(param_1);
  iVar1 = *(int *)(param_1 + 0x14);
  uVar3 = iVar2 >> 0xc;
  if (iVar1 != 0) {
    if ((int)uVar3 < 0) {
      uVar3 = *(uint *)(iVar1 + 8);
    }
    if (*(uint *)(iVar1 + 8) <= uVar3) {
      uVar3 = 0;
    }
    *(uint *)(param_1 + 0x110) = uVar3;
    *(undefined2 *)(param_1 + 0x114) = 0;
    *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 8;
  }
  return;
}

