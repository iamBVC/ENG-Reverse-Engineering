/* sub_406990 @ 00406990   124 bytes */

void sub_406990(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_00581144 == 0) {
    DAT_00581148 = 0;
    return;
  }
  iVar5 = 0;
  iVar3 = DAT_00581144;
  if (0 < DAT_00581148) {
    iVar4 = 0;
    do {
      iVar1 = *(int *)(iVar4 + 8 + iVar3);
      if (iVar1 != 0) {
        sub_562941(iVar1);
        iVar3 = DAT_00581144;
      }
      piVar2 = *(int **)(iVar4 + 0x10 + iVar3);
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 8))(piVar2);
        iVar3 = DAT_00581144;
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x1c;
    } while (iVar5 < DAT_00581148);
  }
  sub_562941(iVar3);
  DAT_00581144 = 0;
  DAT_00581148 = 0;
  return;
}

