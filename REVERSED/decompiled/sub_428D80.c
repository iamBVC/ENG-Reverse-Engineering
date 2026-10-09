/* sub_428D80 @ 00428d80   283 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_428D80(undefined4 *param_1,int *param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if ((int)param_1[0x104] < 0x14) {
    param_1[param_1[0x104] * 3] = (float)*param_2 * (float)_DAT_0056e020;
    param_1[param_1[0x104] * 3 + 1] = (float)param_2[1] * (float)_DAT_0056e020;
    param_1[param_1[0x104] * 3 + 2] = -((float)param_2[2] * (float)_DAT_0056e020);
    param_1[param_1[0x104] + 0xf0] =
         (uint)param_3._2_1_ | (param_3 & 0xff) << 0x10 | param_3 & 0xff00;
    param_1[0x104] = param_1[0x104] + 1;
    return;
  }
  iVar3 = 0x13;
  puVar2 = param_1 + 0xf0;
  puVar1 = param_1;
  do {
    iVar3 = iVar3 + -1;
    *puVar1 = puVar1[3];
    puVar1[1] = puVar1[4];
    puVar1[2] = puVar1[5];
    *puVar2 = puVar2[1];
    puVar2 = puVar2 + 1;
    puVar1 = puVar1 + 3;
  } while (iVar3 != 0);
  param_1[0x39] = (float)*param_2 * (float)_DAT_0056e020;
  param_1[0x3a] = (float)param_2[1] * (float)_DAT_0056e020;
  param_1[0x3b] = -((float)param_2[2] * (float)_DAT_0056e020);
  param_1[0x103] = (uint)param_3._2_1_ | (param_3 & 0xff) << 0x10 | param_3 & 0xff00;
  return;
}

