/* _AAL_Quit@0 @ 21102560   1219 bytes */

undefined4 _AAL_Quit_0(void)

{
  char cVar1;
  byte bVar2;
  void *pvVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  char *pcVar10;
  char *pcVar11;
  byte *pbVar12;
  uint local_124;
  char local_120 [128];
  byte local_a0 [128];
  undefined4 local_20;
  byte *local_14;
  byte *local_10;
  uint local_c;
  uint local_8;
  
                    /* 0x2560  52  _AAL_Quit@0 */
  if (DAT_21115588 != (LPVOID)0x0) {
    sub_2110D4F4(DAT_21115588);
    DAT_21115588 = (LPVOID)0x0;
  }
  if (DAT_211155b0 != (int *)0x0) {
    _AAL_Lock_0();
    sub_21109D50(DAT_211155b0);
    piVar4 = DAT_211155b0;
    if (DAT_211155b0 != (int *)0x0) {
      sub_21109BF0(DAT_211155b0);
      sub_2110D4F4(piVar4);
      DAT_211155b0 = (int *)0x0;
    }
    _AAL_Unlock_0();
  }
  if (DAT_211155ac != 0) {
    _AAL_QuitDriver_4(1);
  }
  if (DAT_211155b4 != (undefined4 *)0x0) {
    local_c = 0;
    iVar6 = sub_21109660(DAT_211155b4,s_AAL_Mixer_21114134,&local_c,&local_8);
    if (iVar6 != 0) {
      local_10 = local_a0;
      do {
        uVar7 = 0xffffffff;
        pcVar10 = s_AAL_Mixer_21114134;
        do {
          pcVar11 = pcVar10;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        local_20 = 0;
        pcVar10 = pcVar11 + -uVar7;
        pcVar11 = local_120;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar11 = pcVar11 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar11 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar11 = pcVar11 + 1;
        }
        uVar7 = 0xffffffff;
        pcVar10 = s_MIXER_shutdown_211141a4;
        do {
          pcVar11 = pcVar10;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        pbVar9 = (byte *)(pcVar11 + -uVar7);
        pbVar12 = local_a0;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pbVar12 = *(undefined4 *)pbVar9;
          pbVar9 = pbVar9 + 4;
          pbVar12 = pbVar12 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pbVar12 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          pbVar12 = pbVar12 + 1;
        }
        local_14 = (byte *)0x0;
        pbVar9 = local_10;
        do {
          bVar2 = *pbVar9;
          local_14 = local_14 + bVar2;
          pbVar9 = pbVar9 + 1;
        } while (bVar2 != 0);
        for (pvVar3 = *(void **)(DAT_211155b4[1] + 0xc + ((uint)local_14 & 0x1ff) * 4);
            pvVar3 != (void *)0x0; pvVar3 = *(void **)((int)pvVar3 + 8)) {
          iVar6 = sub_21103430(pvVar3,(int *)&local_124);
          if (iVar6 != 0) {
            if (pvVar3 != (void *)0x0) {
              (**(code **)((int)pvVar3 + 0x124))();
            }
            break;
          }
        }
        iVar6 = sub_21109660(DAT_211155b4,s_AAL_Mixer_21114134,&local_c,&local_8);
      } while (iVar6 != 0);
    }
    local_c = 0;
    iVar6 = sub_21109660(DAT_211155b4,s_AAL_codec_21114114,&local_c,&local_8);
    if (iVar6 != 0) {
      local_14 = local_a0;
      do {
        uVar7 = 0xffffffff;
        pcVar10 = s_AAL_codec_21114114;
        do {
          pcVar11 = pcVar10;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        local_20 = 0;
        pcVar10 = pcVar11 + -uVar7;
        pcVar11 = local_120;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar11 = pcVar11 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar11 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar11 = pcVar11 + 1;
        }
        uVar7 = 0xffffffff;
        pcVar10 = s_ASI_shutdown_21114194;
        do {
          pcVar11 = pcVar10;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        pbVar9 = (byte *)(pcVar11 + -uVar7);
        pbVar12 = local_a0;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pbVar12 = *(undefined4 *)pbVar9;
          pbVar9 = pbVar9 + 4;
          pbVar12 = pbVar12 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pbVar12 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          pbVar12 = pbVar12 + 1;
        }
        local_10 = (byte *)0x0;
        pbVar9 = local_14;
        do {
          bVar2 = *pbVar9;
          local_10 = local_10 + bVar2;
          pbVar9 = pbVar9 + 1;
        } while (bVar2 != 0);
        for (pvVar3 = *(void **)(DAT_211155b4[1] + 0xc + ((uint)local_10 & 0x1ff) * 4);
            pvVar3 != (void *)0x0; pvVar3 = *(void **)((int)pvVar3 + 8)) {
          iVar6 = sub_21103430(pvVar3,(int *)&local_124);
          if (iVar6 != 0) {
            if (pvVar3 != (void *)0x0) {
              (**(code **)((int)pvVar3 + 0x124))();
            }
            break;
          }
        }
        iVar6 = sub_21109660(DAT_211155b4,s_AAL_codec_21114114,&local_c,&local_8);
      } while (iVar6 != 0);
    }
    local_c = 0;
    iVar6 = sub_21109660(DAT_211155b4,&DAT_211140f8,&local_c,&local_8);
    if (iVar6 != 0) {
      local_14 = local_a0;
      do {
        uVar7 = 0xffffffff;
        pcVar10 = &DAT_211140f8;
        do {
          pcVar11 = pcVar10;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        local_20 = 0;
        pcVar10 = pcVar11 + -uVar7;
        pcVar11 = local_120;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar11 = pcVar11 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar11 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar11 = pcVar11 + 1;
        }
        uVar7 = 0xffffffff;
        pcVar10 = s_AL3D_shutdown_21114184;
        do {
          pcVar11 = pcVar10;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        pbVar9 = (byte *)(pcVar11 + -uVar7);
        pbVar12 = local_a0;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pbVar12 = *(undefined4 *)pbVar9;
          pbVar9 = pbVar9 + 4;
          pbVar12 = pbVar12 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pbVar12 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          pbVar12 = pbVar12 + 1;
        }
        local_10 = (byte *)0x0;
        pbVar9 = local_14;
        do {
          bVar2 = *pbVar9;
          local_10 = local_10 + bVar2;
          pbVar9 = pbVar9 + 1;
        } while (bVar2 != 0);
        for (pvVar3 = *(void **)(DAT_211155b4[1] + 0xc + ((uint)local_10 & 0x1ff) * 4);
            pvVar3 != (void *)0x0; pvVar3 = *(void **)((int)pvVar3 + 8)) {
          iVar6 = sub_21103430(pvVar3,(int *)&local_124);
          if (iVar6 != 0) {
            if (pvVar3 != (void *)0x0) {
              (**(code **)((int)pvVar3 + 0x124))();
            }
            break;
          }
        }
        iVar6 = sub_21109660(DAT_211155b4,&DAT_211140f8,&local_c,&local_8);
      } while (iVar6 != 0);
    }
    local_c = 0;
    iVar6 = sub_21109660(DAT_211155b4,s_AAL_filter_211140d8,&local_c,&local_8);
    if (iVar6 != 0) {
      local_14 = local_a0;
      do {
        uVar7 = 0xffffffff;
        pcVar10 = s_AAL_filter_211140d8;
        do {
          pcVar11 = pcVar10;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        local_20 = 0;
        pcVar10 = pcVar11 + -uVar7;
        pcVar11 = local_120;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar11 = pcVar11 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar11 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar11 = pcVar11 + 1;
        }
        uVar7 = 0xffffffff;
        pcVar10 = s_FLT_shutdown_21114174;
        do {
          pcVar11 = pcVar10;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        pbVar9 = (byte *)(pcVar11 + -uVar7);
        pbVar12 = local_a0;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pbVar12 = *(undefined4 *)pbVar9;
          pbVar9 = pbVar9 + 4;
          pbVar12 = pbVar12 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pbVar12 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          pbVar12 = pbVar12 + 1;
        }
        local_10 = (byte *)0x0;
        pbVar9 = local_14;
        do {
          bVar2 = *pbVar9;
          local_10 = local_10 + bVar2;
          pbVar9 = pbVar9 + 1;
        } while (bVar2 != 0);
        for (pvVar3 = *(void **)(DAT_211155b4[1] + 0xc + ((uint)local_10 & 0x1ff) * 4);
            pvVar3 != (void *)0x0; pvVar3 = *(void **)((int)pvVar3 + 8)) {
          iVar6 = sub_21103430(pvVar3,(int *)&local_124);
          if (iVar6 != 0) {
            if (pvVar3 != (void *)0x0) {
              (**(code **)((int)pvVar3 + 0x124))();
            }
            break;
          }
        }
        iVar6 = sub_21109660(DAT_211155b4,s_AAL_filter_211140d8,&local_c,&local_8);
      } while (iVar6 != 0);
    }
    puVar5 = DAT_211155b4;
    if (DAT_211155b4 != (undefined4 *)0x0) {
      sub_21108D10(DAT_211155b4);
      sub_2110D4F4(puVar5);
      DAT_211155b4 = (undefined4 *)0x0;
    }
    sub_211012D0();
    sub_21101D90();
    CloseHandle(DAT_211155bc);
  }
  return 0;
}

