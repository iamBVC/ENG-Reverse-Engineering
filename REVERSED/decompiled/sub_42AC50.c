/* sub_42AC50 @ 0042ac50   4815 bytes */

void sub_42AC50(uint *param_1,undefined4 param_2)

{
  uint *puVar1;
  int iVar2;
  ushort uVar3;
  undefined4 *puVar4;
  uint *puVar5;
  undefined1 uVar6;
  byte bVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  uint *puVar12;
  uint uVar13;
  int *piVar14;
  int *piVar15;
  byte *pbVar16;
  undefined4 *puVar17;
  int iVar18;
  uint uVar19;
  undefined1 *puVar20;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint *local_14;
  int local_10;
  uint *local_c;
  uint *local_8;
  undefined1 local_4 [4];
  
  puVar5 = param_1;
  sub_415AB0(param_2,param_1);
  puVar12 = param_1 + 5;
  sub_415AB0(param_2,puVar12);
  puVar1 = param_1 + 6;
  sub_415AB0(param_2,puVar1);
  param_1[4] = *puVar1 * *puVar12;
  local_8 = operator_new(*param_1 << 2);
  uVar8 = sub_41EF00(*puVar1 * *puVar12 * 4);
  param_1[0x10] = uVar8;
  uVar8 = sub_41EF00(*param_1 << 3);
  param_1[0x11] = uVar8;
  uVar8 = 0;
  if (*puVar1 * *puVar12 != 0) {
    do {
      uVar8 = uVar8 + 1;
      *(undefined4 *)((param_1[0x10] - 4) + uVar8 * 4) = 0;
    } while (uVar8 < *puVar1 * *puVar12);
  }
  uVar8 = *param_1;
  param_1 = (uint *)0x0;
  if (uVar8 != 0) {
    local_14 = local_8;
    do {
      local_c = (uint *)0x0;
      sub_415AB0(param_2,&local_1c);
      sub_415AB0(param_2,&local_20);
      sub_415AB0(param_2,&local_18);
      sub_415AB0(param_2,&local_24);
      sub_415AB0(param_2,local_4);
      sub_415AB0(param_2,&local_c);
      uVar8 = puVar5[0x11];
      *(uint **)(uVar8 + (int)param_1 * 8) = param_1;
      *(undefined4 *)(uVar8 + 4 + (int)param_1 * 8) = 0;
      iVar18 = uVar8 + (int)param_1 * 8;
      iVar9 = __ftol();
      uVar8 = puVar5[5];
      iVar10 = __ftol();
      iVar10 = iVar10 - iVar9 * uVar8;
      *(undefined4 *)(iVar18 + 4) = *(undefined4 *)(puVar5[0x10] + iVar10 * 4);
      *(int *)(puVar5[0x10] + iVar10 * 4) = iVar18;
      if (local_c != (uint *)0x0) {
        *local_14 = (uint)param_1;
        local_14 = local_14 + 1;
      }
      param_1 = (uint *)((int)param_1 + 1);
    } while (param_1 < *puVar5);
  }
  sub_415AB0(param_2,&local_10);
  uVar8 = sub_41EF00(local_10 * 4);
  puVar5[0xc] = uVar8;
  iVar18 = 0;
  if (0 < local_10) {
    do {
      sub_415AB0(param_2,puVar5[0xc] + iVar18 * 4);
      iVar18 = iVar18 + 1;
    } while (iVar18 < local_10);
  }
  puVar12 = puVar5 + 7;
  sub_415AB0(param_2,puVar12);
  uVar8 = sub_41EF00(*puVar12 * 0x5c);
  puVar5[9] = uVar8;
  iVar18 = 0;
  param_1 = (uint *)0x0;
  if (0 < (int)*puVar12) {
    do {
      sub_415AB0(param_2,puVar5[9] + iVar18);
      sub_415AB0(param_2,puVar5[9] + 4 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 8 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0xc + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x10 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x14 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x18 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x1c + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x20 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x24 + iVar18);
      sub_415AB0(param_2,&local_c);
      if (local_c == (uint *)0x0) {
        *(undefined4 *)(puVar5[9] + 0x28 + iVar18) = 0;
      }
      else {
        *(int *)(puVar5[9] + 0x28 + iVar18) = DAT_006d9dbc + (int)local_c;
      }
      sub_415AB0(param_2,puVar5[9] + 0x2c + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x30 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x34 + iVar18);
      sub_415AF0(param_2,puVar5[9] + 0x38 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x3c + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x40 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x44 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x48 + iVar18);
      uVar8 = puVar5[9];
      iVar9 = *(int *)(uVar8 + 0x3c + iVar18);
      if (*(int *)(uVar8 + 0x44 + iVar18) <= iVar9) {
        *(int *)(uVar8 + iVar18 + 0x44) = (iVar9 >> 1) + iVar9;
        iVar9 = *(int *)(puVar5[9] + iVar18 + 0x40);
        *(int *)(puVar5[9] + iVar18 + 0x48) = (iVar9 >> 1) + iVar9;
      }
      sub_415AB0(param_2,puVar5[9] + 0x4c + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x50 + iVar18);
      sub_415AF0(param_2,puVar5[9] + 0x54 + iVar18);
      sub_415AF0(param_2,puVar5[9] + 0x56 + iVar18);
      sub_415AB0(param_2,puVar5[9] + 0x58 + iVar18);
      if ((*(byte *)(puVar5[9] + 0x20 + iVar18) & 8) != 0) {
        DAT_00584644 = puVar5[9] + iVar18;
      }
      param_1 = (uint *)((int)param_1 + 1);
      iVar18 = iVar18 + 0x5c;
    } while ((int)param_1 < (int)*puVar12);
  }
  puVar12 = puVar5 + 10;
  sub_415AB0(param_2,puVar12);
  uVar8 = sub_41EF00(*puVar12 * 0x30);
  puVar5[0xb] = uVar8;
  param_1 = (uint *)0x0;
  if (*puVar12 != 0) {
    iVar18 = 0;
    do {
      sub_415AB0(param_2,iVar18 + puVar5[0xb]);
      sub_415AB0(param_2,iVar18 + 4 + puVar5[0xb]);
      sub_415AF0(param_2,&local_14);
      *(uint *)(iVar18 + 8 + puVar5[0xb]) = (uint)local_14 & 0xffff;
      sub_415AF0(param_2,&local_14);
      *(uint *)(iVar18 + 0xc + puVar5[0xb]) = (uint)local_14 & 0xffff;
      sub_415AF0(param_2,&local_14);
      *(uint *)(iVar18 + 0x10 + puVar5[0xb]) = (uint)local_14 & 0xffff;
      sub_415AB0(param_2,iVar18 + 0x18 + puVar5[0xb]);
      sub_415AB0(param_2,iVar18 + 0x1c + puVar5[0xb]);
      sub_415AB0(param_2,iVar18 + 0x20 + puVar5[0xb]);
      sub_415AB0(param_2,iVar18 + 0x28 + puVar5[0xb]);
      sub_415AB0(param_2,iVar18 + 0x2c + puVar5[0xb]);
      param_1 = (uint *)((int)param_1 + 1);
      iVar18 = iVar18 + 0x30;
    } while (param_1 < *puVar12);
  }
  piVar14 = (int *)puVar5[0xb];
  piVar15 = (int *)0x0;
  uVar8 = 0;
  if (*puVar12 != 0) {
    do {
      if (piVar15 != (int *)0x0) {
        piVar14[1] = (int)piVar15;
      }
      if (*piVar14 == 0) {
        piVar15 = (int *)0x0;
      }
      else {
        *piVar14 = (int)(piVar14 + 0xc);
        piVar15 = piVar14;
      }
      uVar8 = uVar8 + 1;
      piVar14 = piVar14 + 0xc;
    } while (uVar8 < *puVar12);
  }
  DAT_006da350 = sub_41EF00(0x100);
  iVar18 = 0;
  do {
    sub_415AB0(param_2,iVar18 + DAT_006da350);
    sub_415AB0(param_2,iVar18 + 4 + DAT_006da350);
    iVar18 = iVar18 + 8;
  } while (iVar18 < 0x100);
  DAT_00586424 = 0xffff0000;
  uVar8 = sub_41EF00(puVar5[6] * puVar5[5] * 4);
  puVar5[0x12] = uVar8;
  uVar8 = 0;
  if (puVar5[6] != 0) {
    do {
      uVar13 = puVar5[5];
      uVar19 = 0;
      if (uVar13 != 0) {
        do {
          sub_415AB0(param_2,puVar5[0x12] + (uVar13 * uVar8 + uVar19) * 4);
          uVar13 = puVar5[5];
          uVar19 = uVar19 + 1;
        } while (uVar19 < uVar13);
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < puVar5[6]);
  }
  uVar8 = sub_41EF00(*puVar5 << 5);
  puVar5[0xf] = uVar8;
  uVar8 = 0;
  if (*puVar5 != 0) {
    iVar18 = 0;
    do {
      sub_415AB0(param_2,iVar18 + puVar5[0xf]);
      sub_415AB0(param_2,iVar18 + 4 + puVar5[0xf]);
      sub_415AB0(param_2,iVar18 + 8 + puVar5[0xf]);
      sub_415AB0(param_2,iVar18 + 0x10 + puVar5[0xf]);
      sub_415AB0(param_2,iVar18 + 0x14 + puVar5[0xf]);
      sub_415AB0(param_2,iVar18 + 0x18 + puVar5[0xf]);
      uVar8 = uVar8 + 1;
      iVar18 = iVar18 + 0x20;
    } while (uVar8 < *puVar5);
  }
  uVar8 = sub_41EF00(*puVar5 << 2);
  puVar5[0x13] = uVar8;
  uVar8 = 0;
  if (*puVar5 != 0) {
    do {
      sub_415AB0(param_2,puVar5[0x13] + uVar8 * 4);
      uVar8 = uVar8 + 1;
    } while (uVar8 < *puVar5);
  }
  if ((DAT_006da330 & 0x10000) != 0) {
    puVar12 = puVar5 + 8;
    sub_415AB0(param_2,puVar12);
    uVar8 = sub_41EF00(*puVar12 * 0x18);
    puVar5[0x14] = uVar8;
    param_1 = (uint *)0x0;
    if (*puVar12 != 0) {
      local_c = local_8;
      iVar18 = 0;
      do {
        sub_415AB0(param_2,iVar18 + puVar5[0x14]);
        sub_415AB0(param_2,iVar18 + 4 + puVar5[0x14]);
        sub_415AB0(param_2,iVar18 + 8 + puVar5[0x14]);
        sub_415AB0(param_2,iVar18 + 0xc + puVar5[0x14]);
        sub_415AB0(param_2,iVar18 + 0x10 + puVar5[0x14]);
        uVar8 = *local_c;
        local_c = local_c + 1;
        *(uint *)(iVar18 + 0x14 + puVar5[0x14]) = puVar5[0x13] + uVar8 * 4;
        param_1 = (uint *)((int)param_1 + 1);
        iVar18 = iVar18 + 0x18;
      } while (param_1 < *puVar12);
    }
  }
  if ((DAT_006da330 & 0x10000000) == 0) {
    iVar18 = *puVar5 << 2;
  }
  else {
    iVar18 = *puVar5 << 3;
  }
  uVar8 = sub_41EF00(iVar18);
  puVar5[0x16] = uVar8;
  local_c = (uint *)0x0;
  param_1 = (uint *)0x0;
  if (*puVar5 != 0) {
    iVar9 = 0;
    iVar18 = DAT_005846ec;
    do {
      local_20 = 0;
      uVar11 = sub_41EF00((uint)*(ushort *)(iVar18 + 0x6c + *(int *)(puVar5[0x13] + iVar9) * 0x84)
                          << 2);
      local_1c = 0;
      *(undefined4 *)(puVar5[0x16] + iVar9) = uVar11;
      uVar8 = 0;
      if (*(short *)(DAT_005846ec + 0x6c + *(int *)(puVar5[0x13] + iVar9) * 0x84) != 0) {
        do {
          iVar18 = local_1c * 4;
          sub_415AB0(param_2,*(int *)(puVar5[0x16] + iVar9) + iVar18);
          piVar14 = (int *)(puVar5[0x16] + iVar9);
          if ((int)local_20 < (int)(uint)*(byte *)(iVar18 + 3 + *(int *)(puVar5[0x16] + iVar9))) {
            local_20 = (uint)*(byte *)(iVar18 + 3 + *piVar14);
          }
          if (DAT_006d7c61 == '\0') {
            puVar20 = (undefined1 *)(iVar18 + *piVar14);
            local_14 = (uint *)(uint)(byte)puVar20[1];
            uVar6 = __ftol();
            *puVar20 = uVar6;
            puVar20[1] = uVar6;
            puVar20[2] = uVar6;
          }
          iVar10 = 0;
          do {
            pbVar16 = (byte *)(*(int *)(puVar5[0x16] + iVar9) + iVar18 + iVar10);
            uVar8 = (uint)*pbVar16 * 2;
            if (0xff < uVar8) {
              uVar8 = 0xff;
            }
            iVar10 = iVar10 + 1;
            *pbVar16 = (byte)uVar8;
          } while (iVar10 < 3);
          local_1c = local_1c + 1;
          uVar8 = local_20;
        } while ((int)local_1c <
                 (int)(uint)*(ushort *)(DAT_005846ec + 0x6c + *(int *)(puVar5[0x13] + iVar9) * 0x84)
                );
      }
      puVar12 = (uint *)(puVar5[0x13] + iVar9);
      local_18 = (uint)*(ushort *)(DAT_005846ec + 0x6c + *(int *)(puVar5[0x13] + iVar9) * 0x84);
      iVar18 = DAT_005846ec;
      if (1 < (int)uVar8) {
        sub_41EF00((uVar8 - 1) * local_18 * 4);
        local_24 = 1;
        *(char *)(*(int *)(puVar5[0x16] + iVar9) + 3) = (char)uVar8;
        iVar18 = DAT_005846ec;
        if (1 < (int)uVar8) {
          do {
            iVar10 = 0;
            uVar8 = (uint)*(ushort *)(iVar18 + 0x6c + *(int *)(puVar5[0x13] + iVar9) * 0x84);
            if (uVar8 != 0) {
              do {
                sub_415AB0(param_2,*(int *)(puVar5[0x16] + iVar9) + (local_24 * uVar8 + iVar10) * 4)
                ;
                if (DAT_006d7c61 == '\0') {
                  pbVar16 = (byte *)(*(int *)(puVar5[0x16] + iVar9) +
                                    (*(ushort *)
                                      (DAT_005846ec + 0x6c + *(int *)(puVar5[0x13] + iVar9) * 0x84)
                                     * local_24 + iVar10) * 4);
                  local_14 = (uint *)(uint)*pbVar16;
                  bVar7 = __ftol();
                  *pbVar16 = bVar7;
                  pbVar16[1] = bVar7;
                  pbVar16[2] = bVar7;
                }
                iVar18 = 0;
                do {
                  iVar2 = *(int *)(puVar5[0x16] + iVar9) +
                          (*(ushort *)(DAT_005846ec + 0x6c + *(int *)(puVar5[0x13] + iVar9) * 0x84)
                           * local_24 + iVar10) * 4;
                  puVar20 = (undefined1 *)(iVar2 + iVar18);
                  uVar8 = (uint)*(byte *)(iVar2 + iVar18) * 2;
                  if (0xff < uVar8) {
                    uVar8 = 0xff;
                  }
                  iVar18 = iVar18 + 1;
                  *puVar20 = (char)uVar8;
                } while (iVar18 < 3);
                iVar10 = iVar10 + 1;
                uVar8 = (uint)*(ushort *)
                               (DAT_005846ec + 0x6c + *(int *)(puVar5[0x13] + iVar9) * 0x84);
                iVar18 = DAT_005846ec;
              } while (iVar10 < (int)uVar8);
            }
            local_24 = local_24 + 1;
            uVar8 = local_20;
          } while ((int)local_24 < (int)local_20);
        }
        puVar12 = (uint *)(puVar5[0x13] + iVar9);
        local_18 = *(ushort *)(iVar18 + 0x6c + *puVar12 * 0x84) * local_24;
        local_14 = puVar12;
      }
      uVar13 = 0;
      if (puVar5[8] != 0) {
        puVar17 = (undefined4 *)(puVar5[0x14] + 0x14);
        do {
          if ((uint *)*puVar17 == puVar12) break;
          uVar13 = uVar13 + 1;
          puVar17 = puVar17 + 6;
        } while (uVar13 < puVar5[8]);
      }
      if (uVar13 != puVar5[8]) {
        if ((DAT_006da330 & 0x10000000) != 0) {
          *(uint *)(puVar5[0x16] + (*puVar5 + (int)local_c) * 4) =
               *(int *)(puVar5[0x16] + iVar9) + local_18 * 4;
          iVar18 = DAT_005846ec;
        }
        local_c = (uint *)((int)local_c + 1);
        puVar12 = (uint *)(uVar13 * 0x18);
        local_14 = puVar12;
        sub_41EF00((uint)*(ushort *)
                          (iVar18 + 0x6c + *(int *)(puVar5[0x14] + 0x10 + (int)puVar12) * 0x84) << 2
                  );
        local_1c = 0;
        if (*(short *)(DAT_005846ec + 0x6c + *(int *)(puVar5[0x14] + 0x10 + (int)puVar12) * 0x84) !=
            0) {
          iVar18 = local_18 * 4;
          do {
            sub_415AB0(param_2,*(int *)(puVar5[0x16] + iVar9) + iVar18);
            piVar14 = (int *)(puVar5[0x16] + iVar9);
            if ((int)local_20 < (int)(uint)*(byte *)(iVar18 + 3 + *(int *)(puVar5[0x16] + iVar9))) {
              local_20 = (uint)*(byte *)(iVar18 + 3 + *piVar14);
            }
            if (DAT_006d7c61 == '\0') {
              puVar20 = (undefined1 *)(iVar18 + *piVar14);
              local_24 = (uint)(byte)puVar20[2];
              uVar6 = __ftol();
              *puVar20 = uVar6;
              puVar20[1] = uVar6;
              puVar20[2] = uVar6;
            }
            iVar10 = 0;
            do {
              pbVar16 = (byte *)(*(int *)(puVar5[0x16] + iVar9) + iVar10 + iVar18);
              uVar8 = (uint)*pbVar16 * 2;
              if (0xff < uVar8) {
                uVar8 = 0xff;
              }
              iVar10 = iVar10 + 1;
              *pbVar16 = (byte)uVar8;
            } while (iVar10 < 3);
            iVar18 = iVar18 + 4;
            local_1c = local_1c + 1;
            uVar8 = local_20;
          } while ((int)local_1c <
                   (int)(uint)*(ushort *)
                               (DAT_005846ec + 0x6c +
                               *(int *)(puVar5[0x14] + 0x10 + (int)local_14) * 0x84));
        }
        iVar18 = DAT_005846ec;
        if (1 < (int)uVar8) {
          sub_41EF00((uint)*(ushort *)
                            (DAT_005846ec + 0x6c +
                            *(int *)(puVar5[0x14] + 0x10 + (int)local_14) * 0x84) * (uVar8 - 1) * 4)
          ;
          local_24 = 1;
          *(char *)(*(int *)(puVar5[0x16] + iVar9) + 3 + local_18 * 4) = (char)uVar8;
          iVar18 = DAT_005846ec;
          if (1 < (int)uVar8) {
            do {
              iVar10 = 0;
              uVar8 = (uint)*(ushort *)
                             (iVar18 + 0x6c + *(int *)(puVar5[0x14] + 0x10 + (int)local_14) * 0x84);
              if (uVar8 != 0) {
                do {
                  sub_415AB0(param_2,*(int *)(puVar5[0x16] + iVar9) +
                                     (local_24 * uVar8 + iVar10 + local_18) * 4);
                  if (DAT_006d7c61 == '\0') {
                    puVar20 = (undefined1 *)
                              (*(int *)(puVar5[0x16] + iVar9) +
                              (*(ushort *)
                                (DAT_005846ec + 0x6c +
                                *(int *)(puVar5[0x14] + 0x10 + (int)local_14) * 0x84) * local_24 +
                               iVar10 + local_18) * 4);
                    local_1c = (uint)(byte)puVar20[1];
                    uVar6 = __ftol();
                    *puVar20 = uVar6;
                    puVar20[1] = uVar6;
                    puVar20[2] = uVar6;
                  }
                  iVar18 = 0;
                  do {
                    iVar2 = *(int *)(puVar5[0x16] + iVar9) +
                            (*(ushort *)
                              (DAT_005846ec + 0x6c +
                              *(int *)(puVar5[0x14] + 0x10 + (int)local_14) * 0x84) * local_24 +
                             iVar10 + local_18) * 4;
                    puVar20 = (undefined1 *)(iVar2 + iVar18);
                    uVar8 = (uint)*(byte *)(iVar2 + iVar18) * 2;
                    if (0xff < uVar8) {
                      uVar8 = 0xff;
                    }
                    iVar18 = iVar18 + 1;
                    *puVar20 = (char)uVar8;
                  } while (iVar18 < 3);
                  iVar10 = iVar10 + 1;
                  uVar8 = (uint)*(ushort *)
                                 (DAT_005846ec + 0x6c +
                                 *(int *)(puVar5[0x14] + 0x10 + (int)local_14) * 0x84);
                  iVar18 = DAT_005846ec;
                } while (iVar10 < (int)uVar8);
              }
              local_24 = local_24 + 1;
            } while ((int)local_24 < (int)local_20);
          }
        }
      }
      param_1 = (uint *)((int)param_1 + 1);
      iVar9 = iVar9 + 4;
    } while (param_1 < *puVar5);
  }
  puVar12 = puVar5 + 1;
  sub_415AB0(param_2,puVar12);
  sub_415AB0(param_2,puVar5 + 2);
  uVar8 = sub_41EF00(*puVar12 * 0x48);
  puVar5[0xe] = uVar8;
  param_1 = (uint *)0x0;
  if (*puVar12 != 0) {
    iVar18 = 0;
    do {
      sub_415AF0(param_2,&local_14);
      *(uint *)(puVar5[0xe] + iVar18) = (uint)local_14 & 0xffff;
      sub_415AF0(param_2,&local_14);
      *(uint *)(puVar5[0xe] + 4 + iVar18) = (uint)local_14 & 0xffff;
      sub_415AF0(param_2,&local_14);
      *(uint *)(puVar5[0xe] + 8 + iVar18) = (uint)local_14 & 0xffff;
      sub_415AB0(param_2,puVar5[0xe] + 0x10 + iVar18);
      sub_415AB0(param_2,puVar5[0xe] + 0x14 + iVar18);
      sub_415AB0(param_2,puVar5[0xe] + 0x18 + iVar18);
      sub_415AB0(param_2,&local_18);
      *(uint *)(puVar5[0xe] + 0x20 + iVar18) = local_18 + DAT_006d9dbc;
      sub_415AB0(param_2,puVar5[0xe] + 0x24 + iVar18);
      sub_415AB0(param_2,&local_18);
      if (local_18 == 0xffffffff) {
        *(undefined4 *)(puVar5[0xe] + 0x28 + iVar18) = 0;
      }
      else {
        *(uint *)(puVar5[0xe] + 0x28 + iVar18) = puVar5[0xc] + local_18 * 4;
      }
      sub_415AB0(param_2,puVar5[0xe] + 0x2c + iVar18);
      sub_415AB0(param_2,puVar5[0xe] + 0x30 + iVar18);
      sub_415AB0(param_2,puVar5[0xe] + 0x34 + iVar18);
      sub_415AB0(param_2,puVar5[0xe] + 0x38 + iVar18);
      sub_415AB0(param_2,&local_18);
      if (local_18 == 0xffffffff) {
        *(undefined4 *)(puVar5[0xe] + 0x3c + iVar18) = 0;
      }
      else {
        *(uint *)(puVar5[0xe] + 0x3c + iVar18) = local_18 * 0x30 + puVar5[0xb];
      }
      sub_415AB0(param_2,puVar5[0xe] + 0x40 + iVar18);
      sub_415AF0(param_2,puVar5[0xe] + 0x44 + iVar18);
      sub_415AF0(param_2,puVar5[0xe] + 0x46 + iVar18);
      param_1 = (uint *)((int)param_1 + 1);
      iVar18 = iVar18 + 0x48;
    } while (param_1 < *puVar12);
  }
  param_1 = (uint *)0x0;
  if (*puVar12 != 0) {
    iVar18 = 0;
    do {
      puVar17 = *(undefined4 **)(puVar5[0xe] + 0x3c + iVar18);
      if (puVar17 != (undefined4 *)0x0) {
        for (puVar4 = (undefined4 *)*puVar17; puVar4 != (undefined4 *)0x0;
            puVar4 = (undefined4 *)*puVar4) {
          puVar17 = puVar4;
        }
        *(undefined4 **)(puVar5[0xe] + iVar18 + 0x40) = puVar17;
      }
      param_1 = (uint *)((int)param_1 + 1);
      iVar18 = iVar18 + 0x48;
    } while (param_1 < *puVar12);
  }
  if ((DAT_006da330 & 0x200000) == 0) {
    DAT_006d9cc0 = 0;
    DAT_006d9c90 = 0;
  }
  else {
    sub_415AB0(param_2,&DAT_006d9cc0);
    DAT_006d9c90 = sub_41EF00(DAT_006d9cc0 * 8);
    param_1 = (uint *)0x0;
    if (0 < DAT_006d9cc0) {
      iVar18 = 4;
      do {
        sub_415AB0(param_2,DAT_006d9c90 + -4 + iVar18);
        uVar11 = sub_41EF00(*(int *)(DAT_006d9c90 + -4 + iVar18) << 3);
        *(undefined4 *)(DAT_006d9c90 + iVar18) = uVar11;
        local_1c = 0;
        if (0 < *(int *)(DAT_006d9c90 + -4 + iVar18)) {
          do {
            uVar8 = local_1c;
            iVar9 = local_1c * 8;
            sub_415AF0(param_2,*(int *)(DAT_006d9c90 + iVar18) + iVar9);
            sub_415AF0(param_2,*(int *)(DAT_006d9c90 + iVar18) + 2 + iVar9);
            uVar11 = sub_41EF00((uint)*(ushort *)(*(int *)(DAT_006d9c90 + iVar18) + iVar9) * 0x1c);
            local_24 = 0;
            *(undefined4 *)(*(int *)(DAT_006d9c90 + iVar18) + 4 + iVar9) = uVar11;
            if (*(short *)(iVar9 + *(int *)(DAT_006d9c90 + iVar18)) != 0) {
              iVar10 = 0;
              do {
                iVar2 = *(int *)(iVar9 + 4 + *(int *)(DAT_006d9c90 + iVar18));
                if (iVar10 < 1) {
                  *(undefined4 *)(iVar2 + iVar10) = 0;
                }
                else {
                  piVar14 = (int *)(iVar2 + iVar10);
                  *piVar14 = (int)(piVar14 + -7);
                }
                iVar2 = *(int *)(*(int *)(DAT_006d9c90 + iVar18) + iVar9 + 4);
                if ((int)local_24 < (int)(*(ushort *)(*(int *)(DAT_006d9c90 + iVar18) + iVar9) - 1))
                {
                  *(int *)(iVar2 + 4 + iVar10) = iVar2 + 0x1c + iVar10;
                }
                else {
                  *(undefined4 *)(iVar2 + 4 + iVar10) = 0;
                }
                sub_415AB0(param_2,*(int *)(*(int *)(DAT_006d9c90 + iVar18) + 4 + iVar9) + 8 +
                                   iVar10);
                sub_415AB0(param_2,*(int *)(*(int *)(DAT_006d9c90 + iVar18) + 4 + iVar9) + 0xc +
                                   iVar10);
                if ((DAT_006da330 & 0x4000000) == 0) {
                  *(undefined4 *)
                   (*(int *)(*(int *)(DAT_006d9c90 + iVar18) + 4 + iVar9) + 0x14 + iVar10) = 0;
                }
                else {
                  sub_415AB0(param_2,*(int *)(*(int *)(DAT_006d9c90 + iVar18) + 4 + iVar9) + 0x14 +
                                     iVar10);
                }
                sub_415AF0(param_2,*(int *)(*(int *)(DAT_006d9c90 + iVar18) + 4 + iVar9) + 0x10 +
                                   iVar10);
                sub_415AF0(param_2,*(int *)(*(int *)(DAT_006d9c90 + iVar18) + 4 + iVar9) + 0x12 +
                                   iVar10);
                iVar2 = *(int *)(DAT_006d9c90 + iVar18) + iVar9;
                uVar3 = *(ushort *)
                         (*(int *)(*(int *)(DAT_006d9c90 + iVar18) + 4 + iVar9) + 0x10 + iVar10);
                local_c = (uint *)(uint)uVar3;
                switch(local_c) {
                case (uint *)0x1:
                case (uint *)0x6:
                case (uint *)0x7:
                case (uint *)0xb:
                case (uint *)0xd:
                  *(ushort *)(iVar2 + 2) =
                       *(ushort *)(iVar2 + 2) | (ushort)(1 << ((byte)uVar3 & 0x1f));
                  break;
                case (uint *)0xa:
                  *(ushort *)(iVar2 + 2) = *(ushort *)(iVar2 + 2) | 0x440;
                  break;
                case (uint *)0xc:
                  *(ushort *)(iVar2 + 2) = *(ushort *)(iVar2 + 2) | 0x1040;
                }
                local_24 = local_24 + 1;
                iVar10 = iVar10 + 0x1c;
                uVar8 = local_1c;
              } while ((int)local_24 <
                       (int)(uint)*(ushort *)(iVar9 + *(int *)(DAT_006d9c90 + iVar18)));
            }
            local_1c = uVar8 + 1;
          } while ((int)local_1c < *(int *)(iVar18 + -4 + DAT_006d9c90));
        }
        param_1 = (uint *)((int)param_1 + 1);
        iVar18 = iVar18 + 8;
      } while ((int)param_1 < DAT_006d9cc0);
    }
    DAT_006d9cc0 = DAT_006d9cc0 + -1;
  }
  if ((DAT_006da330 & 0x10) == 0) {
    DAT_006da328 = 200;
  }
  else {
    sub_415AB0(param_2,&DAT_006da328);
  }
  DAT_006da320 = 100;
  if (local_8 != (uint *)0x0) {
    sub_562941(local_8);
  }
  sub_415AF0(param_2,puVar5 + 3);
  return;
}

