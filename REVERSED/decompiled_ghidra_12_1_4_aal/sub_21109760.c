/* sub_21109760 @ 21109760   721 bytes */

undefined4 __thiscall sub_21109760(void *this,LPCSTR param_1,char *param_2,LPCSTR param_3)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  LPCSTR pCVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  LPCSTR pCVar11;
  char *pcVar12;
  char *pcVar13;
  bool bVar14;
  byte local_128 [128];
  byte local_a8 [128];
  int local_28;
  uint local_1c;
  int local_18;
  void *local_14;
  code *local_10;
  byte *local_c;
  int local_8;
  
  iVar7 = *(int *)(*(int *)((int)this + 4) + 0xc);
  local_18 = 0xc;
  local_14 = this;
joined_r0x21109787:
  while( true ) {
    while (iVar7 == 0) {
      iVar7 = *(int *)(*(int *)((int)this + 4) + 4 + local_18);
      local_18 = local_18 + 4;
      if (0x80b < local_18) {
        return 0;
      }
    }
    if (*(int *)(iVar7 + 0x11c) != 0) break;
    local_8 = iVar7;
    iVar3 = lstrcmpA((LPCSTR)(iVar7 + 0x1c),param_1);
    if ((iVar3 != 0) ||
       (iVar3 = lstrcmpA((LPCSTR)(iVar7 + 0x9c),s_ALP_query_attribute_211141cc), iVar3 != 0)) break;
    iVar3 = *(int *)(iVar7 + 0x18);
    uVar8 = 0xffffffff;
    local_10 = *(code **)(iVar7 + 0x124);
    pCVar6 = (LPCSTR)(iVar7 + 0x1c);
    do {
      pCVar11 = pCVar6;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      pCVar11 = pCVar6 + 1;
      cVar1 = *pCVar6;
      pCVar6 = pCVar11;
    } while (cVar1 != '\0');
    uVar8 = ~uVar8;
    local_28 = 1;
    pbVar10 = (byte *)(pCVar11 + -uVar8);
    pbVar4 = local_128;
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pbVar4 = *(undefined4 *)pbVar10;
      pbVar10 = pbVar10 + 4;
      pbVar4 = pbVar4 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pbVar4 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      pbVar4 = pbVar4 + 1;
    }
    uVar8 = 0xffffffff;
    pcVar12 = param_2;
    do {
      pcVar13 = pcVar12;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      pcVar13 = pcVar12 + 1;
      cVar1 = *pcVar12;
      pcVar12 = pcVar13;
    } while (cVar1 != '\0');
    uVar8 = ~uVar8;
    pbVar10 = (byte *)(pcVar13 + -uVar8);
    pbVar4 = local_a8;
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pbVar4 = *(undefined4 *)pbVar10;
      pbVar10 = pbVar10 + 4;
      pbVar4 = pbVar4 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pbVar4 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      pbVar4 = pbVar4 + 1;
    }
    pbVar10 = local_a8;
    local_c = pbVar10;
    local_1c = 0;
    do {
      bVar2 = *pbVar10;
      local_1c = local_1c + bVar2;
      pbVar10 = pbVar10 + 1;
    } while (bVar2 != 0);
    for (iVar7 = *(int *)(*(int *)((int)local_14 + 4) + 0xc + (local_1c & 0x1ff) * 4); iVar7 != 0;
        iVar7 = *(int *)(iVar7 + 8)) {
      if (local_128[0] == 0) {
        if ((local_28 == *(int *)(iVar7 + 0x11c)) && (iVar3 == *(int *)(iVar7 + 0x18))) {
          pbVar10 = (byte *)(iVar7 + 0x9c);
          pbVar4 = local_a8;
          do {
            bVar2 = *pbVar4;
            bVar14 = bVar2 < *pbVar10;
            if (bVar2 != *pbVar10) {
LAB_211098ca:
              iVar5 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
              goto joined_r0x21109952;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar4[1];
            bVar14 = bVar2 < pbVar10[1];
            if (bVar2 != pbVar10[1]) goto LAB_211098ca;
            pbVar4 = pbVar4 + 2;
            pbVar10 = pbVar10 + 2;
          } while (bVar2 != 0);
          iVar5 = 0;
joined_r0x21109952:
          if (iVar5 == 0) {
            if (iVar7 != 0) {
              pCVar6 = (LPCSTR)(*local_10)(*(undefined4 *)(iVar7 + 0x124));
              iVar7 = lstrlenA(param_3);
              goto joined_r0x21109987;
            }
            break;
          }
        }
      }
      else if ((local_28 == *(int *)(iVar7 + 0x11c)) && (iVar3 == *(int *)(iVar7 + 0x18))) {
        pbVar10 = (byte *)(iVar7 + 0x1c);
        pbVar4 = local_128;
        do {
          bVar2 = *pbVar4;
          bVar14 = bVar2 < *pbVar10;
          if (bVar2 != *pbVar10) {
LAB_21109912:
            iVar5 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
            goto LAB_21109917;
          }
          if (bVar2 == 0) break;
          bVar2 = pbVar4[1];
          bVar14 = bVar2 < pbVar10[1];
          if (bVar2 != pbVar10[1]) goto LAB_21109912;
          pbVar4 = pbVar4 + 2;
          pbVar10 = pbVar10 + 2;
        } while (bVar2 != 0);
        iVar5 = 0;
LAB_21109917:
        if (iVar5 == 0) {
          pbVar10 = (byte *)(iVar7 + 0x9c);
          pbVar4 = local_a8;
          do {
            bVar2 = *pbVar4;
            bVar14 = bVar2 < *pbVar10;
            if (bVar2 != *pbVar10) {
LAB_2110994b:
              iVar5 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
              goto joined_r0x21109952;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar4[1];
            bVar14 = bVar2 < pbVar10[1];
            if (bVar2 != pbVar10[1]) goto LAB_2110994b;
            pbVar4 = pbVar4 + 2;
            pbVar10 = pbVar10 + 2;
          } while (bVar2 != 0);
          iVar5 = 0;
          goto joined_r0x21109952;
        }
      }
    }
    iVar7 = *(int *)(local_8 + 8);
    this = local_14;
  }
  goto LAB_211099da;
  while (param_3[iVar7] != '.') {
joined_r0x21109987:
    iVar7 = iVar7 + -1;
    if (iVar7 < 1) break;
  }
  local_c = (byte *)(param_3 + iVar7);
  local_10 = (code *)lstrlenA((LPCSTR)local_c);
  do {
    iVar7 = lstrlenA(pCVar6);
    pCVar11 = pCVar6 + iVar7 + 1;
    iVar3 = lstrlenA(pCVar11);
    iVar7 = local_8;
    if (iVar3 == 0) break;
    if (((int)local_10 <= iVar3) &&
       (iVar7 = lstrcmpiA(pCVar11 + (iVar3 - (int)local_10),(LPCSTR)local_c), iVar7 == 0)) {
      return *(undefined4 *)(local_8 + 0x18);
    }
    pCVar6 = pCVar11 + iVar3 + 1;
    iVar7 = local_8;
  } while (pCVar11[iVar3 + 1] != '\0');
LAB_211099da:
  iVar7 = *(int *)(iVar7 + 8);
  this = local_14;
  goto joined_r0x21109787;
}

