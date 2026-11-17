/* sub_2110A200 @ 2110a200   1447 bytes */

void __thiscall sub_2110A200(void *this,int param_1,uint param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int **ppiVar9;
  byte *pbVar10;
  int iVar11;
  char *pcVar12;
  char *pcVar13;
  byte *pbVar14;
  int *piVar15;
  int *piVar16;
  bool bVar17;
  float10 fVar18;
  byte local_18c [128];
  byte local_10c [128];
  int *local_8c;
  undefined4 local_80;
  char *local_7c;
  int *local_78;
  undefined4 local_74;
  undefined4 local_70;
  char *local_6c;
  int *local_68;
  undefined4 local_64;
  undefined4 local_60;
  char *local_5c;
  int *local_58;
  undefined4 local_54;
  undefined4 local_50;
  char *local_4c;
  int *local_48;
  undefined4 local_44;
  undefined4 local_40;
  char *local_3c;
  int *local_38;
  undefined4 local_34;
  undefined4 local_30;
  char *local_2c;
  int *local_28;
  undefined4 local_24;
  byte *local_20;
  int local_1c;
  int *local_18;
  int *local_14;
  uint local_10;
  int *local_c;
  void *local_8;
  
  uVar6 = param_2;
  local_8 = this;
  iVar11 = param_1;
  if (param_1 == 4) {
    iVar11 = 0;
  }
  do {
    piVar15 = (int *)((int)local_8 + (iVar11 * 9 + 0x24) * 4);
    local_c = piVar15;
    if (*piVar15 != 0) {
      if (iVar11 == 0) {
        if ((code *)piVar15[3] != (code *)0x0) {
          (*(code *)piVar15[3])(piVar15[7]);
        }
      }
      else if ((iVar11 == 1) && (piVar15[2] != 0)) {
        (**(code **)(piVar15[2] + 0x20))(piVar15[3]);
      }
      *piVar15 = 0;
    }
  } while ((param_1 == 4) && (iVar11 = iVar11 + 1, iVar11 < 3));
  piVar15[1] = param_2;
  if (param_2 != 0) {
    if (iVar11 == 0) {
      local_18 = piVar15 + 2;
      if (param_3 != 0) {
        local_68 = piVar15 + 3;
        local_58 = piVar15 + 4;
        local_78 = piVar15 + 2;
        local_48 = piVar15 + 5;
        uVar7 = 0xffffffff;
        local_28 = piVar15 + 8;
        local_1c = DAT_211155b4;
        pcVar12 = s_AAL_stream_2111487c;
        do {
          pcVar13 = pcVar12;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        local_38 = piVar15 + 6;
        pbVar10 = (byte *)(pcVar13 + -uVar7);
        pbVar3 = local_18c;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pbVar3 = *(undefined4 *)pbVar10;
          pbVar10 = pbVar10 + 4;
          pbVar3 = pbVar3 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pbVar3 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          pbVar3 = pbVar3 + 1;
        }
        ppiVar9 = &local_78;
        local_80 = 0;
        local_7c = s_ASI_open_21114870;
        local_74 = 0;
        local_70 = 0;
        local_6c = s_ASI_close_21114864;
        local_64 = 0;
        local_60 = 0;
        local_5c = s_ASI_process_21114858;
        local_54 = 0;
        local_50 = 0;
        local_4c = s_ASI_set_preference_21114844;
        local_44 = 0;
        local_40 = 0;
        local_3c = s_ASI_attribute_21114834;
        local_34 = 0;
        local_30 = 1;
        local_2c = s_Position_21114828;
        local_24 = 0;
        local_20 = local_10c;
        param_2 = 6;
        do {
          uVar7 = 0xffffffff;
          piVar15 = ppiVar9[-1];
          do {
            piVar16 = piVar15;
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            piVar16 = (int *)((int)piVar15 + 1);
            iVar11 = *piVar15;
            piVar15 = piVar16;
          } while ((char)iVar11 != '\0');
          piVar15 = ppiVar9[-2];
          uVar7 = ~uVar7;
          pbVar10 = (byte *)((int)piVar16 - uVar7);
          pbVar3 = local_10c;
          for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(undefined4 *)pbVar3 = *(undefined4 *)pbVar10;
            pbVar10 = pbVar10 + 4;
            pbVar3 = pbVar3 + 4;
          }
          for (uVar7 = uVar7 & 3; piVar16 = local_18, uVar7 != 0; uVar7 = uVar7 - 1) {
            *pbVar3 = *pbVar10;
            pbVar10 = pbVar10 + 1;
            pbVar3 = pbVar3 + 1;
          }
          local_14 = piVar15;
          local_8c = piVar15;
          local_10 = 0;
          pbVar10 = local_20;
          do {
            bVar2 = *pbVar10;
            local_10 = local_10 + bVar2;
            pbVar10 = pbVar10 + 1;
          } while (bVar2 != 0);
          for (iVar11 = *(int *)(*(int *)(local_1c + 4) + 0xc + (local_10 & 0x1ff) * 4); iVar11 != 0
              ; iVar11 = *(int *)(iVar11 + 8)) {
            if (local_18c[0] == 0) {
              if ((piVar15 == *(int **)(iVar11 + 0x11c)) && (uVar6 == *(uint *)(iVar11 + 0x18))) {
                pbVar10 = (byte *)(iVar11 + 0x9c);
                pbVar3 = local_10c;
                do {
                  bVar2 = *pbVar3;
                  bVar17 = bVar2 < *pbVar10;
                  if (bVar2 != *pbVar10) {
LAB_2110a67e:
                    iVar4 = (1 - (uint)bVar17) - (uint)(bVar17 != 0);
                    goto joined_r0x2110a70e;
                  }
                  if (bVar2 == 0) break;
                  bVar2 = pbVar3[1];
                  bVar17 = bVar2 < pbVar10[1];
                  if (bVar2 != pbVar10[1]) goto LAB_2110a67e;
                  pbVar3 = pbVar3 + 2;
                  pbVar10 = pbVar10 + 2;
                } while (bVar2 != 0);
                iVar4 = 0;
joined_r0x2110a70e:
                if (iVar4 == 0) {
                  if (iVar11 != 0) {
                    **ppiVar9 = *(int *)(iVar11 + 0x124);
                    goto LAB_2110a74e;
                  }
                  break;
                }
              }
            }
            else if ((piVar15 == *(int **)(iVar11 + 0x11c)) && (uVar6 == *(uint *)(iVar11 + 0x18)))
            {
              pbVar10 = (byte *)(iVar11 + 0x1c);
              pbVar3 = local_18c;
              do {
                bVar2 = *pbVar3;
                bVar17 = bVar2 < *pbVar10;
                if (bVar2 != *pbVar10) {
LAB_2110a6ce:
                  iVar4 = (1 - (uint)bVar17) - (uint)(bVar17 != 0);
                  goto LAB_2110a6d3;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar3[1];
                bVar17 = bVar2 < pbVar10[1];
                if (bVar2 != pbVar10[1]) goto LAB_2110a6ce;
                pbVar3 = pbVar3 + 2;
                pbVar10 = pbVar10 + 2;
              } while (bVar2 != 0);
              iVar4 = 0;
LAB_2110a6d3:
              if (iVar4 == 0) {
                pbVar10 = (byte *)(iVar11 + 0x9c);
                pbVar3 = local_10c;
                do {
                  bVar2 = *pbVar3;
                  bVar17 = bVar2 < *pbVar10;
                  if (bVar2 != *pbVar10) {
LAB_2110a707:
                    iVar4 = (1 - (uint)bVar17) - (uint)(bVar17 != 0);
                    goto joined_r0x2110a70e;
                  }
                  if (bVar2 == 0) break;
                  bVar2 = pbVar3[1];
                  bVar17 = bVar2 < pbVar10[1];
                  if (bVar2 != pbVar10[1]) goto LAB_2110a707;
                  pbVar3 = pbVar3 + 2;
                  pbVar10 = pbVar10 + 2;
                } while (bVar2 != 0);
                iVar4 = 0;
                goto joined_r0x2110a70e;
              }
            }
          }
          if (piVar15 == (int *)0x0) {
            **ppiVar9 = 0;
          }
          else {
            **ppiVar9 = -1;
          }
LAB_2110a74e:
          ppiVar9 = ppiVar9 + 4;
          param_2 = param_2 - 1;
        } while (param_2 != 0);
        if ((code *)*local_18 == (code *)0x0) {
          OutputDebugStringA(s_Failed_to_find_ASI_entry_functio_21114804);
          return;
        }
        iVar11 = (*(code *)*local_18)
                           (local_8,*(undefined4 *)(param_3 + 0x34),
                            *(undefined4 *)((int)local_8 + 0x48));
        piVar16[5] = iVar11;
        *local_c = 1;
      }
    }
    else if (iVar11 == 1) {
      if (param_3 != 0) {
        _AAL_OpenFilterProvider_4(param_2);
        iVar11 = *(int *)(*(int *)((int)local_8 + 0x5c) + 4);
        if (iVar11 != 0) {
          while (*(uint *)(iVar11 + 0x34) != param_2) {
            iVar11 = *(int *)(iVar11 + 0x3c);
            if (iVar11 == 0) {
              return;
            }
          }
          if ((iVar11 != 0) && (*(code **)(iVar11 + 0x1c) != (code *)0x0)) {
            iVar4 = (**(code **)(iVar11 + 0x1c))(*(undefined4 *)(iVar11 + 0x38),local_8);
            piVar15[3] = iVar4;
            if (iVar4 != 0) {
              fVar5 = (float)(**(code **)(iVar11 + 0x28))(iVar4,0);
              fVar18 = sub_2110A160(fVar5);
              *(float *)((int)local_8 + 0x28) = (float)fVar18;
              piVar15[2] = iVar11;
              *piVar15 = 1;
              return;
            }
          }
        }
      }
    }
    else if (iVar11 == 2) {
      uVar6 = 0xffffffff;
      pcVar12 = s_AAL_Mixer_21114134;
      do {
        pcVar13 = pcVar12;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar13 = pcVar12 + 1;
        cVar1 = *pcVar12;
        pcVar12 = pcVar13;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar10 = (byte *)(pcVar13 + -uVar6);
      pbVar3 = local_18c;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar3 = *(undefined4 *)pbVar10;
        pbVar10 = pbVar10 + 4;
        pbVar3 = pbVar3 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar3 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        pbVar3 = pbVar3 + 1;
      }
      pbVar10 = local_10c;
      uVar6 = 0xffffffff;
      pcVar12 = s_MIXER_merge_21114628;
      do {
        pcVar13 = pcVar12;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar13 = pcVar12 + 1;
        cVar1 = *pcVar12;
        pcVar12 = pcVar13;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar3 = (byte *)(pcVar13 + -uVar6);
      pbVar14 = local_10c;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar14 = *(undefined4 *)pbVar3;
        pbVar3 = pbVar3 + 4;
        pbVar14 = pbVar14 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar14 = *pbVar3;
        pbVar3 = pbVar3 + 1;
        pbVar14 = pbVar14 + 1;
      }
      local_8c = (int *)0x0;
      uVar6 = 0;
      do {
        bVar2 = *pbVar10;
        uVar6 = uVar6 + bVar2;
        pbVar10 = pbVar10 + 1;
      } while (bVar2 != 0);
      iVar11 = *(int *)(*(int *)(DAT_211155b4 + 4) + 0xc + (uVar6 & 0x1ff) * 4);
      do {
        if (iVar11 == 0) {
LAB_2110a425:
          local_c[3] = 0;
          *local_c = 1;
          return;
        }
        if (local_18c[0] == 0) {
          if ((*(int *)(iVar11 + 0x11c) == 0) && (param_2 == *(uint *)(iVar11 + 0x18))) {
            pbVar10 = (byte *)(iVar11 + 0x9c);
            pbVar3 = local_10c;
            do {
              bVar2 = *pbVar3;
              bVar17 = bVar2 < *pbVar10;
              if (bVar2 != *pbVar10) {
LAB_2110a38e:
                iVar4 = (1 - (uint)bVar17) - (uint)(bVar17 != 0);
                goto joined_r0x2110a413;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar3[1];
              bVar17 = bVar2 < pbVar10[1];
              if (bVar2 != pbVar10[1]) goto LAB_2110a38e;
              pbVar3 = pbVar3 + 2;
              pbVar10 = pbVar10 + 2;
            } while (bVar2 != 0);
            iVar4 = 0;
joined_r0x2110a413:
            if (iVar4 == 0) {
              if (iVar11 != 0) {
                local_c[3] = *(int *)(iVar11 + 0x124);
                *local_c = 1;
                return;
              }
              goto LAB_2110a425;
            }
          }
        }
        else if ((*(int *)(iVar11 + 0x11c) == 0) && (param_2 == *(uint *)(iVar11 + 0x18))) {
          pbVar10 = (byte *)(iVar11 + 0x1c);
          pbVar3 = local_18c;
          do {
            bVar2 = *pbVar3;
            bVar17 = bVar2 < *pbVar10;
            if (bVar2 != *pbVar10) {
LAB_2110a3d3:
              iVar4 = (1 - (uint)bVar17) - (uint)(bVar17 != 0);
              goto LAB_2110a3d8;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar3[1];
            bVar17 = bVar2 < pbVar10[1];
            if (bVar2 != pbVar10[1]) goto LAB_2110a3d3;
            pbVar3 = pbVar3 + 2;
            pbVar10 = pbVar10 + 2;
          } while (bVar2 != 0);
          iVar4 = 0;
LAB_2110a3d8:
          if (iVar4 == 0) {
            pbVar10 = (byte *)(iVar11 + 0x9c);
            pbVar3 = local_10c;
            do {
              bVar2 = *pbVar3;
              bVar17 = bVar2 < *pbVar10;
              if (bVar2 != *pbVar10) {
LAB_2110a40c:
                iVar4 = (1 - (uint)bVar17) - (uint)(bVar17 != 0);
                goto joined_r0x2110a413;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar3[1];
              bVar17 = bVar2 < pbVar10[1];
              if (bVar2 != pbVar10[1]) goto LAB_2110a40c;
              pbVar3 = pbVar3 + 2;
              pbVar10 = pbVar10 + 2;
            } while (bVar2 != 0);
            iVar4 = 0;
            goto joined_r0x2110a413;
          }
        }
        iVar11 = *(int *)(iVar11 + 8);
      } while( true );
    }
  }
  return;
}

