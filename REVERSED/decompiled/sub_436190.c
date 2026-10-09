/* sub_436190 @ 00436190   836 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_436190(void)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int local_2c;
  int local_28;
  int local_24;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar9 = DAT_006d9e38;
  if (DAT_006d9e38 == 0) {
    return 1;
  }
  do {
    uVar2 = *(uint *)(iVar9 + 0xec);
    if ((uVar2 & 0x40000000) == 0) {
      if ((uVar2 & 0x40000) == 0) {
        *(uint *)(iVar9 + 0xec) = uVar2 | 0x8000;
      }
      else {
        iVar6 = DAT_00586590 + 0x800;
        if (DAT_006d9e28 == 0) goto LAB_0043626f;
        iVar8 = *(int *)(iVar9 + 0x30) - *(int *)(DAT_006d9e28 + 0x30);
        if (iVar8 < 0) {
          iVar8 = *(int *)(DAT_006d9e28 + 0x30) - *(int *)(iVar9 + 0x30);
        }
        if (iVar8 < iVar6) {
          iVar8 = *(int *)(iVar9 + 0x34) - *(int *)(DAT_006d9e28 + 0x34);
          if (iVar8 < 0) {
            iVar8 = *(int *)(DAT_006d9e28 + 0x34) - *(int *)(iVar9 + 0x34);
          }
          if (iVar8 < iVar6) {
            iVar8 = *(int *)(iVar9 + 0x38) - *(int *)(DAT_006d9e28 + 0x38);
            if (iVar8 < 0) {
              iVar8 = *(int *)(DAT_006d9e28 + 0x38) - *(int *)(iVar9 + 0x38);
            }
            if (iVar8 < iVar6) goto LAB_0043626f;
          }
        }
        *(uint *)(iVar9 + 0xec) = uVar2 | 0x8000;
      }
    }
    else {
      uVar3 = *(uint *)(*(int *)(iVar9 + 0xc) + 0xec);
      if (((uVar3 & 0x8000) == 0) && ((uVar3 & 0x40000) != 0)) {
LAB_0043626f:
        *(uint *)(iVar9 + 0xec) = *(uint *)(iVar9 + 0xec) & 0xffff7fff;
        if ((((*(int *)(iVar9 + 0x10) != 0) && (*(short *)(*(int *)(iVar9 + 0x10) + 0x6e) != 0)) &&
            ((*(uint *)(iVar9 + 0xe8) & 0x1000004) == 0)) && (*(int *)(iVar9 + 0x10c) != 0)) {
          local_c = (float)*(int *)(iVar9 + 0x30) * (float)_DAT_0056e020;
          local_8 = (float)*(int *)(iVar9 + 0x34) * (float)_DAT_0056e020;
          local_4 = -((float)*(int *)(iVar9 + 0x38) * (float)_DAT_0056e020);
          if ((*(uint *)(iVar9 + 0xe8) & 0x80) == 0) {
            if ((*(byte *)(iVar9 + 0xe8) & 0x20) != 0) {
              local_8 = local_8 + _DAT_0056e118;
            }
            local_18 = (float)*(int *)(iVar9 + 0x20) * (float)_DAT_0056e058;
            local_14 = (float)*(int *)(iVar9 + 0x24) * (float)_DAT_0056e058;
            local_10 = -((float)*(int *)(iVar9 + 0x28) * (float)_DAT_0056e058);
            local_24 = *(int *)(iVar9 + 0x60);
            if (local_24 == 0) {
              local_24 = 1;
            }
            fVar4 = (float)local_24;
            local_24 = *(int *)(iVar9 + 100);
            if (local_24 == 0) {
              local_24 = 1;
            }
            fVar5 = (float)local_24;
            local_24 = *(int *)(iVar9 + 0x68);
            if (local_24 == 0) {
              local_24 = 1;
            }
            iVar6 = *(int *)(iVar9 + 0x14);
            if (iVar6 == 0) {
              uVar7 = 0;
            }
            else {
              uVar7 = *(undefined4 *)(*(int *)(iVar6 + 0x1c) + *(int *)(iVar9 + 0x110) * 4);
            }
            sub_41FB30(*(undefined4 *)(iVar9 + 0x10),&local_18,fVar4 * (float)_DAT_0056e020,
                       fVar5 * (float)_DAT_0056e020,(float)local_24 * (float)_DAT_0056e020,
                       (float)*(uint *)(iVar9 + 0x10c) * _DAT_0056e28c,
                       *(uint *)(iVar9 + 0xec) >> 0x13 & 0xffffff01,iVar6 != 0,uVar7,0xffffffff,
                       0xffffffff,0xffffffff,1,iVar9 + 0x133);
          }
          else {
            local_18 = 0.0;
            local_14 = 0.0;
            local_10 = -((float)((*(int *)(iVar9 + 0x28) >> 0xc) - 0x800U & 0xfff) *
                        (float)_DAT_0056e058);
            local_28 = *(int *)(iVar9 + 0x60);
            if (local_28 == 0) {
              local_28 = 1;
            }
            local_2c = *(int *)(iVar9 + 100);
            if (local_2c == 0) {
              local_2c = 1;
            }
            local_24 = *(int *)(iVar9 + 0x68);
            if (local_24 == 0) {
              local_24 = 1;
            }
            sub_422740(*(undefined4 *)(iVar9 + 0x10),&local_18,
                       (float)local_28 * (float)_DAT_0056e020,(float)local_2c * (float)_DAT_0056e020
                       ,(float)local_24 * (float)_DAT_0056e020);
          }
        }
      }
      else {
        *(uint *)(iVar9 + 0xec) = uVar2 | 0x8000;
      }
    }
    piVar1 = (int *)(iVar9 + 4);
    iVar9 = *piVar1;
    if (*piVar1 == 0) {
      return 1;
    }
  } while( true );
}

