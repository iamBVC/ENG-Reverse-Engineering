/* sub_547DF0 @ 00547df0   77 bytes */

void sub_547DF0(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = *(int **)(param_1 + 8);
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    piVar1 = (int *)*piVar2;
    if (piVar2[6] == param_2) {
      if (piVar1 != (int *)0x0) {
        piVar1[2] = piVar1[2] + piVar2[2];
      }
      sub_546E30(piVar2);
      sub_546E10(piVar2,param_1);
      *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
    }
  }
  return;
}

