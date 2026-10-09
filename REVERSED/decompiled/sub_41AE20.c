/* sub_41AE20 @ 0041ae20   216 bytes */

int * sub_41AE20(uint param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  short sVar5;
  
  piVar4 = DAT_0058499c;
  if (DAT_0058499c == (int *)0x0) {
    return (int *)0x0;
  }
  while ((*(short *)((int)piVar4 + 10) != 0 || (*(ushort *)(piVar4 + 2) < param_1))) {
    piVar4 = (int *)*piVar4;
    if (piVar4 == (int *)0x0) {
      return (int *)0x0;
    }
  }
  *(undefined2 *)((int)piVar4 + 10) = 1;
  uVar1 = param_1 + 3;
  sVar5 = (short)param_1;
  if (*piVar4 == 0) {
    if (*(ushort *)(piVar4 + 2) < uVar1) {
      return (int *)0x0;
    }
    piVar2 = piVar4 + uVar1;
    piVar2[1] = (int)piVar4;
    *piVar2 = 0;
    *piVar4 = (int)piVar2;
    *(short *)(piVar2 + 2) = ((short)piVar4[2] - sVar5) + -3;
    *(short *)(piVar4 + 2) = sVar5;
    *(undefined2 *)((int)piVar2 + 10) = 0;
  }
  else if (uVar1 <= *(ushort *)(piVar4 + 2)) {
    piVar2 = piVar4 + uVar1;
    piVar2[1] = (int)piVar4;
    *piVar2 = *piVar4;
    *(int **)(*piVar4 + 4) = piVar2;
    *piVar4 = (int)piVar2;
    *(short *)(piVar2 + 2) = ((short)piVar4[2] - sVar5) + -3;
    *(short *)(piVar4 + 2) = sVar5;
    iVar3 = *piVar2;
    *(undefined2 *)((int)piVar2 + 10) = 0;
    if ((iVar3 != 0) && (*(short *)(iVar3 + 10) == 0)) {
      *(short *)(piVar2 + 2) = (short)piVar2[2] + *(short *)(iVar3 + 8) + 3;
      iVar3 = *(int *)*piVar2;
      *piVar2 = iVar3;
      if (iVar3 != 0) {
        *(int **)(iVar3 + 4) = piVar2;
        return piVar4 + 3;
      }
    }
  }
  return piVar4 + 3;
}

