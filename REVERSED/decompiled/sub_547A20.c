/* sub_547A20 @ 00547a20   317 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

short sub_547A20(int param_1,short *param_2,short param_3,short param_4)

{
  int iVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  uint uVar5;
  uint uVar6;
  undefined2 uVar7;
  
  sVar3 = *(short *)(param_1 + 0x76);
  if (*(int *)(DAT_006d9490 + 0x58) == 2) {
    *param_2 = param_3;
    param_2[1] = param_3;
    uVar7 = 0;
  }
  else {
    if (sVar3 < 0x801) {
      uVar5 = (int)((int)sVar3 - 0x400U) >> 0x1f;
      uVar6 = (uint)param_3;
      *param_2 = param_3;
      param_3 = (short)((int)((((int)sVar3 - 0x400U ^ uVar5) - uVar5) * uVar6) >> 10);
    }
    else {
      uVar6 = (int)((int)sVar3 - 0xc00U) >> 0x1f;
      *param_2 = (short)((int)((((int)sVar3 - 0xc00U ^ uVar6) - uVar6) * (int)param_3) >> 10);
    }
    uVar7 = (undefined2)(uVar6 >> 0x10);
    param_2[1] = param_3;
  }
  if ((*(uint *)(param_1 + 0x3c) & 0x2000) == 0) {
    if (param_4 == 0) {
      if ((DAT_005834f4 != 0) && (iVar2 = *(int *)(param_1 + 0x88), iVar2 != 0)) {
        *(uint *)(iVar2 + 0x10) = *(uint *)(iVar2 + 0x10) | 0x40;
        iVar1 = *(int *)(param_1 + 0x34);
        *(undefined4 *)(iVar2 + 0x2c) = 0x461c4000;
        *(float *)(iVar2 + 0x28) = (float)iVar1 * _DAT_0056e50c;
      }
      sVar3 = 1;
    }
    else {
      sVar3 = sub_5479E0(param_2,CONCAT22(uVar7,*(undefined2 *)(param_1 + 100)));
      sVar4 = sub_5479E0(param_2 + 1,*(undefined2 *)(param_1 + 0x66));
      sVar3 = sVar3 + sVar4;
    }
    if (((DAT_005834f4 != 0) && (sVar3 != 0)) && (iVar2 = *(int *)(param_1 + 0x88), iVar2 != 0)) {
      *(uint *)(iVar2 + 0x10) = *(uint *)(iVar2 + 0x10) | 0x1000;
      *(float *)(iVar2 + 0x30) = (float)*(int *)(param_1 + 0x24) * (float)_DAT_0056e020;
      *(float *)(iVar2 + 0x34) = (float)*(int *)(param_1 + 0x28) * (float)_DAT_0056e020;
      *(float *)(iVar2 + 0x38) = -((float)*(int *)(param_1 + 0x2c) * (float)_DAT_0056e020);
    }
    return sVar3;
  }
  return 1;
}

