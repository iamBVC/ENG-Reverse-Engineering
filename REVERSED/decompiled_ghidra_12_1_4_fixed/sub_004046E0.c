/* sub_4046E0 @ 004046e0   1224 bytes */

void sub_4046E0(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  byte *pbVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int local_44;
  int local_3c;
  int local_34;
  int local_30;
  int local_28;
  int local_24;
  
  iVar4 = param_4;
  uVar1 = *(uint *)(param_1 + 0xe8);
  iVar3 = DAT_006d9e38;
  do {
    if (iVar3 == 0) {
      return;
    }
    if (((iVar3 != param_1) && ((*(byte *)(iVar3 + 0xec) & 0x20) != 0)) &&
       ((*(int *)(iVar3 + 0x60) != 0 || (*(int *)(iVar3 + 0x68) != 0)))) {
      iVar2 = *(int *)(iVar3 + 0x13c);
      iVar6 = *(int *)(param_1 + 0x30) - *(int *)(iVar3 + 0x30);
      iVar15 = *(int *)(param_1 + 0x38) - *(int *)(iVar3 + 0x38);
      if ((((iVar6 <= iVar2) && (-iVar2 <= iVar6)) && (iVar15 <= iVar2)) && (-iVar2 <= iVar15)) {
        iVar2 = *(int *)(iVar3 + 0x10);
        iVar7 = (uint)*(ushort *)(iVar2 + 0x7c) + (uint)*(ushort *)(iVar2 + 0x7a) +
                (uint)*(ushort *)(iVar2 + 0x78);
        if (iVar7 != 0) {
          local_34 = *(int *)(iVar3 + 0x60);
          if (*(int *)(iVar3 + 0x60) < *(int *)(iVar3 + 100)) {
            local_34 = *(int *)(iVar3 + 100);
          }
          if (local_34 < *(int *)(iVar3 + 0x68)) {
            local_34 = *(int *)(iVar3 + 0x68);
          }
          if (local_34 != 0) {
            if (local_34 < 0) {
              local_34 = -local_34;
            }
            iVar8 = ((int)*(short *)(*(int *)(param_1 + 0xc0) + 0x38) << 0xc) / local_34;
            iVar9 = (int)*(short *)(*(int *)(param_1 + 0xc0) + 0x34) - *(int *)(iVar3 + 0x34);
            iVar17 = *(int *)(param_1 + 0x50) - *(int *)(iVar3 + 0x30);
            iVar13 = *(int *)(param_1 + 0x58) - *(int *)(iVar3 + 0x38);
            sVar5 = -(short)(*(int *)(iVar3 + 0x24) >> 0xc);
            if (sVar5 == 0) {
              iVar18 = iVar6 * 0x1000;
              iVar17 = iVar15 * 0x1000;
              iVar13 = iVar17;
              param_4 = iVar18;
            }
            else {
              iVar10 = (&DAT_00574318)[(int)sVar5 & 0xfff];
              iVar11 = (&DAT_00574318)[(int)sVar5 + 0x400U & 0xfff];
              iVar18 = iVar10 * iVar13 + iVar11 * iVar17;
              iVar17 = iVar11 * iVar13 - iVar10 * iVar17;
              iVar13 = iVar11 * iVar15 - iVar10 * iVar6;
              param_4 = iVar10 * iVar15 + iVar11 * iVar6;
            }
            if (*(int *)(iVar3 + 0x60) == 0x1000) {
              param_4 = param_4 >> 0xc;
              iVar18 = iVar18 >> 0xc;
            }
            else {
              param_4 = param_4 / *(int *)(iVar3 + 0x60);
              iVar18 = iVar18 / *(int *)(iVar3 + 0x60);
            }
            if (*(int *)(iVar3 + 100) == 0) {
              local_44 = 0;
              local_3c = 0;
            }
            else {
              local_44 = ((*(int *)(param_1 + 0x34) + iVar9) * 0x1000) / *(int *)(iVar3 + 100);
              local_3c = ((*(int *)(param_1 + 0x54) + iVar9) * 0x1000) / *(int *)(iVar3 + 100);
            }
            if (*(int *)(iVar3 + 0x68) == 0x1000) {
              iVar13 = iVar13 >> 0xc;
              iVar17 = iVar17 >> 0xc;
            }
            else {
              iVar13 = iVar13 / *(int *)(iVar3 + 0x68);
              iVar17 = iVar17 / *(int *)(iVar3 + 0x68);
            }
            local_28 = 0;
            if (iVar7 != 0) {
              local_24 = 0;
              do {
                pbVar14 = (byte *)(*(int *)(iVar2 + 0x80) + local_24);
                if (*(char *)(*(int *)(iVar2 + 0x80) + 1 + local_24) !=
                    (char)(((uVar1 & 0x8000000) != 0) + '\x11')) {
                  iVar6 = (char)pbVar14[3] * 0x20;
                  iVar9 = (char)pbVar14[2] * 0x20;
                  iVar15 = (char)pbVar14[4] * 0x20;
                  if ((((iVar6 < 0x801) && ((iVar9 != 0 || (iVar15 != 0)))) &&
                      (iVar15 * (iVar13 - iVar17) + iVar6 * (local_44 - local_3c) +
                       iVar9 * (param_4 - iVar18) < 1)) &&
                     ((iVar6 = (iVar15 * iVar13 + iVar9 * param_4 + iVar6 * local_44 >> 0xc) -
                               (int)*(short *)(pbVar14 + 6), -1 < iVar6 && (iVar6 < iVar8)))) {
                    local_30 = 0;
                    uVar12 = (uint)((*pbVar14 & 1) != 0);
                    iVar10 = uVar12 + 3;
                    if (uVar12 != 0xfffffffd) {
                      pbVar14 = pbVar14 + 8;
                      do {
                        iVar11 = ((char)pbVar14[2] * 0x20 * iVar13 +
                                  (char)pbVar14[1] * 0x20 * local_44 +
                                  (char)*pbVar14 * 0x20 * param_4 >> 0xc) -
                                 (int)*(short *)(pbVar14 + 4);
                        if ((iVar11 < 0) &&
                           ((iVar11 < -iVar8 ||
                            (iVar16 = iVar8 * iVar8 - iVar6 * iVar6,
                            iVar11 * iVar11 - iVar16 != 0 && iVar16 <= iVar11 * iVar11)))) break;
                        local_30 = local_30 + 1;
                        pbVar14 = pbVar14 + 6;
                      } while (local_30 < iVar10);
                    }
                    if (local_30 == iVar10) {
                      uVar12 = *(int *)(iVar3 + 0x24) >> 0xc;
                      iVar10 = (&DAT_00574318)[uVar12 & 0xfff];
                      iVar11 = (&DAT_00574318)[uVar12 + 0x400 & 0xfff];
                      iVar16 = (iVar8 - iVar6) * local_34 >> 0xc;
                      *(int *)(iVar4 + 0x10) = iVar6;
                      *(int *)(iVar4 + 0x20) =
                           *(int *)(iVar4 + 0x20) +
                           ((iVar10 * iVar15 + iVar11 * iVar9 >> 0xc) * iVar16 >> 0xc);
                      *(int *)(iVar4 + 0x30) = *(int *)(iVar4 + 0x30) + iVar16;
                      *(int *)(iVar4 + 0x28) =
                           *(int *)(iVar4 + 0x28) +
                           (iVar16 * (iVar11 * iVar15 - iVar10 * iVar9 >> 0xc) >> 0xc);
                      *(int *)(iVar4 + 4) = iVar3;
                      *(int *)(iVar4 + 0x2c) = *(int *)(iVar4 + 0x2c) + 1;
                      *(int *)(iVar4 + 0xc) = local_28;
                    }
                  }
                }
                local_28 = local_28 + 1;
                local_24 = local_24 + 0x20;
              } while (local_28 < iVar7);
            }
          }
        }
      }
    }
    iVar3 = *(int *)(iVar3 + 4);
  } while( true );
}

