/* Selected Ghidra export at 00417b20. */

undefined4 sub_417B20(void)

{
  byte *pbVar1;
  int *piVar2;
  int *piVar3;
  byte bVar4;
  
  piVar2 = (int *)*DAT_00583424;
  if (((((piVar2 == (int *)0x0) || (piVar3 = (int *)DAT_00583424[1], piVar3 == (int *)0x0)) ||
       (*piVar3 == 0)) || ((piVar3[1] != 0 || (*piVar2 != 0)))) || (piVar2[1] == 0)) {
    sub_546170(0,0xffffff80,8);
    DAT_006da2fc = 0xf000;
  }
  piVar2 = (int *)*DAT_00583424;
  if (((byte)DAT_005fcf08 & 0x80) == 0) {
    if (((piVar2 != (int *)0x0) && (DAT_00583424[1] != 0)) && ((*piVar2 == 0 && (piVar2[1] != 0))))
    {
      while ((((*DAT_00583424 == 0 || (piVar2 = (int *)DAT_00583424[1], piVar2 == (int *)0x0)) ||
              (*piVar2 == 0)) || (piVar2[1] != 0))) {
        pbVar1 = (byte *)(DAT_00583424 + 4);
        DAT_00583424 = (int *)DAT_00583424[1];
        DAT_00583b74 = *pbVar1 ^ *(byte *)(DAT_00583424 + 4);
      }
      goto LAB_00417c01;
    }
    bVar4 = *(byte *)(DAT_00583424 + 4);
    DAT_00583424 = (int *)*DAT_00583424;
  }
  else {
    if (((piVar2 != (int *)0x0) && (piVar2 = (int *)DAT_00583424[1], piVar2 != (int *)0x0)) &&
       ((*piVar2 != 0 && (piVar2[1] == 0)))) {
      while ((((piVar2 = (int *)*DAT_00583424, piVar2 == (int *)0x0 || (DAT_00583424[1] == 0)) ||
              (*piVar2 != 0)) || (piVar2[1] == 0))) {
        pbVar1 = (byte *)(DAT_00583424 + 4);
        DAT_00583424 = (int *)*DAT_00583424;
        DAT_00583b74 = *pbVar1 ^ *(byte *)(DAT_00583424 + 4);
      }
      goto LAB_00417c01;
    }
    bVar4 = *(byte *)(DAT_00583424 + 4);
    DAT_00583424 = (int *)DAT_00583424[1];
  }
  DAT_00583b74 = bVar4 ^ *(byte *)(DAT_00583424 + 4);
LAB_00417c01:
  DAT_00583914 = 2;
  sub_417750();
  return 0;
}

