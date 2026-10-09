/* sub_407240 @ 00407240   4257 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_407240(void)

{
  uint *puVar1;
  int *piVar2;
  byte bVar3;
  ushort uVar4;
  undefined2 uVar5;
  int *piVar6;
  undefined *puVar7;
  int *piVar8;
  void *pvVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  ushort *puVar16;
  int iVar17;
  int iVar18;
  uint *puVar19;
  undefined4 unaff_ESI;
  undefined4 *puVar20;
  undefined4 unaff_EDI;
  int iVar21;
  undefined4 *puVar22;
  ushort *puVar23;
  int iVar24;
  undefined4 uVar25;
  uint uStack_6c8;
  int *piStack_6c4;
  int iStack_6c0;
  int iStack_6bc;
  int iStack_6b8;
  undefined4 *puStack_6ac;
  int iStack_6a8;
  int iStack_6a4;
  uint uStack_6a0;
  uint uStack_69c;
  int iStack_698;
  int iStack_694;
  int local_68c;
  uint local_688;
  uint uStack_684;
  undefined4 uStack_680;
  undefined4 uStack_67c;
  uint uStack_678;
  uint uStack_674;
  int iStack_670;
  undefined4 auStack_638 [8];
  int iStack_618;
  int iStack_614;
  undefined4 uStack_610;
  undefined4 uStack_60c;
  undefined1 auStack_604 [512];
  undefined1 auStack_404 [1028];
  
  piVar8 = DAT_00582cd0;
  local_68c = 0;
  local_688 = 0;
  (**(code **)(*DAT_00582cd0 + 0x2c))();
  iVar18 = 0;
  if (0 < DAT_00581148) {
    iVar21 = 0;
    do {
      piVar2 = (int *)(iVar21 + DAT_00581144);
      pvVar9 = operator_new(0x400);
      piVar2[2] = (int)pvVar9;
      if (pvVar9 == (void *)0x0) {
        return 0;
      }
      (**(code **)(&DAT_0057037c + *piVar2 * 0x20))(pvVar9,piVar2[5],piVar2[6],piVar2[1],1);
      if ((((DAT_00583400 != '\0') && (DAT_005833e9 != '\0')) &&
          (((&DAT_00570382)[*piVar2 * 0x20] == '\0' ||
           ((DAT_00583401 != '\0' && (DAT_005833ef != '\0')))))) &&
         (iVar10 = (**(code **)(*DAT_00582ccc + 0x14))
                             (DAT_00582ccc,
                              CONCAT31((uint3)(-(uint)((&DAT_00570382)[*piVar2 * 0x20] != '\0') >> 8
                                              ) & 4,0x44),piVar2[2],piVar2 + 4,0), iVar10 != 0)) {
        return 0;
      }
      iVar18 = iVar18 + 1;
      iVar21 = iVar21 + 0x1c;
    } while (iVar18 < DAT_00581148);
  }
  iStack_6bc = 0;
  if (0 < (int)DAT_00581150) {
    iStack_6c0 = 0;
    do {
      puVar19 = (uint *)(iStack_6c0 + (int)DAT_0058114c);
      if ((*puVar19 != 0) || ((DAT_00583400 != '\0' && (DAT_005833e9 != '\0')))) {
        if ((&DAT_00570384)[(*puVar19 & 0x7f) * 0x20] != '\0') {
          puVar11 = operator_new(puVar19[2] * puVar19[1] * 2);
          puVar19[7] = (uint)puVar11;
          if (puVar11 == (undefined4 *)0x0) {
            return 0;
          }
          uVar14 = puVar19[2];
          uVar15 = puVar19[1];
          for (uVar13 = (uVar14 * uVar15 & 0x7fffffff) >> 1; uVar13 != 0; uVar13 = uVar13 - 1) {
            *puVar11 = 0;
            puVar11 = puVar11 + 1;
          }
          for (uVar14 = uVar14 * uVar15 * 2 & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
            *(undefined1 *)puVar11 = 0;
            puVar11 = (undefined4 *)((int)puVar11 + 1);
          }
        }
        if (DAT_005833e1 == '\0') {
          uStack_680 = 0x7c;
          uStack_67c = 0x1007;
          uStack_674 = puVar19[1];
          uStack_678 = puVar19[2];
          puVar11 = (undefined4 *)(&PTR_DAT_00570370)[(*puVar19 & 0x7f) * 8];
          puVar12 = auStack_638;
          for (iVar18 = 8; iVar18 != 0; iVar18 = iVar18 + -1) {
            *puVar12 = *puVar11;
            puVar11 = puVar11 + 1;
            puVar12 = puVar12 + 1;
          }
          puVar1 = puVar19 + 3;
          uStack_610 = 0;
          uStack_60c = 0;
          iStack_618 = (uint)((byte)(-(uint)(DAT_005833e0 != '\0') >> 8) & 8 | 0x10) << 8;
          iStack_614 = (-(uint)(DAT_005833e0 != '\0') & 0xfffffff0) + 0x10;
          iVar18 = (**(code **)(*DAT_00582ccc + 0x18))(DAT_00582ccc,&uStack_680,puVar1,0);
          if (iVar18 != 0) {
            return 0;
          }
          iVar18 = (*(code *)**(undefined4 **)*puVar1)
                             ((undefined4 *)*puVar1,&DAT_0056e6dc,puVar19 + 4);
          if (iVar18 != 0) {
            return 0;
          }
          (**(code **)(*(int *)*puVar1 + 0x74))((int *)*puVar1,8,&puStack_6ac);
        }
        else {
          pvVar9 = operator_new(*(int *)((&PTR_DAT_00570370)[(*puVar19 & 0x7f) * 8] + 0xc) *
                                puVar19[2] * puVar19[1] >> 3);
          puVar19[7] = (uint)pvVar9;
          if (pvVar9 == (void *)0x0) {
            return 0;
          }
        }
        puVar19[5] = 0;
        if ((*puVar19 & 0x7f) == 0) {
          iVar18 = (**(code **)(*(int *)puVar19[3] + 100))((int *)puVar19[3],0,&uStack_680,0x821,0);
          if (iVar18 != 0) {
            return 0;
          }
          iVar18 = 0;
          if (0 < (int)puVar19[2]) {
            do {
              uVar14 = puVar19[1];
              puVar11 = (undefined4 *)(uVar14 * iVar18 + puVar19[6]);
              puVar12 = (undefined4 *)(uStack_684 * iVar18 + iStack_670);
              for (uVar15 = uVar14 >> 2; uVar15 != 0; uVar15 = uVar15 - 1) {
                *puVar12 = *puVar11;
                puVar11 = puVar11 + 1;
                puVar12 = puVar12 + 1;
              }
              iVar18 = iVar18 + 1;
              for (uVar14 = uVar14 & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
                *(undefined1 *)puVar12 = *(undefined1 *)puVar11;
                puVar11 = (undefined4 *)((int)puVar11 + 1);
                puVar12 = (undefined4 *)((int)puVar12 + 1);
              }
            } while (iVar18 < (int)puVar19[2]);
          }
          (**(code **)(*(int *)puVar19[3] + 0x80))((int *)puVar19[3],0);
        }
      }
      iStack_6bc = iStack_6bc + 1;
      iStack_6c0 = iStack_6c0 + 0x20;
    } while (iStack_6bc < (int)DAT_00581150);
  }
  if ((((DAT_00583374 < 0x280) || (DAT_00583378 < 0x1e0)) && (DAT_006d7c64 == '\0')) &&
     (*(int *)(PTR_DAT_00571f58 + 0x10) != 0)) {
    iStack_6a8 = 0;
    do {
      puVar16 = (ushort *)(*(int *)(PTR_DAT_00571f58 + 0x10) + iStack_6a8);
      if ((puVar16[2] != 0) && (puVar16[3] != 0)) {
        puVar23 = (ushort *)(DAT_00581154 + (uint)*puVar16 * 0x14);
        puVar19 = DAT_0058114c + *(char *)(DAT_00581154 + 2 + (uint)*puVar16 * 0x14) * 8;
        if ((*puVar19 & 0x80) == 0) {
          puVar11 = (undefined4 *)puVar19[6];
          *puVar19 = *puVar19 | 0x80;
          puVar12 = operator_new(puVar19[2] * puVar19[1] * 2);
          puVar19[6] = (uint)puVar12;
          if (puVar12 == (undefined4 *)0x0) {
            return 0;
          }
          uVar14 = puVar19[2];
          uVar15 = puVar19[1];
          for (uVar13 = (uVar14 * uVar15 & 0x7fffffff) >> 1; uVar13 != 0; uVar13 = uVar13 - 1) {
            *puVar12 = *puVar11;
            puVar11 = puVar11 + 1;
            puVar12 = puVar12 + 1;
          }
          for (uVar14 = uVar14 * uVar15 * 2 & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
            *(undefined1 *)puVar12 = *(undefined1 *)puVar11;
            puVar11 = (undefined4 *)((int)puVar11 + 1);
            puVar12 = (undefined4 *)((int)puVar12 + 1);
          }
        }
        piStack_6c4 = (int *)(uint)(byte)puVar23[2];
        uStack_6c8 = (uint)(byte)puVar23[6];
        uVar4 = *puVar23;
        uVar14 = ((uint)(byte)puVar23[4] - (int)piStack_6c4) + 1;
        iStack_6b8 = ((byte)puVar23[8] - uStack_6c8) + 1;
        if ((uVar4 & 8) != 0) {
          uVar14 = uVar14 * 2;
        }
        if ((uVar4 & 0x10) != 0) {
          iStack_6b8 = iStack_6b8 * 2;
        }
        if ((uVar4 & 4) != 0) {
          piStack_6c4 = (int *)((int)piStack_6c4 - 1);
          uStack_6c8 = uStack_6c8 - 1;
          uVar14 = uVar14 + 2;
          iStack_6b8 = iStack_6b8 + 2;
        }
        puVar11 = operator_new(iStack_6b8 * uVar14 * 2);
        if (puVar11 == (undefined4 *)0x0) {
          return 0;
        }
        iVar18 = 0;
        puVar12 = puVar11;
        if (0 < iStack_6b8) {
          do {
            puVar20 = (undefined4 *)
                      (puVar19[6] + ((uStack_6c8 + iVar18) * puVar19[1] + (int)piStack_6c4) * 2);
            puVar22 = puVar12;
            for (uVar15 = (uVar14 & 0x7fffffff) >> 1; uVar15 != 0; uVar15 = uVar15 - 1) {
              *puVar22 = *puVar20;
              puVar20 = puVar20 + 1;
              puVar22 = puVar22 + 1;
            }
            iVar18 = iVar18 + 1;
            for (uVar15 = uVar14 * 2 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
              *(undefined1 *)puVar22 = *(undefined1 *)puVar20;
              puVar20 = (undefined4 *)((int)puVar20 + 1);
              puVar22 = (undefined4 *)((int)puVar22 + 1);
            }
            puVar12 = (undefined4 *)((int)puVar12 + uVar14 * 2);
          } while (iVar18 < iStack_6b8);
        }
        sub_40C000(puVar19[6] + 2 + ((uStack_6c8 + 1) * puVar19[1] + (int)piStack_6c4) * 2,
                   puVar19[1],(undefined1 *)((int)puVar11 + uVar14 * 2 + 2),uVar14,uVar14 - 2,
                   iStack_6b8 + -2);
        sub_562941(puVar11);
      }
      iStack_6a8 = iStack_6a8 + 8;
    } while (iStack_6a8 < 0x800);
  }
  iStack_6bc = 0;
  if (0 < DAT_00581158) {
    iStack_6c0 = 0;
    do {
      puVar16 = (ushort *)(iStack_6c0 + DAT_00581154);
      uVar4 = *puVar16;
      if ((uVar4 & 1) == 0) {
        puVar19 = DAT_0058114c + (char)puVar16[1] * 8;
        uVar14 = *puVar19 & 0x7f;
        if (uVar14 != 0) {
          uStack_6c8 = (uint)(byte)puVar16[6];
          uVar15 = (uint)(byte)puVar16[2];
          iVar18 = ((byte)puVar16[4] - uVar15) + 1;
          iVar21 = ((byte)puVar16[8] - uStack_6c8) + 1;
          if ((uVar4 & 8) != 0) {
            iVar18 = iVar18 * 2;
          }
          if ((uVar4 & 0x10) != 0) {
            iVar21 = iVar21 * 2;
          }
          piStack_6c4 = (int *)uVar15;
          if ((uVar4 & 4) != 0) {
            piStack_6c4 = (int *)(uVar15 - 1);
            iVar18 = iVar18 + 2;
            uVar15 = uStack_6c8 - 1;
            iVar21 = iVar21 + 2;
            uStack_6c8 = uVar15;
          }
          iVar10 = uVar14 * 0x20;
          if ((&DAT_00570384)[iVar10] == '\0') {
            if (DAT_005833e1 == '\0') {
              iVar10 = (**(code **)(*(int *)puVar19[3] + 100))
                                 ((int *)puVar19[3],0,&uStack_680,0x821,0);
              if (iVar10 != 0) {
                return 0;
              }
              (**(code **)(&DAT_00570374 + (*puVar19 & 0x7f) * 0x20))
                        (iStack_670,uStack_684,puVar19[6],puVar19[1],unaff_ESI,unaff_EDI,iVar18,
                         iVar21,(*puVar16 & 0x7000) >> 0xc,
                         CONCAT31((int3)((uint)(&PTR_DAT_00570370)[(*puVar19 & 0x7f) * 8] >> 8),
                                  (byte)*puVar16 >> 1) & 0xffffff01,
                         (&PTR_DAT_00570370)[(*puVar19 & 0x7f) * 8]);
              (**(code **)(*(int *)puVar19[3] + 0x80))((int *)puVar19[3],0);
            }
            else {
              (**(code **)(&DAT_00570374 + iVar10))
                        (puVar19[7],
                         *(int *)((&PTR_DAT_00570370)[uVar14 * 8] + 0xc) * puVar19[1] >> 3,
                         puVar19[6],puVar19[1],piStack_6c4,uStack_6c8,iVar18,iVar21,
                         (uVar4 & 0x7000) >> 0xc,
                         CONCAT31((int3)((uint)(&PTR_DAT_00570370)[uVar14 * 8] >> 8),
                                  (byte)uVar4 >> 1) & 0xffffff01,(&PTR_DAT_00570370)[uVar14 * 8]);
            }
          }
          else {
            (**(code **)(&DAT_00570374 + iVar10))
                      (puVar19[7],puVar19[1] * 2,puVar19[6],puVar19[1],piStack_6c4,uStack_6c8,iVar18
                       ,iVar21,(uVar4 & 0x7000) >> 0xc,
                       CONCAT31((int3)(uVar15 >> 8),(byte)uVar4 >> 1) & 0xffffff01,&DAT_00571390);
          }
          *(float *)(puVar16 + 2) = (float)(byte)puVar16[2] / (float)(int)puVar19[1];
          *(float *)(puVar16 + 4) = (float)((byte)puVar16[4] + 1) / (float)(int)puVar19[1];
          *(float *)(puVar16 + 6) = (float)(byte)puVar16[6] / (float)(int)puVar19[2];
          *(float *)(puVar16 + 8) = (float)((byte)puVar16[8] + 1) / (float)(int)puVar19[2];
        }
      }
      else {
        uVar14 = (uVar4 & 0x7000) >> 0xc;
        (**(code **)(&DAT_00570358 + uVar14 * 4))
                  (puVar16 + 2,puVar16 + 4,puVar16 + 6,puVar16 + 8,uVar14);
      }
      iStack_6bc = iStack_6bc + 1;
      iStack_6c0 = iStack_6c0 + 0x14;
    } while (iStack_6bc < DAT_00581158);
  }
  iStack_6bc = 0;
  if (0 < DAT_00581134) {
    iStack_6c0 = 0;
    do {
      puVar11 = DAT_0058114c;
      puVar16 = (ushort *)(iStack_6c0 + DAT_00581138);
      switch((char)puVar16[1]) {
      case '\a':
      case '\t':
        puVar23 = (ushort *)(DAT_00581154 + (uint)*puVar16 * 0x14);
        bVar3 = (byte)puVar23[1];
        piVar2 = (int *)(DAT_00581144 + *(char *)(DAT_00581154 + 3 + (uint)*puVar16 * 0x14) * 0x1c);
        if (((DAT_00583400 == '\0') || (DAT_005833e9 == '\0')) ||
           (((&DAT_00570382)[*piVar2 * 0x20] != '\0' &&
            ((DAT_00583401 == '\0' || (DAT_005833ef == '\0')))))) {
          piStack_6c4 = (int *)(uint)(byte)puVar23[2];
          uStack_6c8 = (uint)(byte)puVar23[6];
          iVar18 = (uint)(byte)puVar23[4] - (int)piStack_6c4;
          iVar21 = (byte)puVar23[8] - uStack_6c8;
          iStack_6a4 = iVar18 + 1;
          iVar10 = iVar21 + 1;
          if ((*puVar23 & 4) != 0) {
            piStack_6c4 = (int *)((int)piStack_6c4 + -1);
            uStack_6c8 = uStack_6c8 - 1;
            iStack_6a4 = iVar18 + 3;
            iVar10 = iVar21 + 3;
          }
          iStack_698 = (int)(0x100 / (longlong)iStack_6a4);
          iStack_6a8 = ((uint)*(byte *)((int)puVar16 + 9) - (uint)(byte)puVar16[4]) + 1;
          iStack_694 = (int)(0x100 / (longlong)iVar10) * iStack_698;
          iVar21 = (iStack_694 + -1 + iStack_6a8) / iStack_694;
          uStack_6a0 = DAT_00581150;
          iVar18 = iVar21 + DAT_00581150;
          puStack_6ac = operator_new(iVar18 * 0x20);
          if (puStack_6ac == (undefined4 *)0x0) {
            return 0;
          }
          if (-1 < iVar18 + -1) {
            puVar11 = puStack_6ac + 2;
            iVar17 = iVar18;
            do {
              puVar11[-2] = 0;
              puVar11[-1] = 0;
              *puVar11 = 0;
              puVar11[1] = 0;
              puVar11[2] = 0;
              puVar11[3] = 0;
              puVar11[4] = 0;
              puVar11[5] = 0;
              puVar11 = puVar11 + 8;
              iVar17 = iVar17 + -1;
            } while (iVar17 != 0);
          }
          puVar11 = DAT_0058114c;
          puVar12 = puStack_6ac;
          for (iVar17 = (DAT_00581150 & 0x7ffffff) << 3; iVar17 != 0; iVar17 = iVar17 + -1) {
            *puVar12 = *puVar11;
            puVar11 = puVar11 + 1;
            puVar12 = puVar12 + 1;
          }
          for (iVar17 = 0; iVar17 != 0; iVar17 = iVar17 + -1) {
            *(undefined1 *)puVar12 = *(undefined1 *)puVar11;
            puVar11 = (undefined4 *)((int)puVar11 + 1);
            puVar12 = (undefined4 *)((int)puVar12 + 1);
          }
          sub_562941(DAT_0058114c);
          puVar11 = puStack_6ac;
          DAT_00581150 = DAT_00581150 + iVar21;
          DAT_0058114c = puStack_6ac;
          uVar4 = puVar23[1];
          if (DAT_005833e1 == '\0') {
            uStack_680 = 0x7c;
            uStack_674 = 0x100;
            uStack_678 = 0x100;
            uStack_67c = 0x1007;
            puVar12 = (undefined4 *)(&PTR_DAT_00570370)[*piVar2 * 8];
            puVar20 = auStack_638;
            for (iVar21 = 8; iVar21 != 0; iVar21 = iVar21 + -1) {
              *puVar20 = *puVar12;
              puVar12 = puVar12 + 1;
              puVar20 = puVar20 + 1;
            }
            iStack_618 = (uint)((byte)(-(uint)(DAT_005833e0 != '\0') >> 8) & 8 | 0x10) << 8;
            iStack_614 = (-(uint)(DAT_005833e0 != '\0') & 0xfffffff0) + 0x10;
            uStack_610 = 0;
            uStack_60c = 0;
            if ((int)uStack_6a0 < iVar18) {
              iVar21 = uStack_6a0 << 5;
              uVar14 = uStack_6a0;
              do {
                *(int *)(iVar21 + (int)DAT_0058114c) = *piVar2;
                *(undefined4 *)(iVar21 + 4 + (int)DAT_0058114c) = 0x100;
                *(undefined4 *)(iVar21 + 8 + (int)DAT_0058114c) = 0x100;
                iVar17 = (**(code **)(*DAT_00582ccc + 0x18))
                                   (DAT_00582ccc,&uStack_680,
                                    (undefined1 *)(iVar21 + 0xc + (int)DAT_0058114c),0);
                if (iVar17 != 0) {
                  return 0;
                }
                piVar6 = *(int **)(iVar21 + 0xc + (int)DAT_0058114c);
                (**(code **)(*piVar6 + 0x74))(piVar6,8,&uStack_6a0);
                puVar12 = *(undefined4 **)(iVar21 + 0xc + (int)DAT_0058114c);
                iVar17 = (**(code **)*puVar12)
                                   (puVar12,&DAT_0056e6dc,
                                    (undefined1 *)(iVar21 + 0x10 + (int)DAT_0058114c));
                if (iVar17 != 0) {
                  return 0;
                }
                uVar14 = uVar14 + 1;
                *(undefined4 *)(iVar21 + 0x14 + (int)DAT_0058114c) = 0;
                iVar21 = iVar21 + 0x20;
              } while ((int)uVar14 < iVar18);
            }
          }
          else {
            uStack_69c = uStack_6a0;
            if ((int)uStack_6a0 < iVar18) {
              iVar21 = uStack_6a0 << 5;
              do {
                *(int *)(iVar21 + (int)DAT_0058114c) = *piVar2;
                *(undefined4 *)(iVar21 + 4 + (int)DAT_0058114c) = 0x100;
                *(undefined4 *)(iVar21 + 8 + (int)DAT_0058114c) = 0x100;
                pvVar9 = operator_new((*(uint *)((&PTR_DAT_00570370)[*piVar2 * 8] + 0xc) & 0xffff)
                                      << 0xd);
                *(void **)(iVar21 + 0x1c + (int)DAT_0058114c) = pvVar9;
                if (*(int *)(iVar21 + 0x1c + (int)DAT_0058114c) == 0) {
                  return 0;
                }
                *(undefined4 *)(iVar21 + 0x14 + (int)DAT_0058114c) = 0;
                iVar21 = iVar21 + 0x20;
                uStack_69c = uStack_69c + 1;
              } while ((int)uStack_69c < iVar18);
            }
          }
          local_688 = (uint)(byte)puVar16[4];
          uStack_684 = (uint)*(byte *)((int)puVar16 + 9);
          *(char *)((int)puVar16 + 5) = (char)iStack_6a8;
          *(undefined1 *)(puVar16 + 1) = 8;
          *(char *)(puVar16 + 2) = (char)puVar16[3];
          *(undefined1 *)(puVar16 + 3) = 0;
          *(undefined1 *)((int)puVar16 + 7) = 0;
          *(undefined1 *)(puVar16 + 4) = 0;
          *(undefined1 *)((int)puVar16 + 9) = 0;
          pvVar9 = operator_new(iStack_6a8 * 0x14);
          *(void **)(puVar16 + 6) = pvVar9;
          if (pvVar9 == (void *)0x0) {
            return 0;
          }
          uStack_69c = 0;
          if (0 < iStack_6a8) {
            puStack_6ac = (undefined4 *)0x0;
            do {
              iVar17 = ((int)uStack_69c % iStack_698) * iStack_6a4;
              iVar18 = (((int)uStack_69c % iStack_694) / iStack_698) * iVar10;
              iVar21 = (int)uStack_69c / iStack_694 + uStack_6a0;
              *(ushort *)((int)puStack_6ac + *(int *)(puVar16 + 6)) = *puVar23 | 0x20;
              *(char *)((int)puStack_6ac + *(int *)(puVar16 + 6) + 2) = (char)iVar21;
              *(undefined1 *)((int)puStack_6ac + *(int *)(puVar16 + 6) + 3) = 0xff;
              if ((*puVar23 & 4) == 0) {
                *(float *)((int)puStack_6ac + *(int *)(puVar16 + 6) + 4) =
                     (float)iVar17 * _DAT_0056e118;
                *(float *)((int)puStack_6ac + *(int *)(puVar16 + 6) + 8) =
                     (float)(iStack_6a4 + iVar17) * _DAT_0056e118;
                *(float *)((int)puStack_6ac + *(int *)(puVar16 + 6) + 0xc) =
                     (float)iVar18 * _DAT_0056e118;
                iVar24 = iVar18;
              }
              else {
                *(float *)((int)puStack_6ac + *(int *)(puVar16 + 6) + 4) =
                     (float)(iVar17 + 1) * _DAT_0056e118;
                *(float *)((int)puStack_6ac + *(int *)(puVar16 + 6) + 8) =
                     (float)(iVar17 + -1 + iStack_6a4) * _DAT_0056e118;
                *(float *)((int)puStack_6ac + *(int *)(puVar16 + 6) + 0xc) =
                     (float)(iVar18 + 1) * _DAT_0056e118;
                iVar24 = iVar18 + -1;
              }
              *(float *)((int)puStack_6ac + *(int *)(puVar16 + 6) + 0x10) =
                   (float)(iVar24 + iVar10) * _DAT_0056e118;
              if (DAT_005833e1 == '\0') {
                iVar24 = 0;
                iVar18 = (**(code **)(*(int *)DAT_0058114c[iVar21 * 8 + 3] + 100))
                                   ((int *)DAT_0058114c[iVar21 * 8 + 3],0,&uStack_680,0x821);
                if (iVar18 != 0) {
                  return 0;
                }
                (**(code **)(&DAT_00570378 + *piStack_6c4 * 0x20))
                          (iStack_670,uStack_684,*(undefined4 *)(iVar24 + 0x18),
                           *(undefined4 *)(iVar24 + 4),iVar17,uStack_6c8,unaff_ESI,unaff_EDI,iVar10,
                           iVar21 * 0x20,piStack_6c4[5],(*puVar23 & 0x7000) >> 0xc,
                           CONCAT31((int3)((uint)(&PTR_DAT_00570370)[*piStack_6c4 * 8] >> 8),
                                    (byte)*puVar23 >> 1) & 0xffffff01,
                           (&PTR_DAT_00570370)[*piStack_6c4 * 8]);
                (**(code **)(**(int **)((int)(piVar8 + 3) + (int)DAT_0058114c) + 0x80))
                          (*(int **)((int)(piVar8 + 3) + (int)DAT_0058114c),0);
              }
              else {
                puVar7 = (&PTR_DAT_00570370)[*piVar2 * 8];
                (**(code **)(&DAT_00570378 + *piVar2 * 0x20))
                          (DAT_0058114c[iVar21 * 8 + 7],
                           (uint)(DAT_0058114c[iVar21 * 8 + 1] * *(int *)(puVar7 + 0xc)) >> 3,
                           puVar11[(char)(byte)uVar4 * 8 + 6],puVar11[(char)(byte)uVar4 * 8 + 1],
                           iVar17,iVar18,piStack_6c4,uStack_6c8,iStack_6a4,iVar10,piVar2[5],
                           (*puVar23 & 0x7000) >> 0xc,
                           CONCAT31((int3)((uint)puVar7 >> 8),(byte)*puVar23 >> 1) & 0xffffff01,
                           puVar7);
              }
              uVar5 = *(undefined2 *)(piVar2[5] + uStack_684 * 2);
              for (uVar14 = uStack_684; (int)local_688 < (int)uVar14; uVar14 = uVar14 - 1) {
                *(undefined2 *)(piVar2[5] + uVar14 * 2) =
                     *(undefined2 *)(piVar2[5] + -2 + uVar14 * 2);
              }
              *(undefined2 *)(piVar2[5] + local_688 * 2) = uVar5;
              uStack_69c = uStack_69c + 1;
              puStack_6ac = puStack_6ac + 5;
            } while ((int)uStack_69c < iStack_6a8);
          }
          iVar18 = 5;
          puVar11 = *(undefined4 **)(puVar16 + 6);
          goto LAB_004080fe;
        }
        *(float *)(puVar23 + 2) =
             (float)(byte)puVar23[2] / (float)(int)DAT_0058114c[(char)bVar3 * 8 + 1];
        *(float *)(puVar23 + 4) =
             (float)((byte)puVar23[4] + 1) / (float)(int)puVar11[(char)bVar3 * 8 + 1];
        *(float *)(puVar23 + 6) = (float)(byte)puVar23[6] / (float)(int)puVar11[(char)bVar3 * 8 + 2]
        ;
        *(float *)(puVar23 + 8) =
             (float)((byte)puVar23[8] + 1) / (float)(int)puVar11[(char)bVar3 * 8 + 2];
        break;
      case '\b':
        iVar18 = 0;
        if (*(char *)((int)puVar16 + 5) != '\0') {
          iVar21 = 0;
          do {
            uVar14 = (uint)*(ushort *)(iVar21 + *(int *)(puVar16 + 6));
            if (uVar14 != 0xffffffff) {
              puVar11 = (undefined4 *)(DAT_00581154 + uVar14 * 0x14);
              puVar23 = (ushort *)(iVar21 + *(int *)(puVar16 + 6));
              for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
                *(undefined4 *)puVar23 = *puVar11;
                puVar11 = puVar11 + 1;
                puVar23 = puVar23 + 2;
              }
            }
            iVar18 = iVar18 + 1;
            iVar21 = iVar21 + 0x14;
          } while (iVar18 < (int)(uint)*(byte *)((int)puVar16 + 5));
        }
        puVar23 = *(ushort **)(puVar16 + 6);
        iVar18 = 5;
        puVar11 = (undefined4 *)(DAT_00581154 + (uint)*puVar16 * 0x14);
LAB_004080fe:
        for (; iVar18 != 0; iVar18 = iVar18 + -1) {
          *(undefined4 *)puVar23 = *puVar11;
          puVar11 = puVar11 + 1;
          puVar23 = puVar23 + 2;
        }
        break;
      case '\n':
      case '\v':
        iVar18 = 0;
        if ((char)puVar16[4] != '\0') {
          iVar21 = 0;
          do {
            uVar14 = (uint)*(ushort *)(iVar21 + *(int *)(puVar16 + 6));
            if (uVar14 != 0xffffffff) {
              puVar11 = (undefined4 *)(DAT_00581154 + uVar14 * 0x14);
              puVar23 = (ushort *)(iVar21 + *(int *)(puVar16 + 6));
              for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
                *(undefined4 *)puVar23 = *puVar11;
                puVar11 = puVar11 + 1;
                puVar23 = puVar23 + 2;
              }
            }
            iVar18 = iVar18 + 1;
            iVar21 = iVar21 + 0x14;
          } while (iVar18 < (int)(uint)(byte)puVar16[4]);
        }
      }
      iStack_6bc = iStack_6bc + 1;
      iStack_6c0 = iStack_6c0 + 0x10;
    } while (iStack_6bc < DAT_00581134);
  }
  iVar18 = 0;
  iStack_6bc = 0;
  if (0 < (int)DAT_00581150) {
    do {
      puVar19 = (uint *)((int)DAT_0058114c + iVar18);
      uVar14 = *(uint *)((int)DAT_0058114c + iVar18) & 0x7f;
      if ((&DAT_00570384)[uVar14 * 0x20] != '\0') {
        if (((uVar14 == 4) || (uVar14 == 5)) || (uVar25 = 0, uVar14 == 7)) {
          uVar25 = 1;
        }
        sub_436CC0(uVar25);
        sub_436D40(puVar19[7],puVar19[2] * puVar19[1]);
        sub_436E30(0,0x100,auStack_604);
        sub_4083A0(auStack_404,auStack_604,0,0x100,uVar25);
        iVar21 = (**(code **)(*DAT_00582ccc + 0x14))(DAT_00582ccc,0x44,auStack_404,puVar19 + 5,0);
        if (((iVar21 != 0) ||
            (iVar21 = (**(code **)(*(int *)puVar19[3] + 0x7c))((int *)puVar19[3],puVar19[5]),
            iVar21 != 0)) ||
           (iVar21 = (**(code **)(*(int *)puVar19[3] + 100))
                               ((int *)puVar19[3],0,&uStack_69c,0x821,0), iVar21 != 0)) {
          return 0;
        }
        iVar21 = 0;
        if (0 < (int)puVar19[2]) {
          do {
            sub_437AC0(0,puVar19[7] + puVar19[1] * iVar21 * 2,uStack_6a0 * iVar21 + local_68c,
                       puVar19[1]);
            iVar21 = iVar21 + 1;
          } while (iVar21 < (int)puVar19[2]);
        }
        (**(code **)(*(int *)puVar19[3] + 0x80))((int *)puVar19[3],0);
        sub_426500();
        sub_562941(puVar19[7]);
        puVar19[7] = 0;
      }
      if ((*puVar19 & 0x80) != 0) {
        sub_562941(puVar19[6]);
        *puVar19 = *puVar19 & 0x7f;
      }
      puVar19[6] = 0;
      iVar21 = (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,puVar19[4]);
      if (iVar21 != 0) {
        return 0;
      }
      DAT_006d7c54 = puVar19[4];
      iStack_6bc = iStack_6bc + 1;
      iVar18 = iVar18 + 0x20;
    } while (iStack_6bc < (int)DAT_00581150);
  }
  return 1;
}

