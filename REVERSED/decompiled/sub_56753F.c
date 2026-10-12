/* sub_56753F @ 0056753f   165 bytes */

void sub_56753F(void)

{
  int iVar1;
  undefined **ppuVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  iVar1 = 0x14;
  if (DAT_006db900 == 0) {
    iVar1 = 0x200;
  }
  else if (0x13 < DAT_006db900) goto LAB_0056755e;
  DAT_006db900 = iVar1;
LAB_0056755e:
  DAT_006da8e4 = sub_56AA33(DAT_006db900,4);
  if (DAT_006da8e4 == 0) {
    DAT_006db900 = 0x14;
    DAT_006da8e4 = sub_56AA33(0x14,4);
    if (DAT_006da8e4 == 0) {
      __amsg_exit(0x1a);
    }
  }
  iVar1 = 0;
  ppuVar2 = &PTR_DAT_0057ca30;
  do {
    *(undefined ***)(iVar1 + DAT_006da8e4) = ppuVar2;
    ppuVar2 = ppuVar2 + 8;
    iVar1 = iVar1 + 4;
  } while ((int)ppuVar2 < 0x57ccb0);
  uVar4 = 0;
  puVar3 = &DAT_0057ca40;
  do {
    iVar1 = *(int *)((&DAT_006da7e0)[(int)uVar4 >> 5] + (uVar4 & 0x1f) * 8);
    if ((iVar1 == -1) || (iVar1 == 0)) {
      *puVar3 = 0xffffffff;
    }
    puVar3 = puVar3 + 8;
    uVar4 = uVar4 + 1;
  } while ((int)puVar3 < 0x57caa0);
  return;
}

