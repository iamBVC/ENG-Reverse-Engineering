/* sub_54F290 @ 0054f290   96 bytes */

void sub_54F290(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = sub_54BC00(param_1);
  iVar2 = iVar2 >> 0xc;
  if (0 < iVar2) {
    do {
      iVar1 = **(int **)(param_1 + 0x120);
      *(int *)(param_1 + 0x120) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x118);
      }
      iVar2 = iVar2 + -1;
    } while (0 < iVar2);
    return;
  }
  for (; iVar2 < 0; iVar2 = iVar2 + 1) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x120) + 4);
    *(int *)(param_1 + 0x120) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x11c);
    }
  }
  return;
}

