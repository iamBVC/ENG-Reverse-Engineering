/* sub_545C00 @ 00545c00   469 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_545C00(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  
  if (DAT_006d9490 != 0) {
    sub_5458D0();
    if (*(int *)(DAT_006d9490 + 0xfc) != 0) {
      iVar5 = *(int *)(DAT_006d9490 + 0xfc) + *(int *)(DAT_006d9490 + 0x100);
      if (iVar5 < 0) {
        iVar5 = 0;
      }
      else if (0x1000 < iVar5) {
        iVar5 = 0x1000;
      }
      *(int *)(DAT_006d9490 + 0x100) = iVar5;
      if (*(int *)(DAT_006d9490 + 0x100) == *(int *)(DAT_006d9490 + 0xf4)) {
        *(undefined4 *)(DAT_006d9490 + 0xfc) = 0;
      }
    }
    iVar5 = DAT_00581168;
    if ((DAT_00581168 != 0) && (DAT_005834f4 != 0)) {
      *(uint *)(DAT_006d9490 + 0x68) = *(uint *)(DAT_006d9490 + 0x68) | 0x14000;
      *(undefined4 *)(DAT_006d9490 + 0xb0) = *(undefined4 *)(iVar5 + 0xc);
      *(undefined4 *)(DAT_006d9490 + 0xb4) = *(undefined4 *)(iVar5 + 0x10);
      *(undefined4 *)(DAT_006d9490 + 0xb8) = *(undefined4 *)(iVar5 + 0x14);
      fVar1 = _DAT_0057db40 * _DAT_0056e418;
      fVar4 = _DAT_0057db44 * _DAT_0056e418;
      fVar3 = _DAT_0057db48 * _DAT_0056e418;
      fVar6 = fVar1 * fVar1 + fVar4 * fVar4 + fVar3 * fVar3;
      fVar2 = fVar6 * _DAT_0056e158;
      fVar6 = (float)(0x5f3759df - ((int)fVar6 >> 1));
      fVar6 = (_DAT_0056e184 - fVar6 * fVar6 * fVar2) * fVar6;
      fVar6 = (_DAT_0056e184 - fVar6 * fVar6 * fVar2) * fVar6;
      *(float *)(DAT_006d9490 + 0xd0) = fVar1 * fVar6;
      *(float *)(DAT_006d9490 + 0xd4) = fVar6 * fVar4;
      *(float *)(DAT_006d9490 + 0xd8) = fVar6 * fVar3;
      *(undefined4 *)(DAT_006d9490 + 0xe0) = 0;
      *(undefined4 *)(DAT_006d9490 + 0xe4) = 0x3f800000;
      *(undefined4 *)(DAT_006d9490 + 0xe8) = 0;
    }
    sub_5476C0(DAT_006d9490,0);
  }
  return;
}

