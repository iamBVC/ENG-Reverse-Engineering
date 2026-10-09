/* sub_417750 @ 00417750   701 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_417750(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int local_c;
  int local_8;
  int local_4;
  
  piVar3 = DAT_00583428;
  piVar4 = DAT_0058342c;
  switch(DAT_00583914) {
  case 0:
    iVar2 = DAT_00583420[3];
    for (piVar3 = DAT_00583410; (*piVar3 != 0 || (piVar3[1] == 0)); piVar3 = (int *)*piVar3) {
      iVar1 = sub_4134F0(piVar3,iVar2);
      if (iVar1 == 0) goto LAB_0041779a;
      if (0 < iVar1) break;
    }
    piVar3 = (int *)0x0;
LAB_0041779a:
    DAT_00583420 = piVar3;
    if (piVar3 == (int *)0x0) {
      DAT_00583420 = DAT_00583418;
    }
  case 1:
    DAT_00583b74 = *(byte *)(DAT_00583424 + 4);
    iVar2 = DAT_00583424[3];
    for (piVar3 = (int *)DAT_00583420[7]; (*piVar3 != 0 || (piVar3[1] == 0));
        piVar3 = (int *)*piVar3) {
      iVar1 = sub_4134F0(piVar3,iVar2);
      if (iVar1 == 0) goto LAB_004177eb;
      if (0 < iVar1) break;
    }
    piVar3 = (int *)0x0;
LAB_004177eb:
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)DAT_00583420[9];
    }
    DAT_00583b74 = DAT_00583b74 ^ *(byte *)(piVar3 + 4);
    DAT_00583424 = piVar3;
  case 2:
    if (DAT_00583b74 == 0) {
      local_c = DAT_00583428[3];
    }
    else if ((char)DAT_00583424[4] == '\0') {
      local_c = DAT_00583434;
      DAT_00583440 = DAT_00583428[3];
    }
    else {
      local_c = DAT_00583440;
      DAT_00583434 = DAT_00583428[3];
    }
    for (piVar3 = (int *)DAT_00583424[0xb]; (*piVar3 != 0 || (piVar3[1] == 0));
        piVar3 = (int *)*piVar3) {
      iVar2 = sub_4136C0(piVar3,&local_c);
      if (iVar2 == 0) goto LAB_0041788e;
      if (0 < iVar2) break;
    }
    piVar3 = (int *)0x0;
LAB_0041788e:
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)DAT_00583424[0xb];
      if (piVar3 == DAT_00583424 + 0xc) {
        piVar3 = (int *)0x0;
      }
      else {
        DAT_00583428 = (int *)0x0;
        for (piVar4 = (int *)*piVar3; (*piVar4 != 0 || (piVar4[1] == 0)); piVar4 = (int *)*piVar4) {
          iVar2 = sub_4136D0(piVar4,piVar3,&local_c);
          if (0 < iVar2) {
            piVar3 = piVar4;
          }
        }
      }
    }
  case 3:
    DAT_00583428 = piVar3;
    if (DAT_00583b74 == 0) {
      local_8 = DAT_0058342c[3];
      local_4 = DAT_0058342c[4];
    }
    else if ((char)DAT_00583424[4] == '\0') {
      DAT_00583444 = DAT_0058342c[3];
      DAT_00583448 = DAT_0058342c[4];
      local_8 = DAT_00583438;
      local_4 = DAT_0058343c;
    }
    else {
      DAT_00583438 = DAT_0058342c[3];
      DAT_0058343c = DAT_0058342c[4];
      local_8 = DAT_00583444;
      local_4 = DAT_00583448;
    }
    for (piVar4 = (int *)DAT_00583428[0xc]; (*piVar4 != 0 || (piVar4[1] == 0));
        piVar4 = (int *)*piVar4) {
      iVar2 = sub_4137B0(piVar4,&local_8);
      if (iVar2 == 0) goto LAB_0041797f;
      if (0 < iVar2) break;
    }
    piVar4 = (int *)0x0;
LAB_0041797f:
    if (piVar4 == (int *)0x0) {
      piVar4 = (int *)DAT_00583428[0xc];
      if (piVar4 == DAT_00583428 + 0xd) {
        piVar4 = (int *)0x0;
      }
      else {
        DAT_0058342c = (int *)0x0;
        for (piVar3 = (int *)*piVar4; (*piVar3 != 0 || (piVar3[1] == 0)); piVar3 = (int *)*piVar3) {
          iVar2 = sub_4137D0(piVar3,piVar4,&local_8);
          if (0 < iVar2) {
            piVar4 = piVar3;
          }
        }
      }
    }
  }
  DAT_0058342c = piVar4;
  DAT_00583b74 = 0;
  _DAT_00583d30 = DAT_00583420[2];
  _DAT_00583d48 = DAT_00583424[2];
  _DAT_00583d60 = DAT_00583428[2];
  _DAT_00583d78 = DAT_0058342c[2];
  return;
}

