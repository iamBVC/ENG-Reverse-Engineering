/* sub_41ADA0 @ 0041ada0   122 bytes */

void sub_41ADA0(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar1 = (int *)(param_1 + -0xc);
  if (*(short *)(param_1 + -2) == 0) {
    sub_563CA7(&DAT_005722e4,piVar1);
  }
  piVar2 = (int *)*piVar1;
  *(undefined2 *)(param_1 + -2) = 0;
  if ((piVar2 != (int *)0x0) && (*(short *)((int)piVar2 + 10) == 0)) {
    *(short *)(param_1 + -4) = *(short *)(param_1 + -4) + (short)piVar2[2] + 3;
    if (*piVar2 != 0) {
      *(int **)(*piVar2 + 4) = piVar1;
    }
    *piVar1 = *(int *)*piVar1;
  }
  iVar3 = *(int *)(param_1 + -8);
  if ((iVar3 != 0) && (*(short *)(iVar3 + 10) == 0)) {
    *(short *)(iVar3 + 8) = *(short *)(iVar3 + 8) + *(short *)(param_1 + -4) + 3;
    **(int **)(param_1 + -8) = *piVar1;
    if (*piVar1 != 0) {
      *(undefined4 *)(*piVar1 + 4) = *(undefined4 *)(param_1 + -8);
    }
  }
  return;
}

