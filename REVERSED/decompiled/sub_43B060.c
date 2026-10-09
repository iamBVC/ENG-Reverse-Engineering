/* sub_43B060 @ 0043b060   26 bytes */

int sub_43B060(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0x80000000;
  iVar1 = 0x1f;
  do {
    if ((param_1 & uVar2) != 0) {
      return iVar1;
    }
    uVar2 = uVar2 >> 1;
    iVar1 = iVar1 + -1;
  } while (-1 < iVar1);
  return 0;
}

