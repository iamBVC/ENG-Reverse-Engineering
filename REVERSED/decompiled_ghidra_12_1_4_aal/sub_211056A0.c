/* sub_211056A0 @ 211056a0   1030 bytes */

int __thiscall sub_211056A0(void *this,int param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  int *piVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  int iVar10;
  char *pcVar11;
  char *pcVar12;
  byte *pbVar13;
  bool bVar14;
  byte local_118 [128];
  byte local_98 [128];
  undefined4 local_18;
  int local_c;
  byte *local_8;
  
  if (param_1 == 5) {
    iVar10 = 0;
  }
  else {
    iVar10 = param_1;
    if (param_1 == 1) {
      iVar10 = *(int *)(*(int *)((int)this + 0xb0) + 0x28);
      *(int *)(*(int *)((int)this + 0xb0) + 0x28) = param_2;
      return iVar10;
    }
  }
  iVar8 = iVar10 * 0x24;
  do {
    piVar3 = (int *)(iVar8 + *(int *)((int)this + 0xb0));
    if (*piVar3 != 0) {
      *piVar3 = 0;
    }
    if (param_1 != 5) break;
    iVar8 = iVar8 + 0x24;
    iVar10 = iVar10 + 1;
  } while (iVar8 < 0x90);
  if (param_2 == 0) {
    return 0;
  }
  iVar8 = piVar3[1];
  local_c = iVar8;
  piVar3[1] = param_2;
  if (iVar10 == 0) {
    uVar6 = 0xffffffff;
    pcVar11 = s_AAL_Mixer_21114134;
    do {
      pcVar12 = pcVar11;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar12 = pcVar11 + 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar12;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pbVar9 = (byte *)(pcVar12 + -uVar6);
    pbVar4 = local_118;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pbVar4 = *(undefined4 *)pbVar9;
      pbVar9 = pbVar9 + 4;
      pbVar4 = pbVar4 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pbVar4 = *pbVar9;
      pbVar9 = pbVar9 + 1;
      pbVar4 = pbVar4 + 1;
    }
    pbVar9 = local_98;
    local_8 = pbVar9;
    uVar6 = 0xffffffff;
    pcVar11 = s_MIXER_flush_211144bc;
    do {
      pcVar12 = pcVar11;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar12 = pcVar11 + 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar12;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pbVar4 = (byte *)(pcVar12 + -uVar6);
    pbVar13 = local_98;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pbVar13 = *(undefined4 *)pbVar4;
      pbVar4 = pbVar4 + 4;
      pbVar13 = pbVar13 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pbVar13 = *pbVar4;
      pbVar4 = pbVar4 + 1;
      pbVar13 = pbVar13 + 1;
    }
    local_18 = 0;
    uVar6 = 0;
    do {
      bVar2 = *pbVar9;
      uVar6 = uVar6 + bVar2;
      pbVar9 = pbVar9 + 1;
    } while (bVar2 != 0);
    for (iVar10 = *(int *)(*(int *)(DAT_211155b4 + 4) + 0xc + (uVar6 & 0x1ff) * 4); iVar10 != 0;
        iVar10 = *(int *)(iVar10 + 8)) {
      if (local_118[0] == 0) {
        if ((*(int *)(iVar10 + 0x11c) == 0) && (param_2 == *(int *)(iVar10 + 0x18))) {
          pbVar9 = (byte *)(iVar10 + 0x9c);
          pbVar4 = local_98;
          do {
            bVar2 = *pbVar4;
            bVar14 = bVar2 < *pbVar9;
            if (bVar2 != *pbVar9) {
LAB_211059db:
              iVar5 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
              goto joined_r0x21105a67;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar4[1];
            bVar14 = bVar2 < pbVar9[1];
            if (bVar2 != pbVar9[1]) goto LAB_211059db;
            pbVar4 = pbVar4 + 2;
            pbVar9 = pbVar9 + 2;
          } while (bVar2 != 0);
          iVar5 = 0;
joined_r0x21105a67:
          if (iVar5 == 0) {
            if (iVar10 != 0) {
              piVar3[2] = *(int *)(iVar10 + 0x124);
              goto LAB_21105a91;
            }
            break;
          }
        }
      }
      else if ((*(int *)(iVar10 + 0x11c) == 0) && (param_2 == *(int *)(iVar10 + 0x18))) {
        pbVar9 = (byte *)(iVar10 + 0x1c);
        pbVar4 = local_118;
        do {
          bVar2 = *pbVar4;
          bVar14 = bVar2 < *pbVar9;
          if (bVar2 != *pbVar9) {
LAB_21105a27:
            iVar5 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
            goto LAB_21105a2c;
          }
          if (bVar2 == 0) break;
          bVar2 = pbVar4[1];
          bVar14 = bVar2 < pbVar9[1];
          if (bVar2 != pbVar9[1]) goto LAB_21105a27;
          pbVar4 = pbVar4 + 2;
          pbVar9 = pbVar9 + 2;
        } while (bVar2 != 0);
        iVar5 = 0;
LAB_21105a2c:
        if (iVar5 == 0) {
          pbVar9 = (byte *)(iVar10 + 0x9c);
          pbVar4 = local_98;
          do {
            bVar2 = *pbVar4;
            bVar14 = bVar2 < *pbVar9;
            if (bVar2 != *pbVar9) {
LAB_21105a60:
              iVar5 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
              goto joined_r0x21105a67;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar4[1];
            bVar14 = bVar2 < pbVar9[1];
            if (bVar2 != pbVar9[1]) goto LAB_21105a60;
            pbVar4 = pbVar4 + 2;
            pbVar9 = pbVar9 + 2;
          } while (bVar2 != 0);
          iVar5 = 0;
          goto joined_r0x21105a67;
        }
      }
    }
    piVar3[2] = 0;
  }
  else {
    if (iVar10 != 3) {
      return iVar8;
    }
    uVar6 = 0xffffffff;
    pcVar11 = s_AAL_Mixer_21114134;
    do {
      pcVar12 = pcVar11;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar12 = pcVar11 + 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar12;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pbVar9 = (byte *)(pcVar12 + -uVar6);
    pbVar4 = local_118;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pbVar4 = *(undefined4 *)pbVar9;
      pbVar9 = pbVar9 + 4;
      pbVar4 = pbVar4 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pbVar4 = *pbVar9;
      pbVar9 = pbVar9 + 1;
      pbVar4 = pbVar4 + 1;
    }
    pbVar9 = local_98;
    local_8 = pbVar9;
    uVar6 = 0xffffffff;
    pcVar11 = s_MIXER_copy_211144c8;
    do {
      pcVar12 = pcVar11;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar12 = pcVar11 + 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar12;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pbVar4 = (byte *)(pcVar12 + -uVar6);
    pbVar13 = local_98;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pbVar13 = *(undefined4 *)pbVar4;
      pbVar4 = pbVar4 + 4;
      pbVar13 = pbVar13 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pbVar13 = *pbVar4;
      pbVar4 = pbVar4 + 1;
      pbVar13 = pbVar13 + 1;
    }
    local_18 = 0;
    uVar6 = 0;
    do {
      bVar2 = *pbVar9;
      uVar6 = uVar6 + bVar2;
      pbVar9 = pbVar9 + 1;
    } while (bVar2 != 0);
    for (iVar10 = *(int *)(*(int *)(DAT_211155b4 + 4) + 0xc + (uVar6 & 0x1ff) * 4); iVar10 != 0;
        iVar10 = *(int *)(iVar10 + 8)) {
      if (local_118[0] == 0) {
        if ((*(int *)(iVar10 + 0x11c) == 0) && (param_2 == *(int *)(iVar10 + 0x18))) {
          pbVar9 = (byte *)(iVar10 + 0x9c);
          pbVar4 = local_98;
          do {
            bVar2 = *pbVar4;
            bVar14 = bVar2 < *pbVar9;
            if (bVar2 != *pbVar9) {
LAB_2110582b:
              iVar5 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
              goto joined_r0x211058b0;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar4[1];
            bVar14 = bVar2 < pbVar9[1];
            if (bVar2 != pbVar9[1]) goto LAB_2110582b;
            pbVar4 = pbVar4 + 2;
            pbVar9 = pbVar9 + 2;
          } while (bVar2 != 0);
          iVar5 = 0;
joined_r0x211058b0:
          if (iVar5 == 0) {
            if (iVar10 != 0) {
              piVar3[4] = *(int *)(iVar10 + 0x124);
              goto LAB_21105a91;
            }
            break;
          }
        }
      }
      else if ((*(int *)(iVar10 + 0x11c) == 0) && (param_2 == *(int *)(iVar10 + 0x18))) {
        pbVar9 = (byte *)(iVar10 + 0x1c);
        pbVar4 = local_118;
        do {
          bVar2 = *pbVar4;
          bVar14 = bVar2 < *pbVar9;
          if (bVar2 != *pbVar9) {
LAB_21105870:
            iVar5 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
            goto LAB_21105875;
          }
          if (bVar2 == 0) break;
          bVar2 = pbVar4[1];
          bVar14 = bVar2 < pbVar9[1];
          if (bVar2 != pbVar9[1]) goto LAB_21105870;
          pbVar4 = pbVar4 + 2;
          pbVar9 = pbVar9 + 2;
        } while (bVar2 != 0);
        iVar5 = 0;
LAB_21105875:
        if (iVar5 == 0) {
          pbVar9 = (byte *)(iVar10 + 0x9c);
          pbVar4 = local_98;
          do {
            bVar2 = *pbVar4;
            bVar14 = bVar2 < *pbVar9;
            if (bVar2 != *pbVar9) {
LAB_211058a9:
              iVar5 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
              goto joined_r0x211058b0;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar4[1];
            bVar14 = bVar2 < pbVar9[1];
            if (bVar2 != pbVar9[1]) goto LAB_211058a9;
            pbVar4 = pbVar4 + 2;
            pbVar9 = pbVar9 + 2;
          } while (bVar2 != 0);
          iVar5 = 0;
          goto joined_r0x211058b0;
        }
      }
    }
    piVar3[4] = 0;
  }
LAB_21105a91:
  *piVar3 = 1;
  return iVar8;
}

