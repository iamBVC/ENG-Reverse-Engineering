/* Selected Ghidra export at 00424900. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_424900(void)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  undefined4 *puVar10;
  int iVar11;
  
  iVar3 = __ftol();
  iVar4 = __ftol();
  iVar5 = __ftol();
  iVar6 = __ftol();
  __ftol();
  iVar7 = __ftol();
  pfVar8 = (float *)sub_41ED90(0x180);
  if (pfVar8 != (float *)0x0) {
    pfVar9 = pfVar8 + 5;
    iVar11 = 3;
    do {
      pfVar9[-2] = 1.0;
      *pfVar9 = 0.0;
      pfVar9 = pfVar9 + 8;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    *pfVar8 = (float)(iVar4 - iVar5);
    fVar1 = (float)(iVar6 + iVar3);
    pfVar8[8] = (float)iVar4;
    pfVar8[1] = fVar1;
    fVar2 = (float)iVar3;
    pfVar8[0xc] = 2.3495283e-38;
    pfVar8[0x14] = 2.3495283e-38;
    pfVar8[9] = fVar2;
    pfVar8[0x10] = (float)iVar4;
    pfVar8[0x11] = fVar1;
    pfVar8[4] = 1.6580612e-38;
    pfVar8[0x1c] = 4.425502e-39;
    pfVar8[0x24] = 4.425502e-39;
    pfVar8[0x18] = (float)(iVar7 + -3);
    pfVar8[0x2c] = 4.425502e-39;
    pfVar8[0x19] = fVar2;
    pfVar8[0x20] = (float)(iVar7 + 3);
    pfVar8[0x21] = fVar2;
    pfVar8[0x28] = (float)iVar7;
    pfVar8[0x29] = fVar1;
    puVar10 = (undefined4 *)sub_41ED90(0x20);
    if (puVar10 != (undefined4 *)0x0) {
      puVar10[1] = pfVar8 + 0x18;
      *puVar10 = DAT_005f6ef8;
      puVar10[2] = 3;
      puVar10[3] = 0;
      puVar10[4] = 0;
      puVar10[5] = 0;
      puVar10[6] = 0;
      puVar10[7] = 0x61;
      DAT_005f6ef8 = puVar10;
    }
    puVar10 = (undefined4 *)sub_41ED90(0x20);
    if (puVar10 != (undefined4 *)0x0) {
      puVar10[1] = pfVar8;
      *puVar10 = DAT_005f6ef8;
      puVar10[2] = 3;
      puVar10[3] = 0;
      puVar10[4] = 0;
      puVar10[5] = 0;
      puVar10[6] = 0;
      puVar10[7] = 0x61;
      DAT_005f6ef8 = puVar10;
    }
  }
  return;
}

