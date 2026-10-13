/* Original intro uploader with verified native Lock/Unlock ABIs. */

void sub_43B080(int *param_1,int param_2,byte *param_3,uint param_4,int param_5)

{
  byte *pbVar1;
  byte *pbVar2;
  byte bVar3;
  int iVar4;
  byte bVar5;
  char cVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  undefined4 uVar10;
  uint uVar11;
  int iVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  byte bVar16;
  byte *pbVar17;
  uint uStack_18;
  uint uStack_c;
  uint uStack_8;
  
  (**(groove_com5 **)(*param_1 + 100))((int)param_1,0,param_2,1,0);
  (**(groove_com2 **)(*param_1 + 0x80))((int)param_1,0);
  uVar10 = sub_43B010(*(undefined4 *)(param_2 + 0x58));
  bVar5 = sub_43B030(uVar10);
  cVar6 = sub_43B060(*(undefined4 *)(param_2 + 0x58));
  bVar13 = 0x1f - cVar6;
  uVar10 = sub_43B010(*(undefined4 *)(param_2 + 0x5c));
  bVar7 = sub_43B030(uVar10);
  cVar6 = sub_43B060(*(undefined4 *)(param_2 + 0x5c));
  bVar14 = 0x1f - cVar6;
  uVar10 = sub_43B010(*(undefined4 *)(param_2 + 0x60));
  bVar8 = sub_43B030(uVar10);
  cVar6 = sub_43B060(*(undefined4 *)(param_2 + 0x60));
  bVar15 = 0x1f - cVar6;
  uVar10 = sub_43B010(*(undefined4 *)(param_2 + 100));
  bVar9 = sub_43B030(uVar10);
  cVar6 = sub_43B060(*(undefined4 *)(param_2 + 100));
  bVar16 = 0x1f - cVar6;
  (**(groove_com5 **)(*param_1 + 100))((int)param_1,0,param_2,1,0);
  if (param_5 == 4) {
    if (*(int *)(param_2 + 0x54) == 0x20) {
      iVar4 = *(int *)(param_2 + 0x24);
      uStack_18 = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uStack_8 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar3 = *param_3;
              pbVar1 = param_3 + 1;
              pbVar17 = param_3 + 2;
              pbVar2 = param_3 + 3;
              param_3 = param_3 + 4;
              uVar11 = ((uint)(*pbVar2 & bVar9) << 0x18) >> (bVar16 & 0x1f) |
                       ((uint)(*pbVar17 & bVar8) << 0x18) >> (bVar15 & 0x1f) |
                       ((uint)(*pbVar1 & bVar7) << 0x18) >> (bVar14 & 0x1f) |
                       ((uint)(bVar3 & bVar5) << 0x18) >> (bVar13 & 0x1f);
              if (uVar11 == 0) {
                uVar11 = param_4;
              }
              iVar12 = uStack_18 * *(int *)(param_2 + 0x10);
              iVar12 = ((int)((iVar12 >> 0x1f & 3U) + iVar12) >> 2) + uStack_8;
              uStack_8 = uStack_8 + 1;
              *(uint *)(iVar4 + iVar12 * 4) = uVar11;
            } while (uStack_8 < *(uint *)(param_2 + 0xc));
          }
          uStack_18 = uStack_18 + 1;
        } while (uStack_18 < *(uint *)(param_2 + 8));
      }
    }
    if (*(int *)(param_2 + 0x54) == 0x18) {
      iVar4 = *(int *)(param_2 + 0x24);
      uStack_18 = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uStack_8 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar3 = *param_3;
              pbVar1 = param_3 + 1;
              pbVar17 = param_3 + 2;
              pbVar2 = param_3 + 3;
              param_3 = param_3 + 4;
              uVar11 = ((uint)(*pbVar2 & bVar9) << 0x18) >> (bVar16 & 0x1f) |
                       ((uint)(*pbVar17 & bVar8) << 0x18) >> (bVar15 & 0x1f) |
                       ((uint)(*pbVar1 & bVar7) << 0x18) >> (bVar14 & 0x1f) |
                       ((uint)(bVar3 & bVar5) << 0x18) >> (bVar13 & 0x1f);
              if (uVar11 == 0) {
                uVar11 = param_4;
              }
              iVar12 = uStack_18 * *(int *)(param_2 + 0x10);
              iVar12 = ((int)((iVar12 >> 0x1f & 3U) + iVar12) >> 2) + uStack_8;
              uStack_8 = uStack_8 + 1;
              *(uint *)(iVar4 + iVar12 * 4) = uVar11;
            } while (uStack_8 < *(uint *)(param_2 + 0xc));
          }
          uStack_18 = uStack_18 + 1;
        } while (uStack_18 < *(uint *)(param_2 + 8));
      }
    }
    if (*(int *)(param_2 + 0x54) == 0x10) {
      iVar4 = *(int *)(param_2 + 0x24);
      uStack_18 = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uStack_8 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar3 = *param_3;
              pbVar1 = param_3 + 1;
              pbVar17 = param_3 + 2;
              pbVar2 = param_3 + 3;
              param_3 = param_3 + 4;
              uVar11 = ((uint)(*pbVar2 & bVar9) << 0x18) >> (bVar16 & 0x1f) |
                       ((uint)(*pbVar17 & bVar8) << 0x18) >> (bVar15 & 0x1f) |
                       ((uint)(*pbVar1 & bVar7) << 0x18) >> (bVar14 & 0x1f) |
                       ((uint)(bVar3 & bVar5) << 0x18) >> (bVar13 & 0x1f);
              if (uVar11 == 0) {
                uVar11 = param_4;
              }
              iVar12 = (int)(uStack_18 * *(int *)(param_2 + 0x10)) / 2 + uStack_8;
              uStack_8 = uStack_8 + 1;
              *(short *)(iVar4 + iVar12 * 2) = (short)uVar11;
            } while (uStack_8 < *(uint *)(param_2 + 0xc));
          }
          uStack_18 = uStack_18 + 1;
        } while (uStack_18 < *(uint *)(param_2 + 8));
      }
    }
  }
  else {
    if (*(int *)(param_2 + 0x54) == 0x20) {
      iVar4 = *(int *)(param_2 + 0x24);
      uStack_c = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uStack_8 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar9 = *param_3;
              pbVar1 = param_3 + 1;
              pbVar17 = param_3 + 2;
              param_3 = param_3 + 3;
              uVar11 = ((uint)(*pbVar17 & bVar8) << 0x18) >> (bVar15 & 0x1f) |
                       ((uint)(*pbVar1 & bVar7) << 0x18) >> (bVar14 & 0x1f) |
                       ((uint)(bVar9 & bVar5) << 0x18) >> (bVar13 & 0x1f);
              if (uVar11 == 0) {
                uVar11 = param_4;
              }
              iVar12 = uStack_c * *(int *)(param_2 + 0x10);
              iVar12 = ((int)((iVar12 >> 0x1f & 3U) + iVar12) >> 2) + uStack_8;
              uStack_8 = uStack_8 + 1;
              *(uint *)(iVar4 + iVar12 * 4) = uVar11;
            } while (uStack_8 < *(uint *)(param_2 + 0xc));
          }
          uStack_c = uStack_c + 1;
        } while (uStack_c < *(uint *)(param_2 + 8));
      }
    }
    if (*(int *)(param_2 + 0x54) == 0x18) {
      iVar4 = *(int *)(param_2 + 0x24);
      uStack_c = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uStack_8 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar9 = *param_3;
              pbVar1 = param_3 + 1;
              pbVar17 = param_3 + 2;
              param_3 = param_3 + 3;
              uVar11 = ((uint)(*pbVar17 & bVar8) << 0x18) >> (bVar15 & 0x1f) |
                       ((uint)(*pbVar1 & bVar7) << 0x18) >> (bVar14 & 0x1f) |
                       ((uint)(bVar9 & bVar5) << 0x18) >> (bVar13 & 0x1f);
              if (uVar11 == 0) {
                uVar11 = param_4;
              }
              iVar12 = uStack_c * *(int *)(param_2 + 0x10);
              iVar12 = ((int)((iVar12 >> 0x1f & 3U) + iVar12) >> 2) + uStack_8;
              uStack_8 = uStack_8 + 1;
              *(uint *)(iVar4 + iVar12 * 4) = uVar11;
            } while (uStack_8 < *(uint *)(param_2 + 0xc));
          }
          uStack_c = uStack_c + 1;
        } while (uStack_c < *(uint *)(param_2 + 8));
      }
    }
    if (*(int *)(param_2 + 0x54) == 0x10) {
      iVar4 = *(int *)(param_2 + 0x24);
      uStack_c = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uStack_8 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar9 = *param_3;
              pbVar1 = param_3 + 1;
              pbVar17 = param_3 + 2;
              param_3 = param_3 + 3;
              uVar11 = ((uint)(*pbVar17 & bVar8) << 0x18) >> (bVar15 & 0x1f) |
                       ((uint)(*pbVar1 & bVar7) << 0x18) >> (bVar14 & 0x1f) |
                       ((uint)(bVar9 & bVar5) << 0x18) >> (bVar13 & 0x1f);
              if (uVar11 == 0) {
                uVar11 = param_4;
              }
              iVar12 = (int)(uStack_c * *(int *)(param_2 + 0x10)) / 2 + uStack_8;
              uStack_8 = uStack_8 + 1;
              *(short *)(iVar4 + iVar12 * 2) = (short)uVar11;
            } while (uStack_8 < *(uint *)(param_2 + 0xc));
          }
          uStack_c = uStack_c + 1;
        } while (uStack_c < *(uint *)(param_2 + 8));
      }
    }
  }
  (**(groove_com2 **)(*param_1 + 0x80))((int)param_1,0);
  return;
}



