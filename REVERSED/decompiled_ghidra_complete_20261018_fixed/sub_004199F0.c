/* sub_4199F0 @ 004199f0   102 bytes */

void sub_4199F0(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  if (param_1 != 0) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x70) + param_2 * 4);
    iVar2 = 0;
    do {
      piVar3 = (int *)(*(int *)(param_1 + 0x70) + iVar2);
      if (*piVar3 == param_3) {
        *piVar3 = iVar1;
      }
      iVar2 = iVar2 + 4;
    } while (iVar2 < 0x38);
    *(int *)(*(int *)(param_1 + 0x70) + param_2 * 4) = param_3;
    return;
  }
  piVar3 = &DAT_00584758;
  iVar1 = (&DAT_00584758)[param_2];
  do {
    if (*piVar3 == param_3) {
      *piVar3 = iVar1;
    }
    piVar3 = piVar3 + 1;
  } while ((int)piVar3 < 0x584790);
  (&DAT_00584758)[param_2] = param_3;
  return;
}

