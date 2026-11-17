/* sub_21104950 @ 21104950   187 bytes */

void __thiscall sub_21104950(void *this,int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar1 = *(int **)((int)this + 8);
  iVar2 = *piVar1;
  while (iVar2 != 0) {
    if (piVar1[0x46] == param_1) {
      piVar1[0x16] = 0;
      piVar1[3] = 0;
      piVar1[0x46] = 0;
      piVar1[6] = 0;
      sub_2110A200(piVar1,4,0,0);
    }
    piVar1 = (int *)*piVar1;
    iVar2 = *piVar1;
  }
  piVar1 = *(int **)((int)this + 0x14);
  iVar2 = *piVar1;
  while (iVar2 != 0) {
    if (piVar1[0x46] == param_1) {
      piVar1[0x16] = 0;
      piVar1[3] = 0;
      piVar1[0x46] = 0;
      piVar1[6] = 0;
      sub_2110A200(piVar1,4,0,0);
      if (*piVar1 != 0) {
        *(int *)(*piVar1 + 4) = piVar1[1];
        *(int *)piVar1[1] = *piVar1;
        *piVar1 = 0;
        piVar1[1] = 0;
      }
      piVar3 = *(int **)((int)this + 0x10);
      if (*piVar3 != 0) {
        if (*piVar1 != 0) {
          *(int *)(*piVar1 + 4) = piVar1[1];
          *(int *)piVar1[1] = *piVar1;
          *piVar1 = 0;
          piVar1[1] = 0;
        }
        iVar2 = *piVar3;
        piVar1[1] = (int)piVar3;
        *piVar1 = iVar2;
        *(int **)(iVar2 + 4) = piVar1;
        *(int **)piVar1[1] = piVar1;
      }
    }
    piVar1 = (int *)*piVar1;
    iVar2 = *piVar1;
  }
  return;
}

