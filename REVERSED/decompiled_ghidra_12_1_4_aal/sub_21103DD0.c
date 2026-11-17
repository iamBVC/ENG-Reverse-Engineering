/* _AAL_EnumerateFilterProviders@12 @ 21103dd0   640 bytes */

undefined4 _AAL_EnumerateFilterProviders_12(uint *param_1,undefined4 **param_2,undefined4 *param_3)

{
  char cVar1;
  byte bVar2;
  undefined4 *puVar3;
  undefined4 **ppuVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  char *pcVar12;
  char *pcVar13;
  uint **ppuVar14;
  uint **ppuVar15;
  bool bVar16;
  byte local_148 [128];
  byte local_c8 [128];
  uint **local_48;
  undefined4 local_3c;
  undefined1 *local_38;
  uint **local_34;
  undefined4 local_30;
  undefined4 local_2c;
  char *local_28;
  code **local_24;
  undefined4 local_20;
  uint local_1c;
  void *local_18;
  uint **local_14;
  byte *local_10;
  int local_c;
  code *local_8;
  
                    /* 0x3dd0  10  _AAL_EnumerateFilterProviders@12 */
  ppuVar4 = param_2;
  local_34 = &param_1;
  local_24 = &local_8;
  local_8 = (code *)0x0;
  local_3c = 1;
  local_38 = &DAT_211141e0;
  local_30 = 0;
  local_2c = 0;
  local_28 = s_ALP_query_attribute_211141cc;
  local_20 = 0;
  if (((DAT_211155ac == 0) || (DAT_211155b4 == (void *)0x0)) ||
     (iVar5 = sub_21109660(DAT_211155b4,s_AAL_filter_211140d8,param_1,(uint *)param_2), iVar5 == 0))
  {
    return 0;
  }
  puVar3 = *ppuVar4;
  local_18 = DAT_211155b4;
  uVar9 = 0xffffffff;
  pcVar12 = s_AAL_filter_211140d8;
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
  pbVar6 = local_148;
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
  param_2 = &local_34;
  local_10 = local_c8;
  local_c = 2;
  do {
    uVar9 = 0xffffffff;
    ppuVar14 = (uint **)param_2[-1];
    do {
      ppuVar15 = ppuVar14;
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      ppuVar15 = (uint **)((int)ppuVar14 + 1);
      cVar1 = *(char *)ppuVar14;
      ppuVar14 = ppuVar15;
    } while (cVar1 != '\0');
    ppuVar14 = (uint **)param_2[-2];
    uVar9 = ~uVar9;
    pbVar11 = (byte *)((int)ppuVar15 - uVar9);
    pbVar6 = local_c8;
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
    local_14 = ppuVar14;
    local_48 = ppuVar14;
    local_1c = 0;
    pbVar11 = local_10;
    do {
      bVar2 = *pbVar11;
      local_1c = local_1c + bVar2;
      pbVar11 = pbVar11 + 1;
    } while (bVar2 != 0);
    for (iVar5 = *(int *)(*(int *)((int)local_18 + 4) + 0xc + (local_1c & 0x1ff) * 4); iVar5 != 0;
        iVar5 = *(int *)(iVar5 + 8)) {
      if (local_148[0] == 0) {
        if ((ppuVar14 == *(uint ***)(iVar5 + 0x11c)) && (puVar3 == *(undefined4 **)(iVar5 + 0x18)))
        {
          pbVar11 = (byte *)(iVar5 + 0x9c);
          pbVar6 = local_c8;
          do {
            bVar2 = *pbVar6;
            bVar16 = bVar2 < *pbVar11;
            if (bVar2 != *pbVar11) {
LAB_21103f4b:
              iVar7 = (1 - (uint)bVar16) - (uint)(bVar16 != 0);
              goto joined_r0x21103fd7;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar6[1];
            bVar16 = bVar2 < pbVar11[1];
            if (bVar2 != pbVar11[1]) goto LAB_21103f4b;
            pbVar6 = pbVar6 + 2;
            pbVar11 = pbVar11 + 2;
          } while (bVar2 != 0);
          iVar7 = 0;
joined_r0x21103fd7:
          if (iVar7 == 0) {
            if (iVar5 != 0) {
              **param_2 = *(uint **)(iVar5 + 0x124);
              goto LAB_21104017;
            }
            break;
          }
        }
      }
      else if ((ppuVar14 == *(uint ***)(iVar5 + 0x11c)) &&
              (puVar3 == *(undefined4 **)(iVar5 + 0x18))) {
        pbVar11 = (byte *)(iVar5 + 0x1c);
        pbVar6 = local_148;
        do {
          bVar2 = *pbVar6;
          bVar16 = bVar2 < *pbVar11;
          if (bVar2 != *pbVar11) {
LAB_21103f97:
            iVar7 = (1 - (uint)bVar16) - (uint)(bVar16 != 0);
            goto LAB_21103f9c;
          }
          if (bVar2 == 0) break;
          bVar2 = pbVar6[1];
          bVar16 = bVar2 < pbVar11[1];
          if (bVar2 != pbVar11[1]) goto LAB_21103f97;
          pbVar6 = pbVar6 + 2;
          pbVar11 = pbVar11 + 2;
        } while (bVar2 != 0);
        iVar7 = 0;
LAB_21103f9c:
        if (iVar7 == 0) {
          pbVar11 = (byte *)(iVar5 + 0x9c);
          pbVar6 = local_c8;
          do {
            bVar2 = *pbVar6;
            bVar16 = bVar2 < *pbVar11;
            if (bVar2 != *pbVar11) {
LAB_21103fd0:
              iVar7 = (1 - (uint)bVar16) - (uint)(bVar16 != 0);
              goto joined_r0x21103fd7;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar6[1];
            bVar16 = bVar2 < pbVar11[1];
            if (bVar2 != pbVar11[1]) goto LAB_21103fd0;
            pbVar6 = pbVar6 + 2;
            pbVar11 = pbVar11 + 2;
          } while (bVar2 != 0);
          iVar7 = 0;
          goto joined_r0x21103fd7;
        }
      }
    }
    if (ppuVar14 == (uint **)0x0) {
      **param_2 = (uint *)0x0;
    }
    else {
      **param_2 = (uint *)0xffffffff;
    }
LAB_21104017:
    param_2 = param_2 + 4;
    local_c = local_c + -1;
    if (local_c == 0) {
      uVar8 = (*local_8)(param_1);
      *param_3 = uVar8;
      return 1;
    }
  } while( true );
}

