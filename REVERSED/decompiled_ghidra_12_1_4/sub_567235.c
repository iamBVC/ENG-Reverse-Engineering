/* sub_567235 @ 00567235   120 bytes */

undefined4 * sub_567235(void)

{
  int iVar1;
  void *pvVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  iVar1 = 0;
  piVar4 = DAT_006da8e4;
  if (0 < DAT_006db900) {
    do {
      if (*piVar4 == 0) {
        pvVar2 = _malloc(0x20);
        DAT_006da8e4[iVar1] = (int)pvVar2;
        puVar3 = (undefined4 *)DAT_006da8e4[iVar1];
        if (puVar3 == (undefined4 *)0x0) {
          return (undefined4 *)0x0;
        }
LAB_00567290:
        if (puVar3 == (undefined4 *)0x0) {
          return (undefined4 *)0x0;
        }
        puVar3[4] = 0xffffffff;
        puVar3[1] = 0;
        puVar3[3] = 0;
        puVar3[2] = 0;
        *puVar3 = 0;
        puVar3[7] = 0;
        return puVar3;
      }
      if ((*(byte *)(*piVar4 + 0xc) & 0x83) == 0) {
        puVar3 = (undefined4 *)DAT_006da8e4[iVar1];
        goto LAB_00567290;
      }
      iVar1 = iVar1 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar1 < DAT_006db900);
  }
  return (undefined4 *)0x0;
}

