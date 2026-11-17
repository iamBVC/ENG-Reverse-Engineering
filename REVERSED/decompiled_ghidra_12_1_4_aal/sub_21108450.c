/* sub_21108450 @ 21108450   104 bytes */

void __thiscall sub_21108450(void *this,int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  piVar1 = *(int **)((int)this + 0x14);
  if (piVar1 != (int *)0x0) {
    piVar3 = (int *)piVar1[4];
    iVar2 = piVar1[1];
    iVar4 = 0;
    if (0 < *piVar1) {
      do {
        if (param_1 == piVar3[1]) {
          _AAL_Lock_0();
          piVar1 = (int *)piVar3[1];
          if (piVar1 != (int *)0x0) {
            (**(code **)(*piVar1 + 8))(piVar1);
            piVar3[1] = 0;
          }
          _AAL_Unlock_0();
          if (*piVar3 == 0) {
            sub_21107C70((int)this);
            return;
          }
        }
        iVar4 = iVar4 + 1;
        piVar3 = (int *)((int)piVar3 + iVar2);
        if (**(int **)((int)this + 0x14) <= iVar4) {
          return;
        }
      } while( true );
    }
  }
  return;
}

