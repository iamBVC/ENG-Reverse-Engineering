/* sub_41FA30 @ 0041fa30   250 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41FA30(uint param_1,int param_2,int param_3)

{
  ushort uVar1;
  byte bVar2;
  short *psVar3;
  float *pfVar4;
  ushort *puVar5;
  int iVar6;
  
  iVar6 = *(int *)(param_2 + 0x10);
  if (param_3 == 0) {
    pfVar4 = *(float **)(param_1 + 0x70);
    psVar3 = (short *)**(undefined4 **)(param_2 + 0x14);
    for (; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar4 = (float)(int)*psVar3 * (float)_DAT_0056e020;
      pfVar4[1] = (float)(int)psVar3[1] * (float)_DAT_0056e020;
      pfVar4[2] = (float)(int)psVar3[2] * (float)_DAT_0056e020;
      pfVar4 = pfVar4 + 6;
      psVar3 = psVar3 + 4;
    }
  }
  else {
    pfVar4 = *(float **)(param_1 + 0x70);
    puVar5 = *(ushort **)(*(int *)(param_2 + 0x14) + param_3 * 4);
    if (iVar6 != 0) {
      do {
        uVar1 = *puVar5;
        param_1 = (uint)uVar1;
        puVar5 = puVar5 + 1;
        bVar2 = (byte)(uVar1 >> 0xc);
        *pfVar4 = (float)(((int)(param_1 << 0x1c) >> 0x1c) << bVar2) * (float)_DAT_0056e020 +
                  *pfVar4;
        iVar6 = iVar6 + -1;
        pfVar4[1] = (float)(((int)(param_1 << 0x18) >> 0x1c) << bVar2) * (float)_DAT_0056e020 +
                    pfVar4[1];
        pfVar4[2] = (float)(((int)(param_1 << 0x14) >> 0x1c) << bVar2) * (float)_DAT_0056e020 +
                    pfVar4[2];
        pfVar4 = pfVar4 + 6;
      } while (iVar6 != 0);
      return;
    }
  }
  return;
}

