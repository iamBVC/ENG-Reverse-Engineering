/* sub_406C50 @ 00406c50   210 bytes */

void sub_406C50(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_0058114c == 0) {
    DAT_00581150 = 0;
    return;
  }
  iVar4 = 0;
  iVar3 = DAT_0058114c;
  if (0 < DAT_00581150) {
    iVar5 = 0;
    do {
      piVar1 = *(int **)(iVar5 + 0xc + iVar3);
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
        iVar3 = DAT_0058114c;
      }
      piVar1 = *(int **)(iVar5 + 0x10 + iVar3);
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
        iVar3 = DAT_0058114c;
      }
      if (((*(uint *)(iVar5 + iVar3) & 0xffffff7f) != 0) &&
         (piVar1 = *(int **)(iVar5 + 0x14 + iVar3), piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1);
        iVar3 = DAT_0058114c;
      }
      iVar2 = *(int *)(iVar5 + 0x1c + iVar3);
      if (iVar2 != 0) {
        sub_562941(iVar2);
        iVar3 = DAT_0058114c;
      }
      if (((*(byte *)(iVar5 + iVar3) & 0x80) != 0) &&
         (iVar2 = *(int *)(iVar5 + 0x18 + iVar3), iVar2 != 0)) {
        sub_562941(iVar2);
        iVar3 = DAT_0058114c;
      }
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 0x20;
    } while (iVar4 < DAT_00581150);
  }
  sub_562941(iVar3);
  DAT_0058114c = 0;
  DAT_00581150 = 0;
  return;
}

