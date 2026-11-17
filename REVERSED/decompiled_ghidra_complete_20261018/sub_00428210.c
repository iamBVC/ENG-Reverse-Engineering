/* sub_428210 @ 00428210   656 bytes */

void sub_428210(int *param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  byte *pbVar11;
  int iVar12;
  int local_28;
  int local_20;
  int local_1c;
  int local_c;
  
  *param_4 = -0x10000;
  param_4[1] = 1000000;
  uVar5 = *param_1 >> 0xc;
  uVar10 = param_1[2] >> 0xc;
  if ((((-1 < (int)uVar5) && (uVar5 < *(uint *)(param_3 + 0x14))) && (-1 < (int)uVar10)) &&
     (uVar10 < *(uint *)(param_3 + 0x18))) {
    for (piVar2 = *(int **)(*(int *)(param_3 + 0x40) +
                           (*(uint *)(param_3 + 0x14) * uVar10 + uVar5) * 4); piVar2 != (int *)0x0;
        piVar2 = (int *)piVar2[1]) {
      iVar6 = *(int *)(*(int *)(param_3 + 0x4c) + *piVar2 * 4);
      iVar1 = param_2 + iVar6 * 0x84;
      local_c = (uint)*(ushort *)(iVar1 + 0x7c) + (uint)*(ushort *)(param_2 + 0x7a + iVar6 * 0x84) +
                (uint)*(ushort *)(iVar1 + 0x78);
      if (local_c != 0) {
        iVar6 = *(int *)(param_3 + 0x3c);
        iVar3 = *piVar2 * 0x20;
        iVar8 = *param_1 - *(int *)(iVar3 + 0x10 + iVar6);
        local_28 = param_1[2] - *(int *)(iVar3 + iVar6 + 0x18);
        iVar12 = (param_1[1] - *(int *)(iVar3 + 0x14 + iVar6)) + 0x1000;
        iVar6 = -*(int *)(iVar3 + iVar6 + 4);
        uVar5 = iVar6 + 0x1000;
        if (uVar5 != 0) {
          iVar4 = (&DAT_00574318)[uVar5 & 0xfff] * iVar8;
          iVar8 = (&DAT_00574318)[uVar5 & 0xfff] * local_28 +
                  (&DAT_00574318)[iVar6 + 0x1400U & 0xfff] * iVar8 >> 0xc;
          local_28 = (&DAT_00574318)[iVar6 + 0x1400U & 0xfff] * local_28 - iVar4 >> 0xc;
        }
        if (local_c != 0) {
          local_1c = 0;
          do {
            pbVar11 = (byte *)(*(int *)(iVar1 + 0x80) + local_1c);
            iVar6 = (char)pbVar11[3] * 0x20;
            if (0 < iVar6) {
              iVar6 = (((*(short *)(pbVar11 + 6) * 0x1000 - (char)pbVar11[4] * 0x20 * local_28) -
                       (char)pbVar11[2] * 0x20 * iVar8) - iVar6 * iVar12) / iVar6;
              iVar4 = -iVar6;
              if ((-1 < iVar4) && (iVar4 < param_4[1])) {
                pbVar7 = pbVar11 + 8;
                uVar5 = (uint)((*pbVar11 & 1) != 0);
                iVar6 = iVar12 + iVar6;
                iVar9 = uVar5 + 3;
                local_20 = 0;
                if (uVar5 != 0xfffffffd) {
                  do {
                    if (((char)pbVar7[1] * 0x20 * iVar6 + (char)pbVar7[2] * 0x20 * local_28 +
                         (char)*pbVar7 * 0x20 * iVar8 >> 0xc) - (int)*(short *)(pbVar7 + 4) < -0x80)
                    break;
                    local_20 = local_20 + 1;
                    pbVar7 = pbVar7 + 6;
                  } while (local_20 < iVar9);
                }
                if (local_20 == iVar9) {
                  *param_4 = *(int *)(iVar3 + 0x14 + *(int *)(param_3 + 0x3c)) + iVar6;
                  param_4[1] = iVar4;
                  param_4[2] = (uint)pbVar11[1];
                }
              }
            }
            local_1c = local_1c + 0x20;
            local_c = local_c + -1;
          } while (local_c != 0);
        }
      }
    }
  }
  return;
}

