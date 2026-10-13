/* Selected Ghidra export at 00417d50. */

undefined4 sub_417D50(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)*DAT_0058342c;
  if (((((piVar1 == (int *)0x0) || (piVar2 = (int *)DAT_0058342c[1], piVar2 == (int *)0x0)) ||
       (*piVar2 == 0)) || ((piVar2[1] != 0 || (*piVar1 != 0)))) || (piVar1[1] == 0)) {
    sub_546170(0,0xffffff80,8);
    DAT_006da2fc = 0xf000;
  }
  piVar1 = (int *)*DAT_0058342c;
  if (((byte)DAT_005fcf08 & 0x80) == 0) {
    if (((piVar1 == (int *)0x0) || (DAT_0058342c[1] == 0)) || ((*piVar1 != 0 || (piVar1[1] == 0))))
    {
      DAT_00583914 = 4;
      DAT_0058342c = piVar1;
      sub_417750();
      return 0;
    }
    while ((((*DAT_0058342c == 0 || (piVar1 = (int *)DAT_0058342c[1], piVar1 == (int *)0x0)) ||
            (*piVar1 == 0)) || (piVar1[1] != 0))) {
      DAT_0058342c = (int *)DAT_0058342c[1];
    }
  }
  else if (((piVar1 == (int *)0x0) || (piVar1 = (int *)DAT_0058342c[1], piVar1 == (int *)0x0)) ||
          ((*piVar1 == 0 || (piVar2 = DAT_0058342c, piVar1[1] != 0)))) {
    DAT_0058342c = (int *)DAT_0058342c[1];
  }
  else {
    do {
      do {
        DAT_0058342c = piVar2;
        piVar2 = (int *)*DAT_0058342c;
      } while (piVar2 == (int *)0x0);
    } while (((DAT_0058342c[1] == 0) || (*piVar2 != 0)) || (piVar2[1] == 0));
  }
  DAT_00583914 = 4;
  sub_417750();
  return 0;
}

