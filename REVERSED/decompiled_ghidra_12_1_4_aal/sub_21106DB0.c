/* sub_21106DB0 @ 21106db0   2627 bytes */

undefined4 __thiscall sub_21106DB0(void *this,int param_1)

{
  int *piVar1;
  uint *puVar2;
  char cVar3;
  byte bVar4;
  ushort uVar5;
  int iVar6;
  LPVOID pvVar7;
  bool bVar8;
  void *pvVar9;
  uint *puVar10;
  byte *pbVar11;
  char *pcVar12;
  char *pcVar13;
  ushort *puVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  byte *pbVar18;
  uint *puVar19;
  uint *puVar20;
  ushort *this_00;
  byte *pbVar21;
  short sVar22;
  char *pcVar23;
  char *pcVar24;
  ushort *puVar25;
  char *pcVar26;
  bool bVar27;
  char *local_50;
  byte *local_4c;
  uint local_48;
  uint local_40;
  int local_38;
  ushort local_30 [24];
  
  iVar15 = *(int *)(param_1 + 4);
  iVar6 = *(int *)(param_1 + 8);
  puVar19 = (uint *)(param_1 + 0xc);
  if (iVar15 == 0) {
    return 1;
  }
  if (iVar6 == 0x45564157) {
    puVar2 = (uint *)(iVar15 + -8 + (int)puVar19);
    if ((*(int *)((int)this + 0x1c) == 0) && (*(int *)((int)this + 0x18) == 0)) {
      while (puVar19 < puVar2) {
        uVar16 = *puVar19;
        uVar17 = puVar19[1];
        puVar20 = puVar19 + 2;
        if ((int)uVar17 < 1) {
          return 1;
        }
        if (uVar16 < 0x20746d67) {
          if (uVar16 == 0x20746d66) {
            if (*(int *)((int)this + 0x18) != 0) {
              return 1;
            }
            if (uVar17 == 0x10) {
              puVar10 = operator_new(0x12);
              *(uint **)((int)this + 0x18) = puVar10;
              *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 1;
              *puVar10 = *puVar20;
              puVar10[1] = puVar19[3];
              puVar10[2] = puVar19[4];
              puVar10[3] = puVar19[5];
              *(undefined2 *)(*(int *)((int)this + 0x18) + 0x10) = 0;
            }
            else {
              if (uVar17 != 0x12) {
                return 1;
              }
              *(uint **)((int)this + 0x18) = puVar20;
            }
          }
          else if (uVar16 == 0x20657563) {
            puVar10 = puVar19 + 3;
            if ((*(int *)((int)this + 0x1c) == 0) && (uVar16 = *puVar20, 1 < uVar16)) {
              pvVar9 = operator_new(0x18);
              *(void **)((int)this + 0x1c) = pvVar9;
              *(uint *)((int)pvVar9 + 8) = puVar19[8];
              if (uVar16 != 1) {
                puVar10 = puVar10 + ((uVar16 - 2) * 3 + 3) * 2;
              }
              *(uint *)(*(int *)((int)this + 0x1c) + 0xc) = puVar10[5];
              pvVar7 = *(LPVOID *)((int)this + 0x1c);
              if (*(uint *)((int)pvVar7 + 8) < *(uint *)((int)pvVar7 + 0xc)) {
                *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 2;
                *(undefined4 *)((int)pvVar7 + 0x14) = 0;
              }
              else if (pvVar7 != (LPVOID)0x0) {
                sub_2110D4F4(pvVar7);
                *(undefined4 *)((int)this + 0x1c) = 0;
              }
            }
          }
          else if (uVar16 == 0x20736461) {
            *(uint **)((int)this + 0x24) = puVar20;
          }
        }
        else if (uVar16 == 0x61746164) {
          if (*(int *)((int)this + 0x34) != 0) {
            return 1;
          }
          *(uint **)((int)this + 0x34) = puVar20;
          *(uint *)((int)this + 0x2c) = uVar17;
        }
        else if (((uVar16 == 0x6c706d73) && (*(int *)((int)this + 0x1c) == 0)) && (puVar19[9] != 0))
        {
          puVar10 = operator_new(0x18);
          *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 2;
          *(uint **)((int)this + 0x1c) = puVar10;
          puVar19 = puVar19 + 0xb;
          for (iVar15 = 6; iVar15 != 0; iVar15 = iVar15 + -1) {
            *puVar10 = *puVar19;
            puVar19 = puVar19 + 1;
            puVar10 = puVar10 + 1;
          }
          *(undefined4 *)(*(int *)((int)this + 0x1c) + 0x14) = 0;
        }
        puVar19 = (uint *)((int)puVar20 + (uVar17 + 1 & 0xfffffffe));
      }
      iVar15 = *(int *)((int)this + 0x18);
      *(undefined4 *)((int)this + 0x30) = 1;
      if (iVar15 != 0) {
        uVar16 = *(uint *)((int)this + 0x2c);
        if (uVar16 < 0x300001) {
          *(uint *)((int)this + 0x28) = (uVar16 * 1000) / *(uint *)(iVar15 + 8);
          return 0;
        }
        *(uint *)((int)this + 0x28) = (uVar16 / *(uint *)(iVar15 + 8)) * 1000;
        return 0;
      }
    }
  }
  else if (iVar6 == 0x6b626673) {
    puVar2 = (uint *)(iVar15 + -8 + (int)puVar19);
    if (*(int *)((int)this + 0x20) != 0) {
      return 0;
    }
    pvVar9 = operator_new(0x265c);
    *(void **)((int)this + 0x20) = pvVar9;
    *(undefined4 *)((int)pvVar9 + 0x50) = 0;
    *(undefined4 *)(*(int *)((int)this + 0x20) + 0x58) = 0;
    *(undefined4 *)(*(int *)((int)this + 0x20) + 0x54) = 0;
    *(int *)((int)this + 0x2c) = iVar15 + 8;
    *(int *)((int)this + 0x34) = param_1;
    while (puVar19 < puVar2) {
      puVar20 = puVar19 + 1;
      if (*puVar19 != 0x5453494c) {
        return 1;
      }
      puVar19 = puVar19 + 3;
      puVar20 = (uint *)((*puVar20 - 4) + (int)puVar19);
      for (; puVar19 < puVar20; puVar19 = (uint *)((int)puVar19 + (uVar17 + 1 & 0xfffffffe))) {
        uVar16 = *puVar19;
        uVar17 = puVar19[1];
        puVar19 = puVar19 + 2;
        if (uVar16 < 0x6e65676a) {
          if (uVar16 == 0x6e656769) {
            *(uint **)(*(int *)((int)this + 0x20) + 0x40) = puVar19;
            *(uint *)(*(int *)((int)this + 0x20) + 0x44) = uVar17;
          }
          else if (uVar16 < 0x6761626a) {
            if (uVar16 == 0x67616269) {
              *(uint **)(*(int *)((int)this + 0x20) + 0x38) = puVar19;
              *(uint *)(*(int *)((int)this + 0x20) + 0x3c) = uVar17;
            }
            else if (uVar16 == 0x646f6d69) {
              *(uint **)(*(int *)((int)this + 0x20) + 0x48) = puVar19;
              *(uint *)(*(int *)((int)this + 0x20) + 0x4c) = uVar17;
            }
            else if (uVar16 == 0x646f6d70) {
              *(uint **)(*(int *)((int)this + 0x20) + 0x30) = puVar19;
              *(uint *)(*(int *)((int)this + 0x20) + 0x34) = uVar17;
            }
          }
          else if (uVar16 == 0x67616270) {
            *(uint **)(*(int *)((int)this + 0x20) + 0x20) = puVar19;
            *(uint *)(*(int *)((int)this + 0x20) + 0x24) = uVar17;
          }
          else if (uVar16 == 0x6c706d73) {
            **(undefined4 **)((int)this + 0x20) = puVar19;
            *(uint *)(*(int *)((int)this + 0x20) + 4) = uVar17;
          }
        }
        else if (uVar16 < 0x72646874) {
          if (uVar16 == 0x72646873) {
            *(uint **)(*(int *)((int)this + 0x20) + 8) = puVar19;
            *(uint *)(*(int *)((int)this + 0x20) + 0xc) = uVar17;
          }
          else if (uVar16 == 0x6e656770) {
            *(uint **)(*(int *)((int)this + 0x20) + 0x28) = puVar19;
            *(uint *)(*(int *)((int)this + 0x20) + 0x2c) = uVar17;
          }
          else if (uVar16 == 0x72646870) {
            *(uint **)(*(int *)((int)this + 0x20) + 0x10) = puVar19;
            *(uint *)(*(int *)((int)this + 0x20) + 0x14) = uVar17;
          }
        }
        else if (uVar16 == 0x74736e69) {
          *(uint **)(*(int *)((int)this + 0x20) + 0x18) = puVar19;
          *(uint *)(*(int *)((int)this + 0x20) + 0x1c) = uVar17;
        }
      }
    }
    *(undefined4 *)((int)this + 0x30) = 6;
    *(uint *)(*(int *)((int)this + 0x20) + 0x50) =
         *(uint *)(*(int *)((int)this + 0x20) + 0x14) / 0x26 - 1;
    local_50 = *(char **)(*(int *)((int)this + 0x20) + 0x10);
    pbVar11 = operator_new(0x36);
    pcVar12 = operator_new(0x18);
    pcVar13 = operator_new(0x1c);
    iVar15 = *(int *)((int)this + 0x20);
    local_40 = 0;
    pbVar21 = pbVar11;
    if (*(int *)(iVar15 + 0x50) != 0) {
      do {
        iVar15 = _strncmp(*(char **)(iVar15 + 0x10),&DAT_21114588,3);
        if (iVar15 == 0) break;
        puVar14 = operator_new(0x2e);
        this_00 = (ushort *)0x0;
        if (puVar14 != (ushort *)0x0) {
          puVar14[7] = 0;
          puVar14[6] = 0;
          puVar14[1] = 0;
          *puVar14 = 0;
          puVar14[10] = 0;
          puVar14[0xb] = 0;
          puVar14[5] = 0;
          puVar14[4] = 0;
          puVar14[3] = 0;
          puVar14[2] = 0;
          puVar14[0x16] = 0;
          puVar14[0x15] = 0;
          puVar14[0x14] = 0;
          puVar14[0x13] = 0;
          puVar14[0x12] = 0;
          puVar14[0x11] = 0;
          puVar14[0x10] = 0;
          puVar14[0xf] = 0;
          puVar14[0xe] = 0;
          puVar14[8] = 0x7f;
          puVar14[9] = 0x3c;
          puVar14[0xc] = 0x40;
          puVar14[0xd] = 0x7f;
          this_00 = puVar14;
        }
        uVar16 = 0xffffffff;
        pcVar23 = local_50;
        do {
          pcVar24 = pcVar23;
          if (uVar16 == 0) break;
          uVar16 = uVar16 - 1;
          pcVar24 = pcVar23 + 1;
          cVar3 = *pcVar23;
          pcVar23 = pcVar24;
        } while (cVar3 != '\0');
        uVar16 = ~uVar16;
        pcVar23 = pcVar24 + -uVar16;
        pcVar24 = pcVar13;
        for (uVar17 = uVar16 >> 2; uVar17 != 0; uVar17 = uVar17 - 1) {
          *(undefined4 *)pcVar24 = *(undefined4 *)pcVar23;
          pcVar23 = pcVar23 + 4;
          pcVar24 = pcVar24 + 4;
        }
        for (uVar16 = uVar16 & 3; uVar16 != 0; uVar16 = uVar16 - 1) {
          *pcVar24 = *pcVar23;
          pcVar23 = pcVar23 + 1;
          pcVar24 = pcVar24 + 1;
        }
        *(undefined2 *)(pcVar13 + 0x14) = *(undefined2 *)(local_50 + 0x14);
        *(undefined2 *)(pcVar13 + 0x16) = *(undefined2 *)(local_50 + 0x16);
        *(undefined2 *)(pcVar13 + 0x18) = *(undefined2 *)(local_50 + 0x18);
        *(undefined2 *)(pcVar13 + 0x1a) = *(undefined2 *)(local_50 + 0x3e);
        sub_21107800(this_00,(ushort *)
                             (*(int *)(*(int *)((int)this + 0x20) + 0x20) +
                             (uint)*(ushort *)(pcVar13 + 0x18) * 4),
                     *(int *)(*(int *)((int)this + 0x20) + 0x28));
        sVar22 = 0;
        uVar16 = 0xffffffff;
        pcVar23 = (char *)(*(int *)(*(int *)((int)this + 0x20) + 0x18) + (uint)*this_00 * 0x16);
        pcVar24 = pcVar23;
        do {
          pcVar26 = pcVar24;
          if (uVar16 == 0) break;
          uVar16 = uVar16 - 1;
          pcVar26 = pcVar24 + 1;
          cVar3 = *pcVar24;
          pcVar24 = pcVar26;
        } while (cVar3 != '\0');
        uVar16 = ~uVar16;
        pcVar24 = pcVar26 + -uVar16;
        pcVar26 = pcVar12;
        for (uVar17 = uVar16 >> 2; uVar17 != 0; uVar17 = uVar17 - 1) {
          *(undefined4 *)pcVar26 = *(undefined4 *)pcVar24;
          pcVar24 = pcVar24 + 4;
          pcVar26 = pcVar26 + 4;
        }
        for (uVar16 = uVar16 & 3; uVar16 != 0; uVar16 = uVar16 - 1) {
          *pcVar26 = *pcVar24;
          pcVar24 = pcVar24 + 1;
          pcVar26 = pcVar26 + 1;
        }
        *(undefined2 *)(pcVar12 + 0x14) = *(undefined2 *)(pcVar23 + 0x14);
        uVar5 = *(ushort *)(pcVar23 + 0x2a);
        *(ushort *)(pcVar12 + 0x16) = uVar5;
        puVar14 = this_00;
        puVar25 = local_30;
        for (iVar15 = 0xb; iVar15 != 0; iVar15 = iVar15 + -1) {
          *(undefined4 *)puVar25 = *(undefined4 *)puVar14;
          puVar14 = puVar14 + 2;
          puVar25 = puVar25 + 2;
        }
        local_48 = (uint)*(ushort *)(pcVar12 + 0x14);
        *puVar25 = *puVar14;
        if (local_48 < uVar5) {
          do {
            puVar14 = local_30;
            puVar25 = this_00;
            for (iVar15 = 0xb; iVar15 != 0; iVar15 = iVar15 + -1) {
              *(undefined4 *)puVar25 = *(undefined4 *)puVar14;
              puVar14 = puVar14 + 2;
              puVar25 = puVar25 + 2;
            }
            *puVar25 = *puVar14;
            sub_21107800(this_00,(ushort *)
                                 (*(int *)(*(int *)((int)this + 0x20) + 0x38) + local_48 * 4),
                         *(int *)(*(int *)((int)this + 0x20) + 0x40));
            bVar8 = false;
            pcVar23 = (char *)(*(int *)(*(int *)((int)this + 0x20) + 8) + (uint)this_00[1] * 0x2e);
            uVar16 = 0xffffffff;
            pcVar24 = pcVar23;
            do {
              pcVar26 = pcVar24;
              if (uVar16 == 0) break;
              uVar16 = uVar16 - 1;
              pcVar26 = pcVar24 + 1;
              cVar3 = *pcVar24;
              pcVar24 = pcVar26;
            } while (cVar3 != '\0');
            uVar16 = ~uVar16;
            pbVar21 = (byte *)(pcVar26 + -uVar16);
            pbVar18 = pbVar11;
            for (uVar17 = uVar16 >> 2; uVar17 != 0; uVar17 = uVar17 - 1) {
              *(undefined4 *)pbVar18 = *(undefined4 *)pbVar21;
              pbVar21 = pbVar21 + 4;
              pbVar18 = pbVar18 + 4;
            }
            for (uVar16 = uVar16 & 3; uVar16 != 0; uVar16 = uVar16 - 1) {
              *pbVar18 = *pbVar21;
              pbVar21 = pbVar21 + 1;
              pbVar18 = pbVar18 + 1;
            }
            *(undefined4 *)(pbVar11 + 0x14) = *(undefined4 *)(pcVar23 + 0x14);
            *(undefined4 *)(pbVar11 + 0x18) = *(undefined4 *)(pcVar23 + 0x18);
            *(undefined4 *)(pbVar11 + 0x1c) = *(undefined4 *)(pcVar23 + 0x1c);
            *(undefined4 *)(pbVar11 + 0x20) = *(undefined4 *)(pcVar23 + 0x20);
            *(undefined4 *)(pbVar11 + 0x24) = *(undefined4 *)(pcVar23 + 0x24);
            pbVar11[0x28] = pcVar23[0x28];
            pbVar11[0x29] = pcVar23[0x29];
            *(undefined2 *)(pbVar11 + 0x2a) = *(undefined2 *)(pcVar23 + 0x2a);
            *(undefined2 *)(pbVar11 + 0x2c) = *(undefined2 *)(pcVar23 + 0x2c);
            *(int *)(pbVar11 + 0x2e) = *(int *)(pbVar11 + 0x18) - *(int *)(pbVar11 + 0x14);
            local_38 = *(int *)(*(int *)((int)this + 0x20) + 0x58);
            if (local_38 == 0) {
LAB_2110746a:
              piVar1 = (int *)(*(int *)((int)this + 0x20) + 0x54);
              *piVar1 = *piVar1 + 1;
            }
            else {
              pbVar18 = (byte *)(*(int *)((int)this + 0x20) + 0x70);
              pbVar21 = pbVar11;
              local_4c = pbVar18;
LAB_21107411:
              do {
                bVar4 = *pbVar21;
                bVar27 = bVar4 < *pbVar18;
                if (bVar4 == *pbVar18) {
                  if (bVar4 != 0) {
                    bVar4 = pbVar21[1];
                    bVar27 = bVar4 < pbVar18[1];
                    if (bVar4 != pbVar18[1]) goto LAB_21107435;
                    pbVar18 = pbVar18 + 2;
                    pbVar21 = pbVar21 + 2;
                    if (bVar4 != 0) goto LAB_21107411;
                  }
                  iVar15 = 0;
                }
                else {
LAB_21107435:
                  iVar15 = (1 - (uint)bVar27) - (uint)(bVar27 != 0);
                }
                if (iVar15 == 0) {
                  bVar8 = true;
                }
                pbVar18 = local_4c + 0x4c;
                local_38 = local_38 + -1;
                pbVar21 = pbVar11;
                local_4c = pbVar18;
              } while (local_38 != 0);
              if (!bVar8) goto LAB_2110746a;
            }
            uVar16 = 0xffffffff;
            pbVar21 = pbVar11;
            do {
              pbVar18 = pbVar21;
              if (uVar16 == 0) break;
              uVar16 = uVar16 - 1;
              pbVar18 = pbVar21 + 1;
              bVar4 = *pbVar21;
              pbVar21 = pbVar18;
            } while (bVar4 != 0);
            uVar16 = ~uVar16;
            pbVar21 = pbVar18 + -uVar16;
            pbVar18 = (byte *)(*(int *)((int)this + 0x20) + 0x70 +
                              *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c);
            for (uVar17 = uVar16 >> 2; uVar17 != 0; uVar17 = uVar17 - 1) {
              *(undefined4 *)pbVar18 = *(undefined4 *)pbVar21;
              pbVar21 = pbVar21 + 4;
              pbVar18 = pbVar18 + 4;
            }
            for (uVar16 = uVar16 & 3; uVar16 != 0; uVar16 = uVar16 - 1) {
              *pbVar18 = *pbVar21;
              pbVar21 = pbVar21 + 1;
              pbVar18 = pbVar18 + 1;
            }
            *(short *)(*(int *)((int)this + 0x20) + 0x84 +
                      *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c) = sVar22;
            *(undefined2 *)
             (*(int *)((int)this + 0x20) + 0x86 + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = (undefined2)local_40;
            *(undefined2 *)
             (*(int *)((int)this + 0x20) + 0x88 + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = *(undefined2 *)(pcVar13 + 0x14);
            *(undefined2 *)
             (*(int *)((int)this + 0x20) + 0x8a + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = *(undefined2 *)(pcVar13 + 0x16);
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0x8c + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = *this_00;
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0x8e + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[1];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0x90 + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[7];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0x92 + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[8];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0x94 + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[9];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0x96 + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[6];
            *(ushort *)
             (*(int *)((int)this + 0x20) + (*(int *)(*(int *)((int)this + 0x20) + 0x58) + 2) * 0x4c)
                 = this_00[0xe];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0x9a + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[0xd];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0x9c + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[0x10];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0x9e + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[0x11];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0xa0 + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[0x12];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0xa2 + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[0x13];
            *(ushort *)
             (*(int *)((int)this + 0x20) + 0xa4 + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = this_00[0x14];
            *(undefined4 *)
             (*(int *)((int)this + 0x20) + 0x5c + *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c
             ) = *(undefined4 *)(pbVar11 + 0x24);
            *(int *)(*(int *)((int)this + 0x20) + 0x60 +
                    *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c) =
                 ((short)this_00[2] * 0x7fffffff + (int)(short)this_00[3] + *(int *)(pbVar11 + 0x2e)
                 ) * 2;
            piVar1 = *(int **)((int)this + 0x20);
            piVar1[piVar1[0x16] * 0x13 + 0x19] =
                 *piVar1 + ((int)(short)this_00[2] + *(int *)(pbVar11 + 0x14)) * 2;
            *(int *)(*(int *)((int)this + 0x20) + 0x68 +
                    *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c) =
                 ((int)(short)this_00[4] + *(int *)(pbVar11 + 0x14) * 0x7fffffff +
                 *(int *)(pbVar11 + 0x1c)) * 2;
            *(int *)(*(int *)((int)this + 0x20) + 0x6c +
                    *(int *)(*(int *)((int)this + 0x20) + 0x58) * 0x4c) =
                 ((int)(short)this_00[5] + *(int *)(pbVar11 + 0x14) * 0x7fffffff +
                 *(int *)(pbVar11 + 0x20)) * 2;
            *(int *)(*(int *)((int)this + 0x20) + 0x58) =
                 *(int *)(*(int *)((int)this + 0x20) + 0x58) + 1;
            local_48 = local_48 + 1;
            sVar22 = sVar22 + 1;
          } while ((int)local_48 < (int)(uint)*(ushort *)(pcVar12 + 0x16));
        }
        if (this_00 != (ushort *)0x0) {
          sub_2110D4F4(this_00);
        }
        pbVar21 = (byte *)0x0;
        iVar15 = *(int *)((int)this + 0x20);
        local_50 = local_50 + 0x26;
        local_40 = local_40 + 1;
      } while (local_40 < *(uint *)(iVar15 + 0x50));
    }
    if (pbVar21 != (byte *)0x0) {
      sub_2110D4F4(pbVar21);
    }
    if (pbVar11 != (byte *)0x0) {
      sub_2110D4F4(pbVar11);
    }
    if (pcVar12 != (char *)0x0) {
      sub_2110D4F4(pcVar12);
    }
    if (pcVar13 != (char *)0x0) {
      sub_2110D4F4(pcVar13);
      return 0;
    }
  }
  else {
    if (iVar6 == 0x20534c44) {
      *(int *)((int)this + 0x34) = param_1;
      *(int *)((int)this + 0x2c) = iVar15 + 8;
      *(undefined4 *)((int)this + 0x30) = 0xd;
      return 0;
    }
    if (iVar6 != 0x47534d44) {
      OutputDebugStringA(s_Riff_Type_not_supported_2111456c);
      return 1;
    }
    *(undefined4 *)((int)this + 0x30) = 0xe;
    *(int *)((int)this + 0x34) = param_1;
    *(int *)((int)this + 0x2c) = iVar15 + 8;
  }
  return 0;
}

