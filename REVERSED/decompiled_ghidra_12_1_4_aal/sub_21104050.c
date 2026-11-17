/* _AAL_OpenFilterProvider@4 @ 21104050   1117 bytes */

LPVOID _AAL_OpenFilterProvider_4(uint param_1)

{
  char cVar1;
  byte bVar2;
  void *pvVar3;
  void *this;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  void **ppvVar8;
  int **ppiVar9;
  byte *pbVar10;
  char *pcVar11;
  char *pcVar12;
  int *piVar13;
  int *piVar14;
  byte *pbVar15;
  uint local_1f4;
  char local_1f0 [128];
  byte local_170 [128];
  int *local_f0;
  undefined4 local_e4;
  char *local_e0;
  void *local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  char *local_d0;
  int local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  char *local_c0;
  int local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  char *local_b0;
  int *local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  char *local_a0;
  int local_9c;
  undefined4 local_98;
  undefined4 local_94;
  char *local_90;
  int local_8c;
  undefined4 local_88;
  undefined4 local_84;
  char *local_80;
  int local_7c;
  undefined4 local_78;
  undefined4 local_74;
  char *local_70;
  int *local_6c;
  undefined4 local_68;
  undefined4 local_64;
  char *local_60;
  int local_5c;
  undefined4 local_58;
  undefined4 local_54;
  char *local_50;
  int local_4c;
  undefined4 local_48;
  undefined4 local_44;
  char *local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  char *local_30;
  int local_2c;
  undefined4 local_28;
  void *local_24;
  int *local_20;
  int *local_1c;
  int *local_18;
  byte *local_14;
  int *local_10;
  int local_c;
  int **local_8;
  
                    /* 0x4050  49  _AAL_OpenFilterProvider@4 */
  if ((DAT_211155ac != 0) && (DAT_211155b4 != (int *)0x0)) {
    for (iVar4 = *(int *)(DAT_211155ac + 4); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x3c)) {
      if ((*(int *)(iVar4 + 0x30) == DAT_211155ac) && (*(uint *)(iVar4 + 0x34) == param_1)) {
        return (LPVOID)0x0;
      }
    }
    local_24 = operator_new(0x40);
    if (param_1 != 0) {
      *(void **)(*(int *)(*DAT_211155b4 + 0xc) + 0x10 + param_1 * 0x30) = local_24;
    }
    local_cc = (int)local_24 + 4;
    local_bc = (int)local_24 + 8;
    local_1c = (int *)((int)local_24 + 0xc);
    local_ac = (int *)((int)local_24 + 0xc);
    local_9c = (int)local_24 + 0x10;
    local_8c = (int)local_24 + 0x14;
    local_7c = (int)local_24 + 0x18;
    local_20 = (int *)((int)local_24 + 0x1c);
    local_6c = (int *)((int)local_24 + 0x1c);
    local_5c = (int)local_24 + 0x20;
    local_4c = (int)local_24 + 0x24;
    local_3c = (int)local_24 + 0x28;
    local_dc = local_24;
    uVar6 = 0xffffffff;
    local_2c = (int)local_24 + 0x2c;
    local_18 = DAT_211155b4;
    pcVar11 = s_AAL_filter_211140d8;
    do {
      pcVar12 = pcVar11;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar12 = pcVar11 + 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar12;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    local_1f4 = param_1;
    local_e4 = 0;
    local_d8 = 0;
    local_d4 = 0;
    local_c8 = 0;
    local_c4 = 0;
    local_b8 = 0;
    local_b4 = 0;
    local_a8 = 0;
    local_a4 = 0;
    local_98 = 0;
    local_94 = 0;
    local_88 = 0;
    local_84 = 0;
    local_78 = 0;
    local_74 = 0;
    local_68 = 0;
    local_64 = 0;
    local_58 = 0;
    local_54 = 0;
    local_48 = 0;
    local_44 = 0;
    local_38 = 0;
    local_34 = 0;
    local_28 = 0;
    pcVar11 = pcVar12 + -uVar6;
    pcVar12 = local_1f0;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar12 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar12 = pcVar12 + 1;
    }
    local_e0 = s_ALP_query_attribute_211141cc;
    local_d0 = s_FLT_init_211140cc;
    local_c0 = s_FLT_shutdown_21114174;
    local_b0 = s_FLT_open_driver_21114368;
    local_a0 = s_FLT_close_driver_21114354;
    local_90 = s_FLT_premix_process_21114340;
    local_80 = s_FLT_postmix_process_2111432c;
    local_70 = s_FLT_voice_open_2111431c;
    local_60 = s_FLT_voice_close_2111430c;
    local_50 = s_FLT_voice_process_211142f8;
    local_40 = s_FLT_voice_get_attribute_211142e0;
    local_30 = s_FLT_voice_set_attribute_211142c8;
    local_14 = local_170;
    ppvVar8 = &local_dc;
    local_8 = ppvVar8;
    local_c = 7;
    do {
      uVar6 = 0xffffffff;
      pcVar11 = ppvVar8[-1];
      do {
        pcVar12 = pcVar11;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar12 = pcVar11 + 1;
        cVar1 = *pcVar11;
        pcVar11 = pcVar12;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar10 = (byte *)(pcVar12 + -uVar6);
      pbVar15 = local_170;
      local_8 = ppvVar8;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar10;
        pbVar10 = pbVar10 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        pbVar15 = pbVar15 + 1;
      }
      pvVar3 = ppvVar8[-2];
      local_f0 = pvVar3;
      local_10 = (int *)0x0;
      pbVar10 = local_14;
      do {
        bVar2 = *pbVar10;
        local_10 = (int *)((int)local_10 + (uint)bVar2);
        pbVar10 = pbVar10 + 1;
      } while (bVar2 != 0);
      for (this = *(void **)(local_18[1] + 0xc + ((uint)local_10 & 0x1ff) * 4); this != (void *)0x0;
          this = *(void **)((int)this + 8)) {
        iVar4 = sub_21103430(this,(int *)&local_1f4);
        if (iVar4 != 0) {
          if (this != (void *)0x0) {
            **local_8 = *(undefined4 *)((int)this + 0x124);
            goto LAB_211042e3;
          }
          break;
        }
      }
      if (pvVar3 == (void *)0x0) {
        **local_8 = 0;
      }
      else {
        **local_8 = 0xffffffff;
      }
LAB_211042e3:
      ppvVar8 = local_8 + 4;
      local_c = local_c + -1;
      local_8 = ppvVar8;
    } while (local_c != 0);
    if (*local_1c == 0) {
      _AAL_CloseFilterProvider_4(param_1);
    }
    else {
      local_1f4 = param_1;
      uVar6 = 0xffffffff;
      local_10 = DAT_211155b4;
      pcVar11 = s_AAL_filter_stream_211142b4;
      do {
        pcVar12 = pcVar11;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar12 = pcVar11 + 1;
        cVar1 = *pcVar11;
        pcVar11 = pcVar12;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pcVar11 = pcVar12 + -uVar6;
      pcVar12 = local_1f0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar11;
        pcVar11 = pcVar11 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar12 = *pcVar11;
        pcVar11 = pcVar11 + 1;
        pcVar12 = pcVar12 + 1;
      }
      ppiVar9 = &local_6c;
      local_14 = local_170;
      local_8 = ppiVar9;
      local_c = 5;
      do {
        uVar6 = 0xffffffff;
        piVar13 = ppiVar9[-1];
        do {
          piVar14 = piVar13;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          piVar14 = (int *)((int)piVar13 + 1);
          iVar4 = *piVar13;
          piVar13 = piVar14;
        } while ((char)iVar4 != '\0');
        uVar6 = ~uVar6;
        pbVar10 = (byte *)((int)piVar14 - uVar6);
        pbVar15 = local_170;
        local_8 = ppiVar9;
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pbVar15 = *(undefined4 *)pbVar10;
          pbVar10 = pbVar10 + 4;
          pbVar15 = pbVar15 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pbVar15 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          pbVar15 = pbVar15 + 1;
        }
        piVar13 = ppiVar9[-2];
        local_f0 = piVar13;
        local_18 = (int *)0x0;
        pbVar10 = local_14;
        do {
          bVar2 = *pbVar10;
          local_18 = (int *)((int)local_18 + (uint)bVar2);
          pbVar10 = pbVar10 + 1;
        } while (bVar2 != 0);
        for (pvVar3 = *(void **)(local_10[1] + 0xc + ((uint)local_18 & 0x1ff) * 4);
            pvVar3 != (void *)0x0; pvVar3 = *(void **)((int)pvVar3 + 8)) {
          iVar4 = sub_21103430(pvVar3,(int *)&local_1f4);
          if (iVar4 != 0) {
            if (pvVar3 != (void *)0x0) {
              **local_8 = *(int *)((int)pvVar3 + 0x124);
              goto LAB_21104403;
            }
            break;
          }
        }
        if (piVar13 == (int *)0x0) {
          **local_8 = 0;
        }
        else {
          **local_8 = -1;
        }
LAB_21104403:
        ppiVar9 = local_8 + 4;
        local_c = local_c + -1;
        local_8 = ppiVar9;
      } while (local_c != 0);
      if (*local_20 == 0) {
        _AAL_CloseFilterProvider_4(param_1);
        return (LPVOID)0x0;
      }
      iVar5 = (*(code *)*local_1c)
                        (DAT_211155ac,*(undefined4 *)(DAT_211155ac + 0x60),
                         *(undefined4 *)(DAT_211155ac + 0x5c));
      *(int *)((int)local_24 + 0x38) = iVar5;
      iVar4 = DAT_211155ac;
      if (iVar5 != 0) {
        *(uint *)((int)local_24 + 0x34) = param_1;
        *(int *)((int)local_24 + 0x30) = iVar4;
        *(undefined4 *)((int)local_24 + 0x3c) = *(undefined4 *)(DAT_211155ac + 4);
        *(void **)(DAT_211155ac + 4) = local_24;
        return local_24;
      }
      if (local_24 != (LPVOID)0x0) {
        sub_2110D4F4(local_24);
        return (LPVOID)0x0;
      }
    }
  }
  return (LPVOID)0x0;
}

