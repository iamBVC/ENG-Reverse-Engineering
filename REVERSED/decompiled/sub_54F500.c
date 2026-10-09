/* sub_54F500 @ 0054f500   71 bytes */

void sub_54F500(int param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  
  piVar2 = *(int **)(param_1 + 0x118);
  uVar3 = 0;
  if (piVar2 != *(int **)(param_1 + 0x11c)) {
    do {
      uVar1 = sub_404C10(piVar2 + 6,param_1 + 0x30);
      if (uVar3 < uVar1) {
        *(int **)(param_1 + 0x120) = piVar2;
        uVar3 = uVar1;
      }
      piVar2 = (int *)*piVar2;
    } while (piVar2 != (int *)*(int *)(param_1 + 0x11c));
  }
  return;
}

