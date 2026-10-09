/* sub_419460 @ 00419460   165 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_419460(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  _DAT_00584660 = (float)DAT_00583374 * _DAT_0056e248;
  DAT_005846e4 = 1;
  _DAT_005846f8 = 0;
  DAT_005846b4 = 0;
  _DAT_00584664 = (float)DAT_00583378 * _DAT_0056e244;
  sub_54B9F0(0,0);
  iVar1 = DAT_00580cfc;
  iVar2 = 0;
  DAT_00584640 = 0;
  if (0 < DAT_00580cfc) {
    piVar3 = &DAT_00580d0c;
    iVar4 = DAT_005846b0;
    do {
      if (((char)piVar3[2] != '\0') && (8 < *piVar3)) {
        *(int *)(&DAT_00584690 + iVar4 * 4) = iVar2;
        iVar4 = DAT_005846b0 + 1;
        DAT_005846b0 = iVar4;
        if (7 < iVar4) break;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 5;
    } while (iVar2 < iVar1);
  }
  sub_41EEA0();
  sub_41EE10();
  DAT_005846dc = 0;
  return;
}

