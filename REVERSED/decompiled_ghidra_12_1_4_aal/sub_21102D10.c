/* _AAL_UnloadFile@4 @ 21102d10   668 bytes */

void _AAL_UnloadFile_4(undefined4 *param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  char *pcVar10;
  char *pcVar11;
  bool bVar12;
  byte local_120 [128];
  byte local_a0 [128];
  int local_20;
  uint local_14;
  byte *local_10;
  undefined4 *local_c;
  uint local_8;
  
                    /* 0x2d10  73  _AAL_UnloadFile@4 */
  local_c = DAT_211155d8;
  if (DAT_211155d8 != (undefined4 *)0x0) {
    while (puVar9 = local_c, local_c != param_1) {
      local_c = (undefined4 *)local_c[0x13];
      if (local_c == (undefined4 *)0x0) {
        return;
      }
    }
    if ((DAT_211155ac != (void *)0x0) &&
       (sub_21104950(DAT_211155ac,(int)local_c), DAT_211155b4 != (void *)0x0)) {
      local_8 = 0;
      iVar3 = sub_21109660(DAT_211155b4,&DAT_211140f8,&local_8,(uint *)&param_1);
      if (iVar3 != 0) {
        local_10 = local_a0;
        do {
          uVar6 = 0xffffffff;
          pcVar10 = &DAT_211140f8;
          do {
            pcVar11 = pcVar10;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pcVar11 = pcVar10 + 1;
            cVar1 = *pcVar10;
            pcVar10 = pcVar11;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          local_20 = 0;
          pbVar8 = (byte *)(pcVar11 + -uVar6);
          pbVar4 = local_120;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pbVar4 = *(undefined4 *)pbVar8;
            pbVar8 = pbVar8 + 4;
            pbVar4 = pbVar4 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pbVar4 = *pbVar8;
            pbVar8 = pbVar8 + 1;
            pbVar4 = pbVar4 + 1;
          }
          uVar6 = 0xffffffff;
          pcVar10 = s_AL3D_DestroyVoiceFile_211141b4;
          do {
            pcVar11 = pcVar10;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pcVar11 = pcVar10 + 1;
            cVar1 = *pcVar10;
            pcVar10 = pcVar11;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          pbVar8 = (byte *)(pcVar11 + -uVar6);
          pbVar4 = local_a0;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pbVar4 = *(undefined4 *)pbVar8;
            pbVar8 = pbVar8 + 4;
            pbVar4 = pbVar4 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pbVar4 = *pbVar8;
            pbVar8 = pbVar8 + 1;
            pbVar4 = pbVar4 + 1;
          }
          local_14 = 0;
          pbVar8 = local_10;
          do {
            bVar2 = *pbVar8;
            local_14 = local_14 + bVar2;
            pbVar8 = pbVar8 + 1;
          } while (bVar2 != 0);
          for (iVar3 = *(int *)(*(int *)((int)DAT_211155b4 + 4) + 0xc + (local_14 & 0x1ff) * 4);
              iVar3 != 0; iVar3 = *(int *)(iVar3 + 8)) {
            if (local_120[0] == 0) {
              if ((local_20 == *(int *)(iVar3 + 0x11c)) &&
                 (param_1 == *(undefined4 **)(iVar3 + 0x18))) {
                pbVar8 = (byte *)(iVar3 + 0x9c);
                pbVar4 = local_a0;
                do {
                  bVar2 = *pbVar4;
                  bVar12 = bVar2 < *pbVar8;
                  if (bVar2 != *pbVar8) {
LAB_21102e8b:
                    iVar5 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
                    goto joined_r0x21102f13;
                  }
                  if (bVar2 == 0) break;
                  bVar2 = pbVar4[1];
                  bVar12 = bVar2 < pbVar8[1];
                  if (bVar2 != pbVar8[1]) goto LAB_21102e8b;
                  pbVar4 = pbVar4 + 2;
                  pbVar8 = pbVar8 + 2;
                } while (bVar2 != 0);
                iVar5 = 0;
joined_r0x21102f13:
                if (iVar5 == 0) {
                  if (iVar3 != 0) {
                    (**(code **)(iVar3 + 0x124))(local_c);
                  }
                  break;
                }
              }
            }
            else if ((local_20 == *(int *)(iVar3 + 0x11c)) &&
                    (param_1 == *(undefined4 **)(iVar3 + 0x18))) {
              pbVar8 = (byte *)(iVar3 + 0x1c);
              pbVar4 = local_120;
              do {
                bVar2 = *pbVar4;
                bVar12 = bVar2 < *pbVar8;
                if (bVar2 != *pbVar8) {
LAB_21102ed3:
                  iVar5 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
                  goto LAB_21102ed8;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar4[1];
                bVar12 = bVar2 < pbVar8[1];
                if (bVar2 != pbVar8[1]) goto LAB_21102ed3;
                pbVar4 = pbVar4 + 2;
                pbVar8 = pbVar8 + 2;
              } while (bVar2 != 0);
              iVar5 = 0;
LAB_21102ed8:
              if (iVar5 == 0) {
                pbVar8 = (byte *)(iVar3 + 0x9c);
                pbVar4 = local_a0;
                do {
                  bVar2 = *pbVar4;
                  bVar12 = bVar2 < *pbVar8;
                  if (bVar2 != *pbVar8) {
LAB_21102f0c:
                    iVar5 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
                    goto joined_r0x21102f13;
                  }
                  if (bVar2 == 0) break;
                  bVar2 = pbVar4[1];
                  bVar12 = bVar2 < pbVar8[1];
                  if (bVar2 != pbVar8[1]) goto LAB_21102f0c;
                  pbVar4 = pbVar4 + 2;
                  pbVar8 = pbVar8 + 2;
                } while (bVar2 != 0);
                iVar5 = 0;
                goto joined_r0x21102f13;
              }
            }
          }
          iVar3 = sub_21109660(DAT_211155b4,&DAT_211140f8,&local_8,(uint *)&param_1);
          puVar9 = local_c;
        } while (iVar3 != 0);
      }
    }
    if (puVar9[0x14] != 0) {
      *(undefined4 *)(puVar9[0x14] + 0x4c) = puVar9[0x13];
    }
    if (puVar9[0x13] != 0) {
      *(undefined4 *)(puVar9[0x13] + 0x50) = puVar9[0x14];
    }
    if (DAT_211155dc == puVar9) {
      DAT_211155dc = (undefined4 *)puVar9[0x14];
    }
    if (DAT_211155d8 == puVar9) {
      DAT_211155d8 = (undefined4 *)puVar9[0x13];
    }
    if (puVar9 != (undefined4 *)0x0) {
      sub_211061D0(puVar9);
      sub_2110D4F4(puVar9);
    }
  }
  return;
}

