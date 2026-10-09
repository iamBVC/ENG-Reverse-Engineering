/* sub_437E90 @ 00437e90   79 bytes */

void sub_437E90(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (DAT_006d7acc != 0) {
    iVar2 = 0;
    do {
      piVar1 = *(int **)(iVar2 + 0x10 + DAT_006d7ad0);
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
        *(undefined4 *)(iVar2 + 0x10 + DAT_006d7ad0) = 0;
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 0x14;
    } while (uVar3 < DAT_006d7acc);
    DAT_006d7acc = 0;
    return;
  }
  DAT_006d7acc = 0;
  return;
}

