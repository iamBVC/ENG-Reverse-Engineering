/* _AAL_Open3DProvider@4 @ 211038d0   1044 bytes */

undefined4 _AAL_Open3DProvider_4(int param_1)

{
  char cVar1;
  byte bVar2;
  void *pvVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  char *pcVar11;
  char *pcVar12;
  bool bVar13;
  byte local_22c [128];
  byte local_1ac [128];
  void *local_12c;
  undefined4 local_120;
  char *local_11c;
  void *local_118;
  undefined4 local_114;
  undefined4 local_110;
  char *local_10c;
  int local_108;
  undefined4 local_104;
  undefined4 local_100;
  char *local_fc;
  int local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  char *local_ec;
  int local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  char *local_dc;
  int local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  char *local_cc;
  int local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  char *local_bc;
  undefined4 *local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  char *local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  char *local_9c;
  int local_98;
  undefined4 local_94;
  undefined4 local_90;
  char *local_8c;
  int local_88;
  undefined4 local_84;
  undefined4 local_80;
  char *local_7c;
  int local_78;
  undefined4 local_74;
  undefined4 local_70;
  char *local_6c;
  int local_68;
  undefined4 local_64;
  undefined4 local_60;
  char *local_5c;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  char *local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  char *local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  char *local_2c;
  int local_28;
  undefined4 local_24;
  byte *local_20;
  int *local_1c;
  undefined4 *local_18;
  void *local_14;
  uint local_10;
  int local_c;
  void **local_8;
  
                    /* 0x38d0  48  _AAL_Open3DProvider@4 */
  if (DAT_211155b4 == (int *)0x0) {
    return 1;
  }
  local_118 = operator_new(0x44);
  if (param_1 != 0) {
    *(void **)(param_1 * 0x30 + 0x10 + *(int *)(*DAT_211155b4 + 0xc)) = local_118;
  }
  local_108 = (int)local_118 + 4;
  local_f8 = (int)local_118 + 8;
  local_e8 = (int)local_118 + 0xc;
  local_d8 = (int)local_118 + 0x10;
  local_c8 = (int)local_118 + 0x14;
  local_18 = (undefined4 *)((int)local_118 + 0x1c);
  local_b8 = (undefined4 *)((int)local_118 + 0x1c);
  local_a8 = (int)local_118 + 0x20;
  local_98 = (int)local_118 + 0x24;
  local_88 = (int)local_118 + 0x2c;
  local_78 = (int)local_118 + 0x30;
  local_68 = (int)local_118 + 0x34;
  local_58 = (int)local_118 + 0x38;
  local_48 = (int)local_118 + 0x28;
  local_28 = (int)local_118 + 0x40;
  local_120 = 0;
  local_11c = s_ALP_query_attribute_211141cc;
  local_114 = 0;
  local_110 = 0;
  local_10c = s_ALP_get_guid_211142a4;
  local_104 = 0;
  local_100 = 0;
  local_fc = s_AL3D_init_211140ec;
  local_f4 = 0;
  local_f0 = 0;
  local_ec = s_AL3D_shutdown_21114184;
  local_e4 = 0;
  local_e0 = 0;
  local_dc = s_AL3D_Set3DAttributes_2111428c;
  local_d4 = 0;
  local_d0 = 0;
  local_cc = s_AL3D_Get3DAttributes_21114274;
  local_c4 = 0;
  local_c0 = 0;
  local_bc = s_AL3D_Activate_21114264;
  local_b4 = 0;
  local_b0 = 0;
  local_ac = s_AL3D_AllocateVoice_21114250;
  local_a4 = 0;
  local_a0 = 0;
  local_9c = s_AL3D_FreeVoice_21114240;
  local_94 = 0;
  local_90 = 0;
  local_8c = s_AL3D_Start_21114234;
  local_84 = 0;
  local_80 = 0;
  local_7c = s_AL3D_Stop_21114228;
  local_74 = 0;
  local_70 = 0;
  local_6c = s_AL3D_Resume_2111421c;
  local_64 = 0;
  local_60 = 0;
  local_5c = s_AL3D_End_21114210;
  local_54 = 0;
  local_50 = 0;
  local_4c = s_AL3D_DestroyVoiceFile_211141b4;
  local_44 = 0;
  local_40 = 0;
  local_3c = s_AL3D_SetAttributes_211141fc;
  local_38 = (int)local_118 + 0x3c;
  local_34 = 0;
  local_30 = 0;
  local_2c = s_AL3D_GetAttributes_211141e8;
  local_24 = 0;
  uVar8 = 0xffffffff;
  local_1c = DAT_211155b4;
  pcVar11 = &DAT_211140f8;
  do {
    pcVar12 = pcVar11;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar11 + 1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar12;
  } while (cVar1 != '\0');
  uVar8 = ~uVar8;
  pbVar10 = (byte *)(pcVar12 + -uVar8);
  pbVar5 = local_22c;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pbVar5 = *(undefined4 *)pbVar10;
    pbVar10 = pbVar10 + 4;
    pbVar5 = pbVar5 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pbVar5 = *pbVar10;
    pbVar10 = pbVar10 + 1;
    pbVar5 = pbVar5 + 1;
  }
  local_8 = &local_118;
  local_20 = local_1ac;
  local_c = 0x10;
  do {
    uVar8 = 0xffffffff;
    pcVar11 = local_8[-1];
    do {
      pcVar12 = pcVar11;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      pcVar12 = pcVar11 + 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar12;
    } while (cVar1 != '\0');
    pvVar3 = local_8[-2];
    uVar8 = ~uVar8;
    pbVar10 = (byte *)(pcVar12 + -uVar8);
    pbVar5 = local_1ac;
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pbVar5 = *(undefined4 *)pbVar10;
      pbVar10 = pbVar10 + 4;
      pbVar5 = pbVar5 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pbVar5 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      pbVar5 = pbVar5 + 1;
    }
    local_14 = pvVar3;
    local_12c = pvVar3;
    local_10 = 0;
    pbVar10 = local_20;
    do {
      bVar2 = *pbVar10;
      local_10 = local_10 + bVar2;
      pbVar10 = pbVar10 + 1;
    } while (bVar2 != 0);
    for (iVar4 = *(int *)(local_1c[1] + 0xc + (local_10 & 0x1ff) * 4); iVar4 != 0;
        iVar4 = *(int *)(iVar4 + 8)) {
      if (local_22c[0] == 0) {
        if ((pvVar3 == *(void **)(iVar4 + 0x11c)) && (param_1 == *(int *)(iVar4 + 0x18))) {
          pbVar10 = (byte *)(iVar4 + 0x9c);
          pbVar5 = local_1ac;
          do {
            bVar2 = *pbVar5;
            bVar13 = bVar2 < *pbVar10;
            if (bVar2 != *pbVar10) {
LAB_21103bde:
              iVar6 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
              goto joined_r0x21103c6a;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar5[1];
            bVar13 = bVar2 < pbVar10[1];
            if (bVar2 != pbVar10[1]) goto LAB_21103bde;
            pbVar5 = pbVar5 + 2;
            pbVar10 = pbVar10 + 2;
          } while (bVar2 != 0);
          iVar6 = 0;
joined_r0x21103c6a:
          if (iVar6 == 0) {
            if (iVar4 != 0) {
              *(undefined4 *)*local_8 = *(undefined4 *)(iVar4 + 0x124);
              goto LAB_21103caa;
            }
            break;
          }
        }
      }
      else if ((pvVar3 == *(void **)(iVar4 + 0x11c)) && (param_1 == *(int *)(iVar4 + 0x18))) {
        pbVar10 = (byte *)(iVar4 + 0x1c);
        pbVar5 = local_22c;
        do {
          bVar2 = *pbVar5;
          bVar13 = bVar2 < *pbVar10;
          if (bVar2 != *pbVar10) {
LAB_21103c2a:
            iVar6 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
            goto LAB_21103c2f;
          }
          if (bVar2 == 0) break;
          bVar2 = pbVar5[1];
          bVar13 = bVar2 < pbVar10[1];
          if (bVar2 != pbVar10[1]) goto LAB_21103c2a;
          pbVar5 = pbVar5 + 2;
          pbVar10 = pbVar10 + 2;
        } while (bVar2 != 0);
        iVar6 = 0;
LAB_21103c2f:
        if (iVar6 == 0) {
          pbVar10 = (byte *)(iVar4 + 0x9c);
          pbVar5 = local_1ac;
          do {
            bVar2 = *pbVar5;
            bVar13 = bVar2 < *pbVar10;
            if (bVar2 != *pbVar10) {
LAB_21103c63:
              iVar6 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
              goto joined_r0x21103c6a;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar5[1];
            bVar13 = bVar2 < pbVar10[1];
            if (bVar2 != pbVar10[1]) goto LAB_21103c63;
            pbVar5 = pbVar5 + 2;
            pbVar10 = pbVar10 + 2;
          } while (bVar2 != 0);
          iVar6 = 0;
          goto joined_r0x21103c6a;
        }
      }
    }
    if (pvVar3 == (void *)0x0) {
      *(undefined4 *)*local_8 = 0;
    }
    else {
      *(undefined4 *)*local_8 = 0xffffffff;
    }
LAB_21103caa:
    local_8 = local_8 + 4;
    local_c = local_c + -1;
    if (local_c == 0) {
      if ((code *)*local_18 == (code *)0x0) {
        return 1;
      }
      uVar7 = (*(code *)*local_18)(param_1);
      return uVar7;
    }
  } while( true );
}

