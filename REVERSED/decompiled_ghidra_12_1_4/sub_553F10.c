/* sub_553F10 @ 00553f10   88 bytes */

int * sub_553F10(int param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = 0;
  piVar2 = *(int **)(DAT_00584648 + 0x50);
  uVar1 = *(uint *)(DAT_00584648 + 0x20);
  if (uVar1 != 0) {
    do {
      if (((*(int *)(param_1 + 0x30) >> 0xc == *piVar2) &&
          (*(int *)(param_1 + 0x34) >> 0xc == piVar2[1])) &&
         (*(int *)(param_1 + 0x38) >> 0xc == piVar2[2])) break;
      piVar2 = piVar2 + 6;
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar1);
  }
  if (uVar3 == uVar1) {
    return (int *)0x0;
  }
  DAT_006da2bc = uVar3;
  return piVar2;
}

