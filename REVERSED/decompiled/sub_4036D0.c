/* sub_4036D0 @ 004036d0   1023 bytes */

void sub_4036D0(int param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int local_28;
  int local_24;
  int local_20;
  int local_c;
  
  piVar4 = param_4;
  uVar8 = *(int *)(param_1 + 0x30) >> 0xc;
  uVar11 = *(int *)(param_1 + 0x38) >> 0xc;
  if ((((-1 < (int)uVar8) && (uVar8 < *(uint *)(param_3 + 0x14))) && (-1 < (int)uVar11)) &&
     (uVar11 < *(uint *)(param_3 + 0x18))) {
    uVar2 = *(uint *)(param_1 + 0xe8);
    for (piVar3 = *(int **)(*(int *)(param_3 + 0x40) +
                           (*(uint *)(param_3 + 0x14) * uVar11 + uVar8) * 4); piVar3 != (int *)0x0;
        piVar3 = (int *)piVar3[1]) {
      iVar12 = *(int *)(*(int *)(param_3 + 0x4c) + *piVar3 * 4);
      iVar1 = param_2 + iVar12 * 0x84;
      iVar12 = (uint)*(ushort *)(iVar1 + 0x7c) + (uint)*(ushort *)(param_2 + 0x7a + iVar12 * 0x84) +
               (uint)*(ushort *)(iVar1 + 0x78);
      if (iVar12 != 0) {
        iVar5 = *piVar3 * 0x20 + *(int *)(param_3 + 0x3c);
        local_20 = *(int *)(param_1 + 0x30) - *(int *)(iVar5 + 0x10);
        local_24 = *(int *)(param_1 + 0x38) - *(int *)(iVar5 + 0x18);
        iVar9 = (*(int *)(param_1 + 0x34) - *(int *)(iVar5 + 0x14)) + DAT_0057dd98;
        uVar8 = -*(int *)(iVar5 + 4);
        if (uVar8 != 0) {
          iVar5 = (&DAT_00574318)[uVar8 & 0xfff] * local_20;
          local_20 = (&DAT_00574318)[uVar8 & 0xfff] * local_24 +
                     (&DAT_00574318)[uVar8 + 0x400 & 0xfff] * local_20 >> 0xc;
          local_24 = (&DAT_00574318)[uVar8 + 0x400 & 0xfff] * local_24 - iVar5 >> 0xc;
        }
        local_28 = 0;
        if (iVar12 != 0) {
          local_c = 0;
          do {
            pbVar10 = (byte *)(local_c + *(int *)(iVar1 + 0x80));
            if (pbVar10[1] != (byte)(((uVar2 & 0x8000000) != 0) + 0x11U)) {
              iVar5 = (int)(char)pbVar10[3];
              iVar14 = iVar5 * 0x20;
              if ((iVar14 != 0) && (((*(uint *)(param_1 + 0xe8) & 0x200000) != 0 || (-1 < iVar14))))
              {
                iVar6 = (((*(short *)(pbVar10 + 6) * 0x1000 - (char)pbVar10[4] * 0x20 * local_24) -
                         (char)pbVar10[2] * 0x20 * local_20) - iVar14 * iVar9) / iVar14;
                iVar7 = -iVar6;
                if (iVar7 < -0x80) {
                  if (((0 < iVar14) && (-piVar4[7] != iVar6 && piVar4[7] <= iVar7)) ||
                     (-piVar4[0x10] != iVar6 && piVar4[0x10] <= iVar7)) {
                    iVar15 = iVar9 + iVar6;
                    uVar8 = (uint)((*pbVar10 & 1) != 0);
                    pbVar10 = pbVar10 + 8;
                    iVar13 = uVar8 + 3;
                    param_4 = (int *)0x0;
                    if (uVar8 != 0xfffffffd) {
                      do {
                        if (((char)pbVar10[1] * 0x20 * iVar15 + (char)pbVar10[2] * 0x20 * local_24 +
                             (char)*pbVar10 * 0x20 * local_20 >> 0xc) - (int)*(short *)(pbVar10 + 4)
                            < -0x40 - (iVar5 * -0x20 + 0x1000 >> 6)) break;
                        param_4 = (int *)((int)param_4 + 1);
                        pbVar10 = pbVar10 + 6;
                      } while ((int)param_4 < iVar13);
                    }
                    if (param_4 == (int *)iVar13) {
                      if ((iVar14 < 1) || (-piVar4[7] == iVar6 || iVar7 < piVar4[7])) {
                        piVar4[0xe] = local_28;
                        piVar4[0xd] = iVar1;
                        iVar5 = *(int *)(*piVar3 * 0x20 + 0x14 + *(int *)(param_3 + 0x3c));
                        piVar4[0x10] = iVar7;
                        piVar4[0xf] = iVar5 + iVar15;
                      }
                      else {
                        iVar5 = *(int *)(*piVar3 * 0x20 + 0x14 + *(int *)(param_3 + 0x3c));
                        piVar4[7] = iVar7;
                        piVar4[6] = iVar5 + iVar15;
                        piVar4[8] = iVar1;
                        piVar4[9] = *piVar3;
                        piVar4[0xb] = local_28;
                      }
                    }
                  }
                }
                else if ((iVar7 < piVar4[1]) && (0 < iVar14)) {
                  uVar8 = (uint)((*pbVar10 & 1) != 0);
                  pbVar10 = pbVar10 + 8;
                  iVar14 = uVar8 + 3;
                  param_4 = (int *)0x0;
                  if (uVar8 != 0xfffffffd) {
                    do {
                      if (((char)pbVar10[1] * 0x20 * (iVar9 + iVar6) +
                           (char)pbVar10[2] * 0x20 * local_24 + (char)*pbVar10 * 0x20 * local_20 >>
                          0xc) - (int)*(short *)(pbVar10 + 4) <
                          -0x40 - (iVar5 * -0x20 + 0x1000 >> 6)) break;
                      param_4 = (int *)((int)param_4 + 1);
                      pbVar10 = pbVar10 + 6;
                    } while ((int)param_4 < iVar14);
                  }
                  if (param_4 == (int *)iVar14) {
                    iVar5 = *(int *)(*piVar3 * 0x20 + 0x14 + *(int *)(param_3 + 0x3c));
                    piVar4[1] = iVar7;
                    *piVar4 = iVar5 + iVar9 + iVar6;
                    piVar4[2] = iVar1;
                    piVar4[3] = *piVar3;
                    piVar4[5] = local_28;
                  }
                }
              }
            }
            local_28 = local_28 + 1;
            local_c = local_c + 0x20;
          } while (local_28 < iVar12);
        }
      }
    }
  }
  return;
}

