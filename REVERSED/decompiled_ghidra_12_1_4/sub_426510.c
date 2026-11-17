/* sub_426510 @ 00426510   471 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_426510(uint param_1,uint param_2,uint param_3,uint param_4,byte param_5,byte param_6,
               byte param_7,uint param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  byte bVar4;
  float *pfVar5;
  float fVar6;
  undefined4 *puVar7;
  int local_10;
  uint local_c;
  
  pfVar5 = (float *)sub_41ED90(0x80);
  if (pfVar5 != (float *)0x0) {
    if (((param_8 & 2) == 0) || (DAT_006d7c66 == '\0')) {
      local_c = 0;
      local_10 = 0;
    }
    else {
      local_c = 1;
      local_10 = 1;
    }
    pfVar5[0x1d] = 0.0;
    pfVar5[0x15] = 0.0;
    pfVar5[0xd] = 0.0;
    pfVar5[5] = 0.0;
    pfVar5[0x1a] = 0.0;
    pfVar5[0x12] = 0.0;
    fVar6 = (float)(((((-(uint)((param_8 & 2) != 0) & 0xffffff81) + 0xff) * 0x100 | (uint)param_5)
                     << 8 | (uint)param_6) << 8 | (uint)param_7);
    pfVar5[10] = 0.0;
    pfVar5[0x1c] = fVar6;
    pfVar5[0x14] = fVar6;
    pfVar5[0xc] = fVar6;
    pfVar5[4] = fVar6;
    pfVar5[2] = 0.0;
    pfVar5[0x1b] = 1.0;
    pfVar5[0x13] = 1.0;
    pfVar5[0xb] = 1.0;
    pfVar5[3] = 1.0;
    fVar6 = (float)param_1 * (float)DAT_00583374 * _DAT_0056e1dc;
    fVar1 = (float)param_3 * (float)DAT_00583374 * _DAT_0056e1dc + fVar6;
    fVar2 = (float)DAT_00583378;
    pfVar5[0x10] = fVar1;
    fVar2 = fVar2 * _DAT_0056e1d8;
    fVar3 = (float)param_2 * fVar2;
    pfVar5[8] = fVar1;
    fVar1 = fVar3 - (float)param_4 * fVar2;
    pfVar5[9] = fVar1;
    pfVar5[1] = fVar1;
    pfVar5[0x18] = fVar6;
    *pfVar5 = fVar6;
    pfVar5[0x19] = fVar3;
    pfVar5[0x11] = fVar3;
    if ((param_5 == param_6) && (param_6 == param_7)) {
      bVar4 = 1;
    }
    else {
      bVar4 = 0;
    }
    puVar7 = (undefined4 *)sub_41ED90(0x20);
    if (puVar7 != (undefined4 *)0x0) {
      *puVar7 = (&DAT_005f6ef8)[param_8 & 1];
      puVar7[3] = 0;
      puVar7[4] = 0;
      puVar7[5] = 0;
      puVar7[6] = 0;
      puVar7[1] = pfVar5;
      puVar7[2] = 4;
      puVar7[7] = (local_10 * 4 | local_c) << 0xc | -(uint)bVar4 & 4 | 0x69;
      (&DAT_005f6ef8)[param_8 & 1] = puVar7;
    }
  }
  return;
}

