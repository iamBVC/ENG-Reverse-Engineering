/* sub_40FD00 @ 0040fd00   128 bytes */

void sub_40FD00(void)

{
  int *piVar1;
  int *piVar2;
  
  sub_40FE10();
  piVar1 = DAT_00583410;
  if (DAT_00583410 != (int *)&DAT_00583414) {
    do {
      piVar2 = piVar1;
      if ((*piVar1 != 0) && (piVar1[1] != 0)) {
        *(int *)(*piVar1 + 4) = piVar1[1];
        *(int *)piVar1[1] = *piVar1;
        *piVar1 = 0;
        piVar1[1] = 0;
        piVar2 = DAT_00583410;
      }
      if (piVar1 != (int *)0x0) {
        sub_413170();
        sub_562941(piVar1);
        piVar2 = DAT_00583410;
      }
      piVar1 = piVar2;
    } while (piVar2 != (int *)&DAT_00583414);
  }
  if (DAT_00583408 != (HMODULE)0x0) {
    FreeLibrary(DAT_00583408);
    DAT_00583408 = (HMODULE)0x0;
  }
  return;
}

