/* sub_40E690 @ 0040e690   90 bytes */

int sub_40E690(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar1 = DAT_00582260;
  if (param_1 == 0) {
    iVar2 = 0;
    do {
      if ((((PTR_DAT_005724dc[iVar2 + 0x18] & 0x80) != 0) && ((PTR_DAT_005724dc[0x50] & 0x80) == 0))
         && ((PTR_DAT_005724dc[0xd0] & 0x80) == 0)) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x100);
  }
  else {
    while ((piVar3 = piVar1, (int *)*piVar3 != (int *)0x0 || (piVar3[1] == 0))) {
      iVar2 = 0;
      do {
        if (*(char *)((int)piVar3 + iVar2 + 0x3c) != '\0') {
          return iVar2;
        }
        iVar2 = iVar2 + 1;
        piVar1 = (int *)*piVar3;
      } while (iVar2 < 0x20);
    }
  }
  return -1;
}

