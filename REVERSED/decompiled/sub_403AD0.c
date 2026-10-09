/* sub_403AD0 @ 00403ad0   1033 bytes */

void sub_403AD0(int param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  byte *pbVar12;
  int iVar13;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_14;
  
  uVar1 = *(uint *)(param_1 + 0xe8);
  iVar3 = DAT_006d9e38;
  do {
    if (iVar3 == 0) {
      return;
    }
    if (((iVar3 != param_1) && ((*(byte *)(iVar3 + 0xec) & 0x20) != 0)) &&
       ((*(int *)(iVar3 + 0x60) != 0 || (*(int *)(iVar3 + 0x68) != 0)))) {
      iVar10 = *(int *)(param_1 + 0x30) - *(int *)(iVar3 + 0x30);
      iVar2 = *(int *)(iVar3 + 0x13c);
      iVar13 = *(int *)(param_1 + 0x38) - *(int *)(iVar3 + 0x38);
      if ((((iVar10 <= iVar2) && (-iVar2 <= iVar10)) && (iVar13 <= iVar2)) && (-iVar2 <= iVar13)) {
        iVar2 = *(int *)(iVar3 + 0x10);
        iVar6 = (uint)*(ushort *)(iVar2 + 0x7c) + (uint)*(ushort *)(iVar2 + 0x7a) +
                (uint)*(ushort *)(iVar2 + 0x78);
        if (iVar6 != 0) {
          uVar7 = (uint)(short)-(short)(*(int *)(iVar3 + 0x24) >> 0xc);
          local_28 = (&DAT_00574318)[uVar7 + 0x400 & 0xfff] * iVar13 -
                     (&DAT_00574318)[uVar7 & 0xfff] * iVar10;
          local_2c = (&DAT_00574318)[uVar7 & 0xfff] * iVar13 +
                     (&DAT_00574318)[uVar7 + 0x400 & 0xfff] * iVar10;
          if (*(int *)(iVar3 + 100) == 0) {
            iVar10 = 0;
          }
          else {
            iVar10 = ((*(int *)(param_1 + 0x34) - *(int *)(iVar3 + 0x34)) * 0x1000) /
                     *(int *)(iVar3 + 100);
          }
          iVar10 = iVar10 + DAT_0057dd98;
          if (*(int *)(iVar3 + 0x60) == 0x1000) {
            local_2c = local_2c >> 0xc;
          }
          else {
            local_2c = local_2c / *(int *)(iVar3 + 0x60);
          }
          if (*(int *)(iVar3 + 0x68) == 0x1000) {
            local_28 = local_28 >> 0xc;
          }
          else {
            local_28 = local_28 / *(int *)(iVar3 + 0x68);
          }
          local_30 = 0;
          if (iVar6 != 0) {
            local_14 = 0;
            do {
              pbVar12 = (byte *)(local_14 + *(int *)(iVar2 + 0x80));
              if (pbVar12[1] != (byte)(((uVar1 & 0x8000000) != 0) + 0x11U)) {
                iVar13 = (int)(char)pbVar12[3];
                iVar11 = iVar13 * 0x20;
                if ((iVar11 != 0) &&
                   (((*(uint *)(param_1 + 0xe8) & 0x200000) != 0 || (-1 < iVar11)))) {
                  iVar4 = (((*(short *)(pbVar12 + 6) * 0x1000 - iVar11 * iVar10) -
                           (char)pbVar12[4] * 0x20 * local_28) - (char)pbVar12[2] * 0x20 * local_2c)
                          / iVar11;
                  iVar5 = -iVar4;
                  if (iVar5 < -0x80) {
                    iVar8 = (*(int *)(iVar3 + 100) * (iVar10 + iVar4) >> 0xc) +
                            *(int *)(iVar3 + 0x34);
                    if (((0 < iVar11) && (iVar8 < param_4[6])) || (iVar8 < param_4[0xf])) {
                      local_34 = 0;
                      uVar7 = (uint)((*pbVar12 & 1) != 0);
                      iVar9 = uVar7 + 3;
                      if (uVar7 != 0xfffffffd) {
                        pbVar12 = pbVar12 + 10;
                        do {
                          if (((char)pbVar12[-1] * 0x20 * (iVar10 + iVar4) +
                               (char)pbVar12[-2] * 0x20 * local_2c +
                               (char)*pbVar12 * 0x20 * local_28 >> 0xc) -
                              (int)*(short *)(pbVar12 + 2) < -0x40 - (iVar13 * -0x20 + 0x1000 >> 6))
                          break;
                          local_34 = local_34 + 1;
                          pbVar12 = pbVar12 + 6;
                        } while (local_34 < iVar9);
                      }
                      if (local_34 == iVar9) {
                        if ((iVar11 < 1) || (param_4[6] <= iVar8)) {
                          param_4[0xc] = iVar3;
                          param_4[0xe] = local_30;
                          param_4[0xf] = iVar8;
                          param_4[0x10] = iVar5;
                        }
                        else {
                          param_4[6] = iVar8;
                          param_4[7] = iVar5;
                          param_4[10] = iVar3;
                          param_4[0xb] = local_30;
                        }
                      }
                    }
                  }
                  else if ((iVar5 < param_4[1]) && (0 < iVar11)) {
                    iVar11 = (*(int *)(iVar3 + 100) * (iVar10 + iVar4) >> 0xc) +
                             *(int *)(iVar3 + 0x34);
                    if (*param_4 < iVar11) {
                      local_34 = 0;
                      uVar7 = (uint)((*pbVar12 & 1) != 0);
                      iVar8 = uVar7 + 3;
                      if (uVar7 != 0xfffffffd) {
                        pbVar12 = pbVar12 + 10;
                        do {
                          if (((char)pbVar12[-1] * 0x20 * (iVar10 + iVar4) +
                               (char)pbVar12[-2] * 0x20 * local_2c +
                               (char)*pbVar12 * 0x20 * local_28 >> 0xc) -
                              (int)*(short *)(pbVar12 + 2) < -0x40 - (iVar13 * -0x20 + 0x1000 >> 6))
                          break;
                          local_34 = local_34 + 1;
                          pbVar12 = pbVar12 + 6;
                        } while (local_34 < iVar8);
                      }
                      if (local_34 == iVar8) {
                        *param_4 = iVar11;
                        param_4[1] = iVar5;
                        param_4[4] = iVar3;
                        param_4[5] = local_30;
                      }
                    }
                  }
                }
              }
              local_30 = local_30 + 1;
              local_14 = local_14 + 0x20;
            } while (local_30 < iVar6);
          }
        }
      }
    }
    iVar3 = *(int *)(iVar3 + 4);
  } while( true );
}

