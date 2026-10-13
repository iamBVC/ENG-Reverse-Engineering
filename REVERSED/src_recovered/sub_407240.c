/* Ghidra export with 26 verified indirect call signatures. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_407240(void)

{
  uint *arg2;
  int *piVar1;
  byte bVar2;
  ushort uVar3;
  undefined2 uVar4;
  int *arg0;
  undefined *arg13;
  void *pvVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  ushort *puVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint *puVar18;
  undefined4 *puVar19;
  int iVar20;
  int iVar21;
  undefined4 *puVar22;
  int arg9;
  ushort *puVar23;
  undefined4 uStack_6cc;
  uint uStack_6c4;
  uint uStack_6c0;
  int iStack_6bc;
  int iStack_6b8;
  int iStack_6b4;
  int iStack_6a8;
  int iStack_6a4;
  uint uStack_698;
  undefined4 color_key[2] = {0};
  uint uStack_684;
  uint uStack_680;
  undefined4 descriptor[31] = {0};
  undefined1 auStack_600 [512];
  undefined1 auStack_400 [1024];
  
  fprintf(stderr, "[textures] upload begin palettes=%d textures=%u\n", DAT_00581148, DAT_00581150);
  color_key[0] = 0;
  color_key[1] = 0;
  (**(groove_com1 **)(*DAT_00582cd0 + 0x2c))((int)DAT_00582cd0);
  iVar17 = 0;
  if (0 < DAT_00581148) {
    iVar21 = 0;
    do {
      piVar1 = (int *)(iVar21 + DAT_00581144);
      pvVar5 = operator_new(0x400);
      piVar1[2] = (int)pvVar5;
      if (pvVar5 == (void *)0x0) {
        return 0;
      }
      (**(code **)(&DAT_0057037c + *piVar1 * 0x20))((int)pvVar5,piVar1[5],piVar1[6],piVar1[1],1);
      if ((((DAT_00583400 != '\0') && (DAT_005833e9 != '\0')) &&
          (((&DAT_00570382)[*piVar1 * 0x20] == '\0' ||
           ((DAT_00583401 != '\0' && (DAT_005833ef != '\0')))))) &&
         (iVar6 = (**(groove_com5 **)(*DAT_00582ccc + 0x14))
                            ((int)DAT_00582ccc,
                             CONCAT31((uint3)(-(uint)((&DAT_00570382)[*piVar1 * 0x20] != '\0') >> 8)
                                      & 4,0x44),piVar1[2],(int)(piVar1 + 4),0), iVar6 != 0)) {
        return 0;
      }
      iVar17 = iVar17 + 1;
      iVar21 = iVar21 + 0x1c;
    } while (iVar17 < DAT_00581148);
  }
  iStack_6b8 = 0;
  if (0 < (int)DAT_00581150) {
    iStack_6bc = 0;
    do {
      puVar18 = (uint *)(iStack_6bc + (int)DAT_0058114c);
      if ((*puVar18 != 0) || ((DAT_00583400 != '\0' && (DAT_005833e9 != '\0')))) {
        if ((&DAT_00570384)[(*puVar18 & 0x7f) * 0x20] != '\0') {
          puVar7 = operator_new(puVar18[2] * puVar18[1] * 2);
          puVar18[7] = (uint)puVar7;
          if (puVar7 == (undefined4 *)0x0) {
            return 0;
          }
          uVar12 = puVar18[2];
          uVar13 = puVar18[1];
          for (uVar11 = (uVar12 * uVar13 & 0x7fffffff) >> 1; uVar11 != 0; uVar11 = uVar11 - 1) {
            *puVar7 = 0;
            puVar7 = puVar7 + 1;
          }
          for (uVar12 = uVar12 * uVar13 * 2 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined1 *)puVar7 = 0;
            puVar7 = (undefined4 *)((int)puVar7 + 1);
          }
        }
        if (DAT_005833e1 == '\0') {
          descriptor[0] = 0x7c;
          descriptor[1] = 0x1007;
          descriptor[3] = puVar18[1];
          descriptor[2] = puVar18[2];
          puVar7 = (undefined4 *)(&PTR_DAT_00570370)[(*puVar18 & 0x7f) * 8];
          puVar8 = (descriptor + 18);
          for (iVar17 = 8; iVar17 != 0; iVar17 = iVar17 + -1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
          arg2 = puVar18 + 3;
          descriptor[28] = 0;
          descriptor[29] = 0;
          descriptor[26] = (uint)((byte)(-(uint)(DAT_005833e0 != '\0') >> 8) & 8 | 0x10) << 8;
          descriptor[27] = (-(uint)(DAT_005833e0 != '\0') & 0xfffffff0) + 0x10;
          iVar17 = (**(groove_com4 **)(*DAT_00582ccc + 0x18))
                             ((int)DAT_00582ccc,(int)&descriptor[0],(int)arg2,0);
          if (iVar17 != 0) {
            return 0;
          }
          iVar17 = (*(groove_com3 *)**(undefined4 **)*arg2)((int)*arg2,(int)&DAT_0056e6dc,(int)(puVar18 + 4));
          if (iVar17 != 0) {
            return 0;
          }
          (**(groove_com3 **)(*(int *)*arg2 + 0x74))((int)*arg2,8,(int)&color_key[0]);
        }
        else {
          pvVar5 = operator_new(*(int *)((&PTR_DAT_00570370)[(*puVar18 & 0x7f) * 8] + 0xc) *
                                puVar18[2] * puVar18[1] >> 3);
          puVar18[7] = (uint)pvVar5;
          if (pvVar5 == (void *)0x0) {
            return 0;
          }
        }
        puVar18[5] = 0;
        if ((*puVar18 & 0x7f) == 0) {
          iVar17 = (**(groove_com5 **)(*(int *)puVar18[3] + 100))
                             ((int)puVar18[3],0,(int)&descriptor[0],0x821,0);
          if (iVar17 != 0) {
            return 0;
          }
          iVar17 = 0;
          if (0 < (int)puVar18[2]) {
            do {
              uVar12 = puVar18[1];
              puVar7 = (undefined4 *)(uVar12 * iVar17 + puVar18[6]);
              puVar8 = (undefined4 *)(descriptor[4] * iVar17 + descriptor[9]);
              for (uVar13 = uVar12 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
                *puVar8 = *puVar7;
                puVar7 = puVar7 + 1;
                puVar8 = puVar8 + 1;
              }
              iVar17 = iVar17 + 1;
              for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
                *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
                puVar7 = (undefined4 *)((int)puVar7 + 1);
                puVar8 = (undefined4 *)((int)puVar8 + 1);
              }
            } while (iVar17 < (int)puVar18[2]);
          }
          (**(groove_com2 **)(*(int *)puVar18[3] + 0x80))((int)puVar18[3],0);
        }
      }
      iStack_6b8 = iStack_6b8 + 1;
      iStack_6bc = iStack_6bc + 0x20;
    } while (iStack_6b8 < (int)DAT_00581150);
  }
  if ((((DAT_00583374 < 0x280) || (DAT_00583378 < 0x1e0)) && (DAT_006d7c64 == '\0')) &&
     (*(int *)((unsigned char *)PTR_DAT_00571f58 + 0x10) != 0)) {
    iStack_6a4 = 0;
    do {
      puVar14 = (ushort *)(*(int *)((unsigned char *)PTR_DAT_00571f58 + 0x10) + iStack_6a4);
      if ((puVar14[2] != 0) && (puVar14[3] != 0)) {
        puVar23 = (ushort *)(DAT_00581154 + (uint)*puVar14 * 0x14);
        puVar18 = DAT_0058114c + *(char *)(DAT_00581154 + 2 + (uint)*puVar14 * 0x14) * 8;
        if ((*puVar18 & 0x80) == 0) {
          puVar7 = (undefined4 *)puVar18[6];
          *puVar18 = *puVar18 | 0x80;
          puVar8 = operator_new(puVar18[2] * puVar18[1] * 2);
          puVar18[6] = (uint)puVar8;
          if (puVar8 == (undefined4 *)0x0) {
            return 0;
          }
          uVar12 = puVar18[2];
          uVar13 = puVar18[1];
          for (uVar11 = (uVar12 * uVar13 & 0x7fffffff) >> 1; uVar11 != 0; uVar11 = uVar11 - 1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
          for (uVar12 = uVar12 * uVar13 * 2 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
            puVar7 = (undefined4 *)((int)puVar7 + 1);
            puVar8 = (undefined4 *)((int)puVar8 + 1);
          }
        }
        uStack_6c0 = (uint)(byte)puVar23[2];
        uStack_6c4 = (uint)(byte)puVar23[6];
        uVar3 = *puVar23;
        uVar12 = ((byte)puVar23[4] - uStack_6c0) + 1;
        iStack_6b4 = ((byte)puVar23[8] - uStack_6c4) + 1;
        if ((uVar3 & 8) != 0) {
          uVar12 = uVar12 * 2;
        }
        if ((uVar3 & 0x10) != 0) {
          iStack_6b4 = iStack_6b4 * 2;
        }
        if ((uVar3 & 4) != 0) {
          uStack_6c0 = uStack_6c0 - 1;
          uStack_6c4 = uStack_6c4 - 1;
          uVar12 = uVar12 + 2;
          iStack_6b4 = iStack_6b4 + 2;
        }
        puVar7 = operator_new(iStack_6b4 * uVar12 * 2);
        if (puVar7 == (undefined4 *)0x0) {
          return 0;
        }
        iVar17 = 0;
        puVar8 = puVar7;
        if (0 < iStack_6b4) {
          do {
            puVar19 = (undefined4 *)
                      (puVar18[6] + ((uStack_6c4 + iVar17) * puVar18[1] + uStack_6c0) * 2);
            puVar22 = puVar8;
            for (uVar13 = (uVar12 & 0x7fffffff) >> 1; uVar13 != 0; uVar13 = uVar13 - 1) {
              *puVar22 = *puVar19;
              puVar19 = puVar19 + 1;
              puVar22 = puVar22 + 1;
            }
            iVar17 = iVar17 + 1;
            for (uVar13 = uVar12 * 2 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
              *(undefined1 *)puVar22 = *(undefined1 *)puVar19;
              puVar19 = (undefined4 *)((int)puVar19 + 1);
              puVar22 = (undefined4 *)((int)puVar22 + 1);
            }
            puVar8 = (undefined4 *)((int)puVar8 + uVar12 * 2);
          } while (iVar17 < iStack_6b4);
        }
        sub_40C000(puVar18[6] + 2 + ((uStack_6c4 + 1) * puVar18[1] + uStack_6c0) * 2,puVar18[1],
                   (undefined1 *)((int)puVar7 + uVar12 * 2 + 2),uVar12,uVar12 - 2,iStack_6b4 + -2);
        sub_562941(puVar7);
      }
      iStack_6a4 = iStack_6a4 + 8;
    } while (iStack_6a4 < 0x800);
  }
  iStack_6b8 = 0;
  if (0 < DAT_00581158) {
    iStack_6bc = 0;
    do {
      puVar14 = (ushort *)(iStack_6bc + DAT_00581154);
      uVar3 = *puVar14;
      if ((uVar3 & 1) == 0) {
        puVar18 = DAT_0058114c + (char)puVar14[1] * 8;
        uVar12 = *puVar18 & 0x7f;
        if (uVar12 != 0) {
          uStack_6c4 = (uint)(byte)puVar14[6];
          uVar13 = (uint)(byte)puVar14[2];
          iVar17 = ((byte)puVar14[4] - uVar13) + 1;
          iVar21 = ((byte)puVar14[8] - uStack_6c4) + 1;
          if ((uVar3 & 8) != 0) {
            iVar17 = iVar17 * 2;
          }
          if ((uVar3 & 0x10) != 0) {
            iVar21 = iVar21 * 2;
          }
          uStack_6c0 = uVar13;
          if ((uVar3 & 4) != 0) {
            uStack_6c0 = uVar13 - 1;
            iVar17 = iVar17 + 2;
            uVar13 = uStack_6c4 - 1;
            iVar21 = iVar21 + 2;
            uStack_6c4 = uVar13;
          }
          iVar6 = uVar12 * 0x20;
          if ((&DAT_00570384)[iVar6] == '\0') {
            if (DAT_005833e1 == '\0') {
              iVar6 = (**(groove_com5 **)(*(int *)puVar18[3] + 100))
                                ((int)puVar18[3],0,(int)&descriptor[0],0x821,0);
              if (iVar6 != 0) {
                return 0;
              }
              (**(code **)(&DAT_00570374 + (*puVar18 & 0x7f) * 0x20))
                        (descriptor[9],descriptor[4],puVar18[6],puVar18[1],uStack_6c0,uStack_6c4,iVar17,
                         iVar21,(*puVar14 & 0x7000) >> 0xc,
                         CONCAT31((int3)((uint)(&PTR_DAT_00570370)[(*puVar18 & 0x7f) * 8] >> 8),
                                  (byte)*puVar14 >> 1) & 0xffffff01,
                         (int)(&PTR_DAT_00570370)[(*puVar18 & 0x7f) * 8]);
              (**(groove_com2 **)(*(int *)puVar18[3] + 0x80))((int)puVar18[3],0);
            }
            else {
              (**(code **)(&DAT_00570374 + iVar6))
                        (puVar18[7],
                         *(int *)((&PTR_DAT_00570370)[uVar12 * 8] + 0xc) * puVar18[1] >> 3,
                         puVar18[6],puVar18[1],uStack_6c0,uStack_6c4,iVar17,iVar21,
                         (uVar3 & 0x7000) >> 0xc,
                         CONCAT31((int3)((uint)(&PTR_DAT_00570370)[uVar12 * 8] >> 8),
                                  (byte)uVar3 >> 1) & 0xffffff01,
                         (int)(&PTR_DAT_00570370)[uVar12 * 8]);
            }
          }
          else {
            (**(code **)(&DAT_00570374 + iVar6))
                      (puVar18[7],puVar18[1] * 2,puVar18[6],puVar18[1],uStack_6c0,uStack_6c4,iVar17,
                       iVar21,(uVar3 & 0x7000) >> 0xc,
                       CONCAT31((int3)(uVar13 >> 8),(byte)uVar3 >> 1) & 0xffffff01,0x571390);
          }
          *(float *)(puVar14 + 2) = (float)(byte)puVar14[2] / (float)(int)puVar18[1];
          *(float *)(puVar14 + 4) = (float)((byte)puVar14[4] + 1) / (float)(int)puVar18[1];
          *(float *)(puVar14 + 6) = (float)(byte)puVar14[6] / (float)(int)puVar18[2];
          *(float *)(puVar14 + 8) = (float)((byte)puVar14[8] + 1) / (float)(int)puVar18[2];
        }
      }
      else {
        uVar12 = (uVar3 & 0x7000) >> 0xc;
        (**(code **)(&DAT_00570358 + uVar12 * 4))
                  ((int)(puVar14 + 2),(int)(puVar14 + 4),(int)(puVar14 + 6),(int)(puVar14 + 8),
                   uVar12);
      }
      iStack_6b8 = iStack_6b8 + 1;
      iStack_6bc = iStack_6bc + 0x14;
    } while (iStack_6b8 < DAT_00581158);
  }
  iStack_6b8 = 0;
  if (0 < DAT_00581134) {
    iStack_6bc = 0;
    do {
      uVar12 = DAT_00581150;
      puVar7 = DAT_0058114c;
      puVar14 = (ushort *)(iStack_6bc + DAT_00581138);
      switch((char)puVar14[1]) {
      case '\a':
      case '\t':
        puVar23 = (ushort *)(DAT_00581154 + (uint)*puVar14 * 0x14);
        bVar2 = (byte)puVar23[1];
        piVar1 = (int *)(DAT_00581144 + *(char *)(DAT_00581154 + 3 + (uint)*puVar14 * 0x14) * 0x1c);
        if (((DAT_00583400 == '\0') || (DAT_005833e9 == '\0')) ||
           (((&DAT_00570382)[*piVar1 * 0x20] != '\0' &&
            ((DAT_00583401 == '\0' || (DAT_005833ef == '\0')))))) {
          uStack_6c0 = (uint)(byte)puVar23[2];
          uStack_6c4 = (uint)(byte)puVar23[6];
          iVar17 = (byte)puVar23[4] - uStack_6c0;
          iVar6 = (byte)puVar23[8] - uStack_6c4;
          iVar21 = iVar17 + 1;
          arg9 = iVar6 + 1;
          if ((*puVar23 & 4) != 0) {
            uStack_6c0 = uStack_6c0 - 1;
            uStack_6c4 = uStack_6c4 - 1;
            iVar21 = iVar17 + 3;
            arg9 = iVar6 + 3;
          }
          iVar6 = (int)(0x100 / (longlong)iVar21);
          iVar15 = ((uint)*(byte *)((int)puVar14 + 9) - (uint)(byte)puVar14[4]) + 1;
          iVar20 = (int)(0x100 / (longlong)arg9) * iVar6;
          iVar9 = (iVar20 + -1 + iVar15) / iVar20;
          iVar17 = iVar9 + DAT_00581150;
          puVar7 = operator_new(iVar17 * 0x20);
          if (puVar7 == (undefined4 *)0x0) {
            return 0;
          }
          if (-1 < iVar17 + -1) {
            puVar8 = puVar7 + 2;
            iVar16 = iVar17;
            do {
              puVar8[-2] = 0;
              puVar8[-1] = 0;
              *puVar8 = 0;
              puVar8[1] = 0;
              puVar8[2] = 0;
              puVar8[3] = 0;
              puVar8[4] = 0;
              puVar8[5] = 0;
              puVar8 = puVar8 + 8;
              iVar16 = iVar16 + -1;
            } while (iVar16 != 0);
          }
          puVar8 = DAT_0058114c;
          puVar19 = puVar7;
          for (iVar16 = (DAT_00581150 & 0x7ffffff) << 3; iVar16 != 0; iVar16 = iVar16 + -1) {
            *puVar19 = *puVar8;
            puVar8 = puVar8 + 1;
            puVar19 = puVar19 + 1;
          }
          for (iVar16 = 0; iVar16 != 0; iVar16 = iVar16 + -1) {
            *(undefined1 *)puVar19 = *(undefined1 *)puVar8;
            puVar8 = (undefined4 *)((int)puVar8 + 1);
            puVar19 = (undefined4 *)((int)puVar19 + 1);
          }
          sub_562941(DAT_0058114c);
          DAT_00581150 = DAT_00581150 + iVar9;
          bVar2 = (byte)puVar23[1];
          DAT_0058114c = puVar7;
          if (DAT_005833e1 == '\0') {
            descriptor[0] = 0x7c;
            descriptor[3] = 0x100;
            descriptor[2] = 0x100;
            descriptor[1] = 0x1007;
            puVar8 = (undefined4 *)(&PTR_DAT_00570370)[*piVar1 * 8];
            puVar19 = (descriptor + 18);
            for (iVar9 = 8; iVar9 != 0; iVar9 = iVar9 + -1) {
              *puVar19 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar19 = puVar19 + 1;
            }
            descriptor[26] = (uint)((byte)(-(uint)(DAT_005833e0 != '\0') >> 8) & 8 | 0x10) << 8;
            descriptor[27] = (-(uint)(DAT_005833e0 != '\0') & 0xfffffff0) + 0x10;
            descriptor[28] = 0;
            descriptor[29] = 0;
            if ((int)uVar12 < iVar17) {
              iVar9 = uVar12 << 5;
              uVar13 = uVar12;
              do {
                *(int *)(iVar9 + (int)DAT_0058114c) = *piVar1;
                *(undefined4 *)(iVar9 + 4 + (int)DAT_0058114c) = 0x100;
                *(undefined4 *)(iVar9 + 8 + (int)DAT_0058114c) = 0x100;
                iVar16 = (**(groove_com4 **)(*DAT_00582ccc + 0x18))
                                   ((int)DAT_00582ccc,(int)&descriptor[0],
                                    (int)(iVar9 + 0xc + (int)DAT_0058114c),0);
                if (iVar16 != 0) {
                  return 0;
                }
                arg0 = *(int **)(iVar9 + 0xc + (int)DAT_0058114c);
                (**(groove_com3 **)(*arg0 + 0x74))((int)arg0,8,(int)&color_key[0]);
                puVar8 = *(undefined4 **)(iVar9 + 0xc + (int)DAT_0058114c);
                iVar16 = (**(groove_com3 **)*puVar8)
                                   ((int)puVar8,(int)&DAT_0056e6dc,(int)(iVar9 + 0x10 + (int)DAT_0058114c));
                if (iVar16 != 0) {
                  return 0;
                }
                uVar13 = uVar13 + 1;
                *(undefined4 *)(iVar9 + 0x14 + (int)DAT_0058114c) = 0;
                iVar9 = iVar9 + 0x20;
              } while ((int)uVar13 < iVar17);
            }
          }
          else {
            uStack_698 = uVar12;
            if ((int)uVar12 < iVar17) {
              iVar9 = uVar12 << 5;
              do {
                *(int *)(iVar9 + (int)DAT_0058114c) = *piVar1;
                *(undefined4 *)(iVar9 + 4 + (int)DAT_0058114c) = 0x100;
                *(undefined4 *)(iVar9 + 8 + (int)DAT_0058114c) = 0x100;
                pvVar5 = operator_new((*(uint *)((&PTR_DAT_00570370)[*piVar1 * 8] + 0xc) & 0xffff)
                                      << 0xd);
                *(void **)(iVar9 + 0x1c + (int)DAT_0058114c) = pvVar5;
                if (*(int *)(iVar9 + 0x1c + (int)DAT_0058114c) == 0) {
                  return 0;
                }
                *(undefined4 *)(iVar9 + 0x14 + (int)DAT_0058114c) = 0;
                iVar9 = iVar9 + 0x20;
                uStack_698 = uStack_698 + 1;
              } while ((int)uStack_698 < iVar17);
            }
          }
          uStack_684 = (uint)(byte)puVar14[4];
          uStack_680 = (uint)*(byte *)((int)puVar14 + 9);
          *(char *)((int)puVar14 + 5) = (char)iVar15;
          *(undefined1 *)(puVar14 + 1) = 8;
          *(char *)(puVar14 + 2) = (char)puVar14[3];
          *(undefined1 *)(puVar14 + 3) = 0;
          *(undefined1 *)((int)puVar14 + 7) = 0;
          *(undefined1 *)(puVar14 + 4) = 0;
          *(undefined1 *)((int)puVar14 + 9) = 0;
          pvVar5 = operator_new(iVar15 * 0x14);
          *(void **)(puVar14 + 6) = pvVar5;
          if (pvVar5 == (void *)0x0) {
            return 0;
          }
          uStack_698 = 0;
          if (0 < iVar15) {
            iStack_6a8 = 0;
            do {
              iVar16 = ((int)uStack_698 % iVar6) * iVar21;
              iVar17 = (((int)uStack_698 % iVar20) / iVar6) * arg9;
              iVar9 = (int)uStack_698 / iVar20 + uVar12;
              *(ushort *)(iStack_6a8 + *(int *)(puVar14 + 6)) = *puVar23 | 0x20;
              *(char *)(iStack_6a8 + 2 + *(int *)(puVar14 + 6)) = (char)iVar9;
              *(undefined1 *)(iStack_6a8 + 3 + *(int *)(puVar14 + 6)) = 0xff;
              if ((*puVar23 & 4) == 0) {
                *(float *)(iStack_6a8 + 4 + *(int *)(puVar14 + 6)) = (float)iVar16 * _DAT_0056e118;
                *(float *)(iStack_6a8 + 8 + *(int *)(puVar14 + 6)) =
                     (float)(iVar21 + iVar16) * _DAT_0056e118;
                *(float *)(iStack_6a8 + 0xc + *(int *)(puVar14 + 6)) = (float)iVar17 * _DAT_0056e118
                ;
                iVar10 = iVar17;
              }
              else {
                *(float *)(iStack_6a8 + 4 + *(int *)(puVar14 + 6)) =
                     (float)(iVar16 + 1) * _DAT_0056e118;
                *(float *)(iStack_6a8 + 8 + *(int *)(puVar14 + 6)) =
                     (float)(iVar16 + -1 + iVar21) * _DAT_0056e118;
                *(float *)(iStack_6a8 + 0xc + *(int *)(puVar14 + 6)) =
                     (float)(iVar17 + 1) * _DAT_0056e118;
                iVar10 = iVar17 + -1;
              }
              *(float *)(iStack_6a8 + 0x10 + *(int *)(puVar14 + 6)) =
                   (float)(iVar10 + arg9) * _DAT_0056e118;
              if (DAT_005833e1 == '\0') {
                iVar10 = (**(groove_com5 **)(*(int *)DAT_0058114c[iVar9 * 8 + 3] + 100))
                                   ((int)DAT_0058114c[iVar9 * 8 + 3],0,(int)&descriptor[0],0x821,0);
                if (iVar10 != 0) {
                  return 0;
                }
                (**(code **)(&DAT_00570378 + *piVar1 * 0x20))
                          (descriptor[9],descriptor[4],puVar7[(char)bVar2 * 8 + 6],
                           puVar7[(char)bVar2 * 8 + 1],iVar16,iVar17,uStack_6c0,uStack_6c4,iVar21,
                           arg9,piVar1[5],(*puVar23 & 0x7000) >> 0xc,
                           CONCAT31((int3)((uint)(&PTR_DAT_00570370)[*piVar1 * 8] >> 8),
                                    (byte)*puVar23 >> 1) & 0xffffff01,
                           (int)(&PTR_DAT_00570370)[*piVar1 * 8]);
                (**(groove_com2 **)(*(int *)DAT_0058114c[iVar9 * 8 + 3] + 0x80))
                          ((int)DAT_0058114c[iVar9 * 8 + 3],0);
              }
              else {
                arg13 = (&PTR_DAT_00570370)[*piVar1 * 8];
                (**(code **)(&DAT_00570378 + *piVar1 * 0x20))
                          (DAT_0058114c[iVar9 * 8 + 7],
                           (uint)(DAT_0058114c[iVar9 * 8 + 1] * *(int *)(arg13 + 0xc)) >> 3,
                           puVar7[(char)bVar2 * 8 + 6],puVar7[(char)bVar2 * 8 + 1],iVar16,iVar17,
                           uStack_6c0,uStack_6c4,iVar21,arg9,piVar1[5],(*puVar23 & 0x7000) >> 0xc,
                           CONCAT31((int3)((uint)arg13 >> 8),(byte)*puVar23 >> 1) & 0xffffff01,
                           (int)arg13);
              }
              uVar4 = *(undefined2 *)(piVar1[5] + uStack_680 * 2);
              for (uVar13 = uStack_680; (int)uStack_684 < (int)uVar13; uVar13 = uVar13 - 1) {
                *(undefined2 *)(piVar1[5] + uVar13 * 2) =
                     *(undefined2 *)(piVar1[5] + -2 + uVar13 * 2);
              }
              *(undefined2 *)(piVar1[5] + uStack_684 * 2) = uVar4;
              uStack_698 = uStack_698 + 1;
              iStack_6a8 = iStack_6a8 + 0x14;
            } while ((int)uStack_698 < iVar15);
          }
          iVar17 = 5;
          puVar7 = *(undefined4 **)(puVar14 + 6);
          goto LAB_004080fe;
        }
        *(float *)(puVar23 + 2) =
             (float)(byte)puVar23[2] / (float)(int)DAT_0058114c[(char)bVar2 * 8 + 1];
        *(float *)(puVar23 + 4) =
             (float)((byte)puVar23[4] + 1) / (float)(int)puVar7[(char)bVar2 * 8 + 1];
        *(float *)(puVar23 + 6) = (float)(byte)puVar23[6] / (float)(int)puVar7[(char)bVar2 * 8 + 2];
        *(float *)(puVar23 + 8) =
             (float)((byte)puVar23[8] + 1) / (float)(int)puVar7[(char)bVar2 * 8 + 2];
        break;
      case '\b':
        iVar17 = 0;
        if (*(char *)((int)puVar14 + 5) != '\0') {
          iVar21 = 0;
          do {
            uVar12 = (uint)*(ushort *)(iVar21 + *(int *)(puVar14 + 6));
            if (uVar12 != 0xffffffff) {
              puVar7 = (undefined4 *)(DAT_00581154 + uVar12 * 0x14);
              puVar23 = (ushort *)(iVar21 + *(int *)(puVar14 + 6));
              for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
                *(undefined4 *)puVar23 = *puVar7;
                puVar7 = puVar7 + 1;
                puVar23 = puVar23 + 2;
              }
            }
            iVar17 = iVar17 + 1;
            iVar21 = iVar21 + 0x14;
          } while (iVar17 < (int)(uint)*(byte *)((int)puVar14 + 5));
        }
        puVar23 = *(ushort **)(puVar14 + 6);
        iVar17 = 5;
        puVar7 = (undefined4 *)(DAT_00581154 + (uint)*puVar14 * 0x14);
LAB_004080fe:
        for (; iVar17 != 0; iVar17 = iVar17 + -1) {
          *(undefined4 *)puVar23 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar23 = puVar23 + 2;
        }
        break;
      case '\n':
      case '\v':
        iVar17 = 0;
        if ((char)puVar14[4] != '\0') {
          iVar21 = 0;
          do {
            uVar12 = (uint)*(ushort *)(iVar21 + *(int *)(puVar14 + 6));
            if (uVar12 != 0xffffffff) {
              puVar7 = (undefined4 *)(DAT_00581154 + uVar12 * 0x14);
              puVar23 = (ushort *)(iVar21 + *(int *)(puVar14 + 6));
              for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
                *(undefined4 *)puVar23 = *puVar7;
                puVar7 = puVar7 + 1;
                puVar23 = puVar23 + 2;
              }
            }
            iVar17 = iVar17 + 1;
            iVar21 = iVar21 + 0x14;
          } while (iVar17 < (int)(uint)(byte)puVar14[4]);
        }
      }
      iStack_6b8 = iStack_6b8 + 1;
      iStack_6bc = iStack_6bc + 0x10;
    } while (iStack_6b8 < DAT_00581134);
  }
  iVar17 = 0;
  iStack_6b8 = 0;
  if (0 < (int)DAT_00581150) {
    do {
      puVar18 = (uint *)((int)DAT_0058114c + iVar17);
      uVar12 = *(uint *)((int)DAT_0058114c + iVar17) & 0x7f;
      if ((&DAT_00570384)[uVar12 * 0x20] != '\0') {
        if (((uVar12 == 4) || (uVar12 == 5)) || (uStack_6cc = 0, uVar12 == 7)) {
          uStack_6cc = 1;
        }
        sub_436CC0(uStack_6cc);
        sub_436D40(puVar18[7],puVar18[2] * puVar18[1]);
        sub_436E30(0,0x100,auStack_600);
        sub_4083A0(auStack_400,auStack_600,0,0x100,uStack_6cc);
        iVar21 = (**(groove_com5 **)(*DAT_00582ccc + 0x14))
                           ((int)DAT_00582ccc,0x44,(int)auStack_400,(int)(puVar18 + 5),0);
        if (((iVar21 != 0) ||
            (iVar21 = (**(groove_com2 **)(*(int *)puVar18[3] + 0x7c))((int)puVar18[3],puVar18[5]),
            iVar21 != 0)) ||
           (iVar21 = (**(groove_com5 **)(*(int *)puVar18[3] + 100))
                               ((int)puVar18[3],0,(int)&descriptor[0],0x821,0), iVar21 != 0)) {
          return 0;
        }
        iVar21 = 0;
        if (0 < (int)puVar18[2]) {
          do {
            sub_437AC0(0,puVar18[7] + puVar18[1] * iVar21 * 2,descriptor[4] * iVar21 + descriptor[9],
                       puVar18[1]);
            iVar21 = iVar21 + 1;
          } while (iVar21 < (int)puVar18[2]);
        }
        (**(groove_com2 **)(*(int *)puVar18[3] + 0x80))((int)puVar18[3],0);
        sub_426500();
        sub_562941(puVar18[7]);
        puVar18[7] = 0;
      }
      if ((*puVar18 & 0x80) != 0) {
        sub_562941(puVar18[6]);
        *puVar18 = *puVar18 & 0x7f;
      }
      puVar18[6] = 0;
      iVar21 = (**(groove_com3 **)(*DAT_00582cd4 + 0x98))((int)DAT_00582cd4,0,puVar18[4]);
      if (iVar21 != 0) {
        return 0;
      }
      DAT_006d7c54 = puVar18[4];
      iStack_6b8 = iStack_6b8 + 1;
      iVar17 = iVar17 + 0x20;
    } while (iStack_6b8 < (int)DAT_00581150);
  }
  fprintf(stderr, "[textures] upload complete\n");
  return 1;
}

