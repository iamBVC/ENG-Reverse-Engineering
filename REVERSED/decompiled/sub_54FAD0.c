/* sub_54FAD0 @ 0054fad0   112 bytes */

void sub_54FAD0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = sub_54BC00(param_1);
  if (*(int *)(param_1 + 0x14) != 0) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x14) + 8) + -1;
    iVar3 = iVar1 >> 0xc;
    if (iVar2 < iVar1 >> 0xc) {
      iVar3 = iVar2;
    }
    iVar1 = *(int *)(param_1 + 0x110);
    while (iVar1 != iVar3) {
      iVar2 = *(int *)(param_1 + 0x14);
      *(int *)(param_1 + 0x110) = iVar1 + 1;
      if (iVar1 + 1 == *(int *)(iVar2 + 8)) {
        *(undefined4 *)(param_1 + 0x110) = 0;
      }
      if (*(int *)(iVar2 + 0x10) != 0) {
        sub_41FA30(*(undefined4 *)(param_1 + 0x10),iVar2,*(undefined4 *)(param_1 + 0x110));
      }
      iVar1 = *(int *)(param_1 + 0x110);
    }
  }
  return;
}

