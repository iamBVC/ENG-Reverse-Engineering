/* sub_43B080 @ 0043b080   1806 bytes */

void sub_43B080(int *param_1,int param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  char cVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  byte bVar9;
  byte bVar10;
  int *piVar11;
  int *piVar12;
  uint uVar13;
  byte bVar14;
  byte bVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  byte *pbStack_24;
  uint uStack_20;
  int iStack_1c;
  
  bVar15 = 0;
  piVar12 = param_1;
  (**(code **)(*param_1 + 100))(param_1,0,param_2,1,0);
  bVar14 = (byte)piVar12;
  (**(code **)(*param_1 + 0x80))();
  uVar5 = sub_43B010(*(undefined4 *)(param_2 + 0x58));
  sub_43B030(uVar5);
  cVar3 = sub_43B060(*(undefined4 *)(param_2 + 0x58));
  bVar9 = 0x1f - cVar3;
  uVar5 = sub_43B010(*(undefined4 *)(param_2 + 0x5c));
  sub_43B030(uVar5);
  cVar3 = sub_43B060(*(undefined4 *)(param_2 + 0x5c));
  bVar10 = 0x1f - cVar3;
  uVar5 = sub_43B010(*(undefined4 *)(param_2 + 0x60));
  bVar4 = sub_43B030(uVar5);
  uVar17 = (uint)bVar4;
  cVar3 = sub_43B060(*(undefined4 *)(param_2 + 0x60));
  bVar4 = 0x1f - cVar3;
  uVar5 = sub_43B010(*(undefined4 *)(param_2 + 100));
  sub_43B030(uVar5);
  iVar6 = sub_43B060(*(undefined4 *)(param_2 + 100));
  piVar11 = (int *)(0x1f - iVar6);
  uVar13 = 0;
  (**(code **)(*param_1 + 100))(param_1,0,param_2,1);
  piVar12 = param_1;
  if (iStack_1c == 4) {
    if (*(int *)(param_2 + 0x54) == 0x20) {
      iVar6 = *(int *)(param_2 + 0x24);
      uVar16 = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uVar18 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar9 = *pbStack_24;
              pbVar1 = pbStack_24 + 1;
              pbVar2 = pbStack_24 + 3;
              pbStack_24 = pbStack_24 + 4;
              uVar7 = (((uint)*pbVar2 & uVar17 & 0xff) << 0x18) >> (bVar4 & 0x1f) |
                      0U >> (bVar14 & 0x1f) |
                      (((uint)*pbVar1 & (uint)param_1 & 0xff) << 0x18) >> (bVar15 & 0x1f) |
                      (((uint)bVar9 & uVar13 & 0xff) << 0x18) >> (bVar10 & 0x1f);
              if (uVar7 == 0) {
                uVar7 = uStack_20;
              }
              iVar8 = uVar16 * *(int *)(param_2 + 0x10);
              iVar8 = ((int)((iVar8 >> 0x1f & 3U) + iVar8) >> 2) + uVar18;
              uVar18 = uVar18 + 1;
              *(uint *)(iVar6 + iVar8 * 4) = uVar7;
            } while (uVar18 < *(uint *)(param_2 + 0xc));
          }
          uVar16 = uVar16 + 1;
          piVar12 = piVar11;
        } while (uVar16 < *(uint *)(param_2 + 8));
      }
    }
    if (*(int *)(param_2 + 0x54) == 0x18) {
      iVar6 = *(int *)(param_2 + 0x24);
      uVar16 = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uVar18 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar9 = *pbStack_24;
              pbVar1 = pbStack_24 + 1;
              pbVar2 = pbStack_24 + 3;
              pbStack_24 = pbStack_24 + 4;
              uVar7 = (((uint)*pbVar2 & uVar17 & 0xff) << 0x18) >> (bVar4 & 0x1f) |
                      0U >> (bVar14 & 0x1f) |
                      (((uint)*pbVar1 & (uint)param_1 & 0xff) << 0x18) >> (bVar15 & 0x1f) |
                      (((uint)bVar9 & uVar13 & 0xff) << 0x18) >> (bVar10 & 0x1f);
              if (uVar7 == 0) {
                uVar7 = uStack_20;
              }
              iVar8 = uVar16 * *(int *)(param_2 + 0x10);
              iVar8 = ((int)((iVar8 >> 0x1f & 3U) + iVar8) >> 2) + uVar18;
              uVar18 = uVar18 + 1;
              *(uint *)(iVar6 + iVar8 * 4) = uVar7;
            } while (uVar18 < *(uint *)(param_2 + 0xc));
          }
          uVar16 = uVar16 + 1;
          piVar12 = piVar11;
        } while (uVar16 < *(uint *)(param_2 + 8));
      }
    }
    if (*(int *)(param_2 + 0x54) == 0x10) {
      iVar6 = *(int *)(param_2 + 0x24);
      uVar16 = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uVar18 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar9 = *pbStack_24;
              pbVar1 = pbStack_24 + 1;
              pbVar2 = pbStack_24 + 3;
              pbStack_24 = pbStack_24 + 4;
              uVar7 = (((uint)*pbVar2 & uVar17 & 0xff) << 0x18) >> (bVar4 & 0x1f) |
                      0U >> (bVar14 & 0x1f) |
                      (((uint)*pbVar1 & (uint)param_1 & 0xff) << 0x18) >> (bVar15 & 0x1f) |
                      (((uint)bVar9 & uVar13 & 0xff) << 0x18) >> (bVar10 & 0x1f);
              if (uVar7 == 0) {
                uVar7 = uStack_20;
              }
              iVar8 = (int)(uVar16 * *(int *)(param_2 + 0x10)) / 2 + uVar18;
              uVar18 = uVar18 + 1;
              *(short *)(iVar6 + iVar8 * 2) = (short)uVar7;
            } while (uVar18 < *(uint *)(param_2 + 0xc));
          }
          uVar16 = uVar16 + 1;
          piVar12 = piVar11;
        } while (uVar16 < *(uint *)(param_2 + 8));
      }
    }
  }
  else {
    if (*(int *)(param_2 + 0x54) == 0x20) {
      iVar6 = *(int *)(param_2 + 0x24);
      uVar17 = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uVar16 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar4 = *pbStack_24;
              pbVar1 = pbStack_24 + 1;
              pbStack_24 = pbStack_24 + 3;
              uVar18 = 0U >> (bVar14 & 0x1f) |
                       (((uint)*pbVar1 & (uint)param_1 & 0xff) << 0x18) >> (bVar15 & 0x1f) |
                       (((uint)bVar4 & uVar13 & 0xff) << 0x18) >> (bVar9 & 0x1f);
              if (uVar18 == 0) {
                uVar18 = uStack_20;
              }
              iVar8 = uVar17 * *(int *)(param_2 + 0x10);
              iVar8 = ((int)((iVar8 >> 0x1f & 3U) + iVar8) >> 2) + uVar16;
              uVar16 = uVar16 + 1;
              *(uint *)(iVar6 + iVar8 * 4) = uVar18;
            } while (uVar16 < *(uint *)(param_2 + 0xc));
          }
          uVar17 = uVar17 + 1;
          piVar12 = piVar11;
        } while (uVar17 < *(uint *)(param_2 + 8));
      }
    }
    if (*(int *)(param_2 + 0x54) == 0x18) {
      iVar6 = *(int *)(param_2 + 0x24);
      uVar17 = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uVar16 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar4 = *pbStack_24;
              pbVar1 = pbStack_24 + 1;
              pbStack_24 = pbStack_24 + 3;
              uVar18 = 0U >> (bVar14 & 0x1f) |
                       (((uint)*pbVar1 & (uint)param_1 & 0xff) << 0x18) >> (bVar15 & 0x1f) |
                       (((uint)bVar4 & uVar13 & 0xff) << 0x18) >> (bVar9 & 0x1f);
              if (uVar18 == 0) {
                uVar18 = uStack_20;
              }
              iVar8 = uVar17 * *(int *)(param_2 + 0x10);
              iVar8 = ((int)((iVar8 >> 0x1f & 3U) + iVar8) >> 2) + uVar16;
              uVar16 = uVar16 + 1;
              *(uint *)(iVar6 + iVar8 * 4) = uVar18;
            } while (uVar16 < *(uint *)(param_2 + 0xc));
          }
          uVar17 = uVar17 + 1;
          piVar12 = piVar11;
        } while (uVar17 < *(uint *)(param_2 + 8));
      }
    }
    if (*(int *)(param_2 + 0x54) == 0x10) {
      iVar6 = *(int *)(param_2 + 0x24);
      uVar17 = 0;
      if (*(int *)(param_2 + 8) != 0) {
        do {
          uVar16 = 0;
          if (*(int *)(param_2 + 0xc) != 0) {
            do {
              bVar4 = *pbStack_24;
              pbVar1 = pbStack_24 + 1;
              pbStack_24 = pbStack_24 + 3;
              uVar18 = 0U >> (bVar14 & 0x1f) |
                       (((uint)*pbVar1 & (uint)param_1 & 0xff) << 0x18) >> (bVar15 & 0x1f) |
                       (((uint)bVar4 & uVar13 & 0xff) << 0x18) >> (bVar9 & 0x1f);
              if (uVar18 == 0) {
                uVar18 = uStack_20;
              }
              iVar8 = (int)(uVar17 * *(int *)(param_2 + 0x10)) / 2 + uVar16;
              uVar16 = uVar16 + 1;
              *(short *)(iVar6 + iVar8 * 2) = (short)uVar18;
            } while (uVar16 < *(uint *)(param_2 + 0xc));
          }
          uVar17 = uVar17 + 1;
          piVar12 = piVar11;
        } while (uVar17 < *(uint *)(param_2 + 8));
      }
    }
  }
  (**(code **)(*piVar12 + 0x80))(piVar12,0);
  return;
}

