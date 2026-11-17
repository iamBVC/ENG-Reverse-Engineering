/* sub_41CD70 @ 0041cd70   50 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41CD70(void)

{
  int iVar1;
  undefined1 *puVar2;
  
  _DAT_00584ec4 = 0;
  puVar2 = &DAT_00584ece;
  do {
    iVar1 = 1;
    do {
      if ((puVar2[iVar1] & 2) != 0) {
        _DAT_00584ec4 = _DAT_00584ec4 + 1;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 6);
    puVar2 = puVar2 + 6;
  } while ((int)puVar2 < 0x584efe);
  return;
}

