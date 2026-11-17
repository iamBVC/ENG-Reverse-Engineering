/* sub_54F430 @ 0054f430   60 bytes */

void sub_54F430(int param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  
  piVar2 = *(int **)(param_1 + 0x118);
  uVar3 = 0xffffffff;
  if (piVar2 != (int *)0x0) {
    do {
      uVar1 = sub_404C90(piVar2 + 6,param_1 + 0x30);
      if (uVar1 < uVar3) {
        *(int **)(param_1 + 0x120) = piVar2;
        uVar3 = uVar1;
      }
      piVar2 = (int *)*piVar2;
    } while (piVar2 != (int *)0x0);
  }
  return;
}

