/* _AAL_Init@0 @ 21101f40   1560 bytes */

undefined4 _AAL_Init_0(void)

{
  char cVar1;
  byte bVar2;
  HANDLE hTargetProcessHandle;
  HANDLE hSourceHandle;
  HANDLE hSourceProcessHandle;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  int iVar7;
  void *pvVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  char *pcVar12;
  char *pcVar13;
  bool bVar14;
  LPHANDLE lpTargetHandle;
  DWORD dwDesiredAccess;
  BOOL bInheritHandle;
  DWORD dwOptions;
  uint local_124;
  byte local_120 [128];
  byte local_a0 [128];
  int local_20;
  byte *local_14;
  byte *local_10;
  uint local_c;
  uint local_8;
  
                    /* 0x1f40  42  _AAL_Init@0 */
  if (DAT_211155b4 == (undefined4 *)0x0) {
    dwOptions = 2;
    bInheritHandle = 0;
    dwDesiredAccess = 0;
    lpTargetHandle = (LPHANDLE)&DAT_211155bc;
    hTargetProcessHandle = GetCurrentProcess();
    hSourceHandle = GetCurrentThread();
    hSourceProcessHandle = GetCurrentProcess();
    DuplicateHandle(hSourceProcessHandle,hSourceHandle,hTargetProcessHandle,lpTargetHandle,
                    dwDesiredAccess,bInheritHandle,dwOptions);
    iVar3 = sub_21101200();
    if (iVar3 == 0) {
      AAL_SetError(s_The_DirectSound_DLL_could_not_be_21114148);
      return 1;
    }
    uVar4 = sub_21101D40();
    if (uVar4 == 0) {
      return 8;
    }
    CoInitialize((LPVOID)0x0);
    puVar5 = operator_new(0x10);
    if (puVar5 == (undefined4 *)0x0) {
      DAT_211155b4 = (undefined4 *)0x0;
    }
    else {
      DAT_211155b4 = sub_211089E0(puVar5);
    }
    local_c = 0;
    sub_21108E50(DAT_211155b4,s___aml_21114140);
    iVar3 = sub_21109660(DAT_211155b4,s_AAL_Mixer_21114134,&local_c,&local_8);
    if (iVar3 != 0) {
      local_10 = local_a0;
      do {
        local_124 = local_8;
        uVar4 = 0xffffffff;
        pcVar12 = s_AAL_Mixer_21114134;
        do {
          pcVar13 = pcVar12;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        local_20 = 0;
        pbVar11 = (byte *)(pcVar13 + -uVar4);
        pbVar6 = local_120;
        for (uVar9 = uVar4 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pbVar6 = *(undefined4 *)pbVar11;
          pbVar11 = pbVar11 + 4;
          pbVar6 = pbVar6 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pbVar6 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          pbVar6 = pbVar6 + 1;
        }
        uVar4 = 0xffffffff;
        pcVar12 = s_MIXER_init_21114128;
        do {
          pcVar13 = pcVar12;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pbVar11 = (byte *)(pcVar13 + -uVar4);
        pbVar6 = local_a0;
        for (uVar9 = uVar4 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pbVar6 = *(undefined4 *)pbVar11;
          pbVar11 = pbVar11 + 4;
          pbVar6 = pbVar6 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pbVar6 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          pbVar6 = pbVar6 + 1;
        }
        local_14 = (byte *)0x0;
        pbVar11 = local_10;
        do {
          bVar2 = *pbVar11;
          local_14 = local_14 + bVar2;
          pbVar11 = pbVar11 + 1;
        } while (bVar2 != 0);
        for (pvVar8 = *(void **)(DAT_211155b4[1] + 0xc + ((uint)local_14 & 0x1ff) * 4);
            pvVar8 != (void *)0x0; pvVar8 = *(void **)((int)pvVar8 + 8)) {
          iVar3 = sub_21103430(pvVar8,(int *)&local_124);
          if (iVar3 != 0) {
            if (pvVar8 != (void *)0x0) {
              (**(code **)((int)pvVar8 + 0x124))();
            }
            break;
          }
        }
        iVar3 = sub_21109660(DAT_211155b4,s_AAL_Mixer_21114134,&local_c,&local_8);
      } while (iVar3 != 0);
    }
    local_c = 0;
    sub_21108E50(DAT_211155b4,s___adl_21114120);
    iVar3 = sub_21109660(DAT_211155b4,s_AAL_codec_21114114,&local_c,&local_8);
    if (iVar3 != 0) {
      local_14 = local_a0;
      do {
        uVar4 = local_8;
        uVar9 = 0xffffffff;
        local_124 = local_8;
        pcVar12 = s_AAL_codec_21114114;
        do {
          pcVar13 = pcVar12;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar9 = ~uVar9;
        local_20 = 0;
        pbVar11 = (byte *)(pcVar13 + -uVar9);
        pbVar6 = local_120;
        for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pbVar6 = *(undefined4 *)pbVar11;
          pbVar11 = pbVar11 + 4;
          pbVar6 = pbVar6 + 4;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *pbVar6 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          pbVar6 = pbVar6 + 1;
        }
        uVar9 = 0xffffffff;
        pcVar12 = s_ASI_init_21114108;
        do {
          pcVar13 = pcVar12;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar9 = ~uVar9;
        pbVar11 = (byte *)(pcVar13 + -uVar9);
        pbVar6 = local_a0;
        for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pbVar6 = *(undefined4 *)pbVar11;
          pbVar11 = pbVar11 + 4;
          pbVar6 = pbVar6 + 4;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *pbVar6 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          pbVar6 = pbVar6 + 1;
        }
        local_10 = (byte *)0x0;
        pbVar11 = local_14;
        do {
          bVar2 = *pbVar11;
          local_10 = local_10 + bVar2;
          pbVar11 = pbVar11 + 1;
        } while (bVar2 != 0);
        for (iVar3 = *(int *)(DAT_211155b4[1] + 0xc + ((uint)local_10 & 0x1ff) * 4); iVar3 != 0;
            iVar3 = *(int *)(iVar3 + 8)) {
          if (local_120[0] == 0) {
            if ((local_20 == *(int *)(iVar3 + 0x11c)) && (uVar4 == *(uint *)(iVar3 + 0x18))) {
              pbVar11 = (byte *)(iVar3 + 0x9c);
              pbVar6 = local_a0;
              do {
                bVar2 = *pbVar6;
                bVar14 = bVar2 < *pbVar11;
                if (bVar2 != *pbVar11) {
LAB_2110222b:
                  iVar7 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                  goto joined_r0x211022b7;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar6[1];
                bVar14 = bVar2 < pbVar11[1];
                if (bVar2 != pbVar11[1]) goto LAB_2110222b;
                pbVar6 = pbVar6 + 2;
                pbVar11 = pbVar11 + 2;
              } while (bVar2 != 0);
              iVar7 = 0;
joined_r0x211022b7:
              if (iVar7 == 0) {
                if (iVar3 != 0) {
                  (**(code **)(iVar3 + 0x124))();
                }
                break;
              }
            }
          }
          else if ((local_20 == *(int *)(iVar3 + 0x11c)) && (uVar4 == *(uint *)(iVar3 + 0x18))) {
            pbVar11 = (byte *)(iVar3 + 0x1c);
            pbVar6 = local_120;
            do {
              bVar2 = *pbVar6;
              bVar14 = bVar2 < *pbVar11;
              if (bVar2 != *pbVar11) {
LAB_21102277:
                iVar7 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                goto LAB_2110227c;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar6[1];
              bVar14 = bVar2 < pbVar11[1];
              if (bVar2 != pbVar11[1]) goto LAB_21102277;
              pbVar6 = pbVar6 + 2;
              pbVar11 = pbVar11 + 2;
            } while (bVar2 != 0);
            iVar7 = 0;
LAB_2110227c:
            if (iVar7 == 0) {
              pbVar11 = (byte *)(iVar3 + 0x9c);
              pbVar6 = local_a0;
              do {
                bVar2 = *pbVar6;
                bVar14 = bVar2 < *pbVar11;
                if (bVar2 != *pbVar11) {
LAB_211022b0:
                  iVar7 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                  goto joined_r0x211022b7;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar6[1];
                bVar14 = bVar2 < pbVar11[1];
                if (bVar2 != pbVar11[1]) goto LAB_211022b0;
                pbVar6 = pbVar6 + 2;
                pbVar11 = pbVar11 + 2;
              } while (bVar2 != 0);
              iVar7 = 0;
              goto joined_r0x211022b7;
            }
          }
        }
        iVar3 = sub_21109660(DAT_211155b4,s_AAL_codec_21114114,&local_c,&local_8);
      } while (iVar3 != 0);
    }
    local_c = 0;
    sub_21108E50(DAT_211155b4,s___3dl_21114100);
    iVar3 = sub_21109660(DAT_211155b4,&DAT_211140f8,&local_c,&local_8);
    if (iVar3 != 0) {
      local_14 = local_a0;
      do {
        local_124 = local_8;
        uVar4 = 0xffffffff;
        pcVar12 = &DAT_211140f8;
        do {
          pcVar13 = pcVar12;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        local_20 = 0;
        pbVar11 = (byte *)(pcVar13 + -uVar4);
        pbVar6 = local_120;
        for (uVar9 = uVar4 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pbVar6 = *(undefined4 *)pbVar11;
          pbVar11 = pbVar11 + 4;
          pbVar6 = pbVar6 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pbVar6 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          pbVar6 = pbVar6 + 1;
        }
        uVar4 = 0xffffffff;
        pcVar12 = s_AL3D_init_211140ec;
        do {
          pcVar13 = pcVar12;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pbVar11 = (byte *)(pcVar13 + -uVar4);
        pbVar6 = local_a0;
        for (uVar9 = uVar4 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pbVar6 = *(undefined4 *)pbVar11;
          pbVar11 = pbVar11 + 4;
          pbVar6 = pbVar6 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pbVar6 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          pbVar6 = pbVar6 + 1;
        }
        local_10 = (byte *)0x0;
        pbVar11 = local_14;
        do {
          bVar2 = *pbVar11;
          local_10 = local_10 + bVar2;
          pbVar11 = pbVar11 + 1;
        } while (bVar2 != 0);
        for (pvVar8 = *(void **)(DAT_211155b4[1] + 0xc + ((uint)local_10 & 0x1ff) * 4);
            pvVar8 != (void *)0x0; pvVar8 = *(void **)((int)pvVar8 + 8)) {
          iVar3 = sub_21103430(pvVar8,(int *)&local_124);
          if (iVar3 != 0) {
            if (pvVar8 != (void *)0x0) {
              (**(code **)((int)pvVar8 + 0x124))();
            }
            break;
          }
        }
        iVar3 = sub_21109660(DAT_211155b4,&DAT_211140f8,&local_c,&local_8);
      } while (iVar3 != 0);
    }
    local_c = 0;
    sub_21108E50(DAT_211155b4,s___aft_211140e4);
    iVar3 = sub_21109660(DAT_211155b4,s_AAL_filter_211140d8,&local_c,&local_8);
    if (iVar3 != 0) {
      local_14 = local_a0;
      do {
        local_124 = local_8;
        uVar4 = 0xffffffff;
        pcVar12 = s_AAL_filter_211140d8;
        do {
          pcVar13 = pcVar12;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        local_20 = 0;
        pbVar11 = (byte *)(pcVar13 + -uVar4);
        pbVar6 = local_120;
        for (uVar9 = uVar4 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pbVar6 = *(undefined4 *)pbVar11;
          pbVar11 = pbVar11 + 4;
          pbVar6 = pbVar6 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pbVar6 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          pbVar6 = pbVar6 + 1;
        }
        uVar4 = 0xffffffff;
        pcVar12 = s_FLT_init_211140cc;
        do {
          pcVar13 = pcVar12;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pbVar11 = (byte *)(pcVar13 + -uVar4);
        pbVar6 = local_a0;
        for (uVar9 = uVar4 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pbVar6 = *(undefined4 *)pbVar11;
          pbVar11 = pbVar11 + 4;
          pbVar6 = pbVar6 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pbVar6 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          pbVar6 = pbVar6 + 1;
        }
        local_10 = (byte *)0x0;
        pbVar11 = local_14;
        do {
          bVar2 = *pbVar11;
          local_10 = local_10 + bVar2;
          pbVar11 = pbVar11 + 1;
        } while (bVar2 != 0);
        for (pvVar8 = *(void **)(DAT_211155b4[1] + 0xc + ((uint)local_10 & 0x1ff) * 4);
            pvVar8 != (void *)0x0; pvVar8 = *(void **)((int)pvVar8 + 8)) {
          iVar3 = sub_21103430(pvVar8,(int *)&local_124);
          if (iVar3 != 0) {
            if (pvVar8 != (void *)0x0) {
              (**(code **)((int)pvVar8 + 0x124))();
            }
            break;
          }
        }
        iVar3 = sub_21109660(DAT_211155b4,s_AAL_filter_211140d8,&local_c,&local_8);
      } while (iVar3 != 0);
    }
    pvVar8 = operator_new(0x18);
    if (pvVar8 != (void *)0x0) {
      DAT_211155b0 = sub_21109B80(pvVar8,4);
      return 0;
    }
    DAT_211155b0 = (undefined4 *)0x0;
  }
  return 0;
}

