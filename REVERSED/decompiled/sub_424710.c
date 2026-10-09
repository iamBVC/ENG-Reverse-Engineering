/* sub_424710 @ 00424710   483 bytes */

void sub_424710(undefined4 param_1,float param_2)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  pfVar1 = (float *)sub_41ED90(0xc0);
  if (pfVar1 != (float *)0x0) {
    pfVar2 = pfVar1 + 3;
    iVar6 = 6;
    do {
      pfVar2[1] = param_2;
      *pfVar2 = 1.0;
      pfVar2[2] = 0.0;
      pfVar2 = pfVar2 + 8;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    iVar6 = __ftol();
    iVar3 = __ftol();
    iVar4 = __ftol();
    *pfVar1 = (float)(iVar3 - iVar6);
    pfVar1[1] = (float)iVar4;
    pfVar1[8] = (float)iVar3;
    pfVar1[9] = (float)(iVar4 - iVar6);
    pfVar1[0x10] = (float)iVar3;
    pfVar1[0x11] = (float)(iVar4 + iVar6);
    iVar3 = __ftol();
    iVar4 = __ftol();
    pfVar1[0x18] = (float)(iVar3 + iVar6);
    pfVar1[0x19] = (float)iVar4;
    pfVar1[0x20] = (float)iVar3;
    pfVar1[0x21] = (float)(iVar4 + iVar6);
    pfVar1[0x28] = (float)iVar3;
    pfVar1[0x29] = (float)(iVar4 - iVar6);
    puVar5 = (undefined4 *)sub_41ED90(0x20);
    if (puVar5 != (undefined4 *)0x0) {
      puVar5[1] = pfVar1;
      *puVar5 = DAT_005f6ef8;
      puVar5[2] = 3;
      puVar5[3] = 0;
      puVar5[4] = 0;
      puVar5[5] = 0;
      puVar5[6] = 0;
      puVar5[7] = 0x69;
      DAT_005f6ef8 = puVar5;
    }
    puVar5 = (undefined4 *)sub_41ED90(0x20);
    if (puVar5 != (undefined4 *)0x0) {
      puVar5[1] = pfVar1 + 0x18;
      *puVar5 = DAT_005f6ef8;
      puVar5[2] = 3;
      puVar5[3] = 0;
      puVar5[4] = 0;
      puVar5[5] = 0;
      puVar5[6] = 0;
      puVar5[7] = 0x69;
      DAT_005f6ef8 = puVar5;
    }
  }
  return;
}

