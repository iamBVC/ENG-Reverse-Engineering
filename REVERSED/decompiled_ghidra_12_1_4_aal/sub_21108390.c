/* sub_21108390 @ 21108390   85 bytes */

void __thiscall sub_21108390(void *this,int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  piVar1 = *(int **)((int)this + 0x14);
  if (piVar1 != (int *)0x0) {
    iVar3 = piVar1[4];
    iVar2 = piVar1[1];
    iVar4 = 0;
    if (0 < *piVar1) {
      do {
        if (param_1 == *(int *)(iVar3 + 0xc)) {
          _AAL_Lock_0();
          piVar1 = *(int **)(iVar3 + 0xc);
          if (piVar1 != (int *)0x0) {
            (**(code **)(*piVar1 + 8))(piVar1);
            *(undefined4 *)(iVar3 + 0xc) = 0;
          }
          _AAL_Unlock_0();
        }
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + iVar2;
      } while (iVar4 < **(int **)((int)this + 0x14));
    }
  }
  return;
}

