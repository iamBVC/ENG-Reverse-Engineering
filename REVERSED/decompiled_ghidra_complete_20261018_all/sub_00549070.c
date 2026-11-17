/* sub_549070 @ 00549070   72 bytes */

void sub_549070(int param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = (int *)0x0;
  piVar1 = *(int **)(param_1 + 0x74);
  if (*(int **)(param_1 + 0x74) != (int *)0x0) {
    while (piVar2 = piVar1, piVar2 + 0x20 != param_2) {
      piVar1 = (int *)*piVar2;
      piVar3 = piVar2;
      if ((int *)*piVar2 == (int *)0x0) {
        return;
      }
    }
    if (piVar3 == (int *)0x0) {
      *(int *)(param_1 + 0x74) = *piVar2;
    }
    else {
      *piVar3 = *piVar2;
    }
    if (piVar2 == *(int **)(param_1 + 0x78)) {
      *(int **)(param_1 + 0x78) = piVar3;
    }
    *piVar2 = *(int *)(param_1 + 0x7c);
    *(int **)(param_1 + 0x7c) = piVar2;
  }
  return;
}

