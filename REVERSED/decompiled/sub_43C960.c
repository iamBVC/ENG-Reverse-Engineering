/* sub_43C960 @ 0043c960   342 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_43C960(int param_1,int param_2,int param_3,int param_4,uint param_5,uint param_6,
               uint param_7)

{
  float *pfVar1;
  undefined4 *puVar2;
  float fVar3;
  
  fVar3 = (float)(((param_5 & 0xff | 0xffff8000) << 8 | param_6 & 0xff) << 8 | param_7 & 0xff);
  if (DAT_006d7c6f != '\0') {
    fVar3 = (float)((((int)(param_5 << 7) >> 8 & 0xffU | 0xffff8000) << 8 |
                    (int)(param_6 << 7) >> 8 & 0xffU) << 8 | (int)(param_7 << 7) >> 8 & 0xffU);
  }
  pfVar1 = (float *)sub_41ED90(0x80);
  if (pfVar1 != (float *)0x0) {
    pfVar1[0x1c] = fVar3;
    pfVar1[0x14] = fVar3;
    pfVar1[0xc] = fVar3;
    pfVar1[4] = fVar3;
    pfVar1[0x1d] = 0.0;
    pfVar1[0x15] = 0.0;
    pfVar1[0xd] = 0.0;
    pfVar1[5] = 0.0;
    pfVar1[0x1a] = 0.0;
    pfVar1[0x12] = 0.0;
    pfVar1[10] = 0.0;
    pfVar1[2] = 0.0;
    pfVar1[0x1b] = 1.0;
    pfVar1[0x13] = 1.0;
    pfVar1[0xb] = 1.0;
    pfVar1[3] = 1.0;
    fVar3 = (float)DAT_00583374 * _DAT_0056e1dc * (float)param_1;
    pfVar1[0x18] = fVar3;
    *pfVar1 = fVar3;
    fVar3 = (float)DAT_00583374 * _DAT_0056e1dc * (float)param_2;
    pfVar1[0x10] = fVar3;
    pfVar1[8] = fVar3;
    fVar3 = (float)DAT_00583378 * _DAT_0056e1d8 * (float)param_3;
    pfVar1[9] = fVar3;
    pfVar1[1] = fVar3;
    fVar3 = (float)DAT_00583378 * _DAT_0056e1d8 * (float)param_4;
    pfVar1[0x19] = fVar3;
    pfVar1[0x11] = fVar3;
    puVar2 = (undefined4 *)sub_41ED90(0x20);
    if (puVar2 != (undefined4 *)0x0) {
      puVar2[1] = pfVar1;
      *puVar2 = DAT_005f6ef8;
      puVar2[2] = 4;
      puVar2[3] = 0;
      puVar2[4] = 0;
      puVar2[5] = 0;
      puVar2[6] = 0;
      puVar2[7] = 0x506d;
      DAT_005f6ef8 = puVar2;
    }
  }
  return;
}

