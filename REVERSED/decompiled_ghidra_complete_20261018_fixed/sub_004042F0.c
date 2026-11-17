/* sub_4042F0 @ 004042f0   1005 bytes */

void sub_4042F0(uint param_1,uint param_2,int param_3,int param_4,int param_5,int *param_6)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  byte *pbVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int local_28;
  int local_24;
  int local_18;
  
  if ((((-1 < (int)param_1) && (param_1 < *(uint *)(param_5 + 0x14))) && (-1 < (int)param_2)) &&
     (param_2 < *(uint *)(param_5 + 0x18))) {
    iVar5 = (int)*(short *)(*(int *)(param_3 + 0xc0) + 0x38);
    uVar2 = *(uint *)(param_3 + 0xe8);
    for (piVar3 = *(int **)(*(int *)(param_5 + 0x40) +
                           (*(uint *)(param_5 + 0x14) * param_2 + param_1) * 4);
        piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]) {
      iVar6 = *(int *)(*(int *)(param_5 + 0x4c) + *piVar3 * 4);
      iVar1 = param_4 + iVar6 * 0x84;
      iVar6 = (uint)*(ushort *)(iVar1 + 0x7c) + (uint)*(ushort *)(param_4 + 0x7a + iVar6 * 0x84) +
              (uint)*(ushort *)(iVar1 + 0x78);
      if (iVar6 != 0) {
        iVar10 = *piVar3 * 0x20 + *(int *)(param_5 + 0x3c);
        iVar19 = *(int *)(param_3 + 0x30) - *(int *)(iVar10 + 0x10);
        iVar7 = (int)*(short *)(*(int *)(param_3 + 0xc0) + 0x34) - *(int *)(iVar10 + 0x14);
        iVar17 = *(int *)(param_3 + 0x34) + iVar7;
        iVar18 = *(int *)(param_3 + 0x38) - *(int *)(iVar10 + 0x18);
        iVar15 = *(int *)(param_3 + 0x50) - *(int *)(iVar10 + 0x10);
        iVar4 = *(int *)(param_3 + 0x54);
        iVar8 = *(int *)(param_3 + 0x58) - *(int *)(iVar10 + 0x18);
        uVar11 = -*(int *)(iVar10 + 4);
        if (uVar11 != 0) {
          iVar10 = (&DAT_00574318)[uVar11 & 0xfff];
          iVar16 = (&DAT_00574318)[uVar11 + 0x400 & 0xfff];
          iVar13 = iVar10 * iVar19;
          iVar14 = iVar10 * iVar15;
          iVar19 = iVar10 * iVar18 + iVar16 * iVar19 >> 0xc;
          iVar18 = iVar16 * iVar18 - iVar13 >> 0xc;
          iVar15 = iVar10 * iVar8 + iVar16 * iVar15 >> 0xc;
          iVar8 = iVar16 * iVar8 - iVar14 >> 0xc;
        }
        local_24 = 0;
        if (iVar6 != 0) {
          local_18 = 0;
          do {
            pbVar12 = (byte *)(local_18 + *(int *)(iVar1 + 0x80));
            if (*(char *)(local_18 + 1 + *(int *)(iVar1 + 0x80)) !=
                (char)(((uVar2 & 0x8000000) != 0) + '\x11')) {
              iVar13 = (char)pbVar12[2] * 0x20;
              iVar10 = (char)pbVar12[3] * 0x20;
              iVar16 = (char)pbVar12[4] * 0x20;
              if ((((((*(byte *)(param_3 + 0xed) & 1) != 0) || (iVar10 < 0x801)) &&
                   ((iVar13 != 0 || (iVar16 != 0)))) &&
                  ((iVar16 * (iVar18 - iVar8) + iVar10 * (iVar17 - (iVar4 + iVar7)) +
                    iVar13 * (iVar19 - iVar15) < 1 &&
                   (iVar10 = (iVar16 * iVar18 + iVar13 * iVar19 + iVar10 * iVar17 >> 0xc) -
                             (int)*(short *)(pbVar12 + 6), -1 < iVar10)))) && (iVar10 < iVar5)) {
                local_28 = 0;
                uVar11 = (uint)((*pbVar12 & 1) != 0);
                pbVar12 = pbVar12 + 8;
                iVar14 = uVar11 + 3;
                if (uVar11 != 0xfffffffd) {
                  do {
                    iVar9 = ((char)pbVar12[2] * 0x20 * iVar18 + (char)pbVar12[1] * 0x20 * iVar17 +
                             (char)*pbVar12 * 0x20 * iVar19 >> 0xc) - (int)*(short *)(pbVar12 + 4);
                    if ((iVar9 < 0) &&
                       ((iVar9 < -iVar5 ||
                        (iVar20 = iVar5 * iVar5 - iVar10 * iVar10,
                        iVar9 * iVar9 - iVar20 != 0 && iVar20 <= iVar9 * iVar9)))) break;
                    local_28 = local_28 + 1;
                    pbVar12 = pbVar12 + 6;
                  } while (local_28 < iVar14);
                }
                if (local_28 == iVar14) {
                  uVar11 = *(uint *)(*piVar3 * 0x20 + 4 + *(int *)(param_5 + 0x3c));
                  iVar14 = (&DAT_00574318)[uVar11 & 0xfff];
                  iVar9 = (&DAT_00574318)[uVar11 + 0x400 & 0xfff];
                  iVar20 = iVar5 - iVar10;
                  param_6[4] = iVar10;
                  param_6[8] = param_6[8] +
                               ((iVar14 * iVar16 + iVar9 * iVar13 >> 0xc) * iVar20 >> 0xc);
                  param_6[0xc] = param_6[0xc] + iVar20;
                  *param_6 = iVar1;
                  param_6[0xb] = param_6[0xb] + 1;
                  param_6[10] = param_6[10] +
                                (iVar20 * (iVar9 * iVar16 - iVar14 * iVar13 >> 0xc) >> 0xc);
                  param_6[2] = (int)piVar3;
                  param_6[3] = local_24;
                }
              }
            }
            local_24 = local_24 + 1;
            local_18 = local_18 + 0x20;
          } while (local_24 < iVar6);
        }
      }
    }
  }
  return;
}

