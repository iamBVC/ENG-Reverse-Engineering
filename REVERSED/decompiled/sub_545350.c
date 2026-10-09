/* sub_545350 @ 00545350   1375 bytes */

undefined4 sub_545350(uint param_1,void *param_2,undefined4 param_3)

{
  ushort *puVar1;
  void *pvVar2;
  ushort uVar3;
  undefined2 uVar4;
  void *pvVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  undefined4 local_3c [14];
  int iStack_4;
  
  pvVar2 = param_2;
  uVar14 = param_1;
  switch(param_3) {
  case 0:
    sub_415AB0(param_2,&param_1);
    pvVar5 = _malloc(0xc);
    iVar11 = 0;
    puVar9 = local_3c;
    *(void **)(DAT_006d9490 + 0x44) = pvVar5;
    **(undefined4 **)(DAT_006d9490 + 0x50) = 3;
    do {
      pvVar5 = _malloc(0x18);
      *(void **)(*(int *)(DAT_006d9490 + 0x44) + iVar11) = pvVar5;
      sub_415A90(pvVar2,puVar9,0x14);
      iVar11 = iVar11 + 4;
      puVar9 = puVar9 + 5;
    } while (iVar11 < 0xc);
    puVar9 = local_3c;
    iVar11 = 0;
    do {
      param_1 = puVar9[4];
      param_3 = 0x20677663;
      puVar6 = operator_new(param_1 + 0x2c);
      *puVar6 = param_3;
      puVar6[1] = param_1;
      puVar15 = puVar9;
      puVar16 = puVar6 + 2;
      for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar16 = *puVar15;
        puVar15 = puVar15 + 1;
        puVar16 = puVar16 + 1;
      }
      sub_415A90(param_2,puVar6 + 7,param_1);
      iVar8 = _AAL_LoadResource_8(puVar6,0);
      puVar6[5] = 0;
      puVar6[6] = 0;
      *(undefined4 *)(iStack_4 + 0x1c + (int)puVar6) = 0;
      *(undefined4 *)((int)puVar6 + iStack_4 + 0x20) = 0;
      *(undefined4 *)((int)puVar6 + iStack_4 + 0x24) = 0;
      *(undefined4 *)((int)puVar6 + iStack_4 + 0x28) = 0;
      if (iVar8 == 0) {
        sub_426500(s_Failed_to_load_fesound_id__d_00578e28,iVar11);
      }
      uVar10 = _AAL_GetDataSize_4(iVar8);
      **(undefined4 **)(*(int *)(DAT_006d9490 + 0x44) + iVar11 * 4) = uVar10;
      iVar7 = _AAL_GetSampleRate_4(iVar8);
      iVar7 = iVar7 << 0xc;
      *(short *)(*(int *)(*(int *)(DAT_006d9490 + 0x44) + iVar11 * 4) + 4) =
           ((short)(iVar7 / 0xac44) + (short)(iVar7 >> 0x1f)) -
           (short)((longlong)iVar7 * 0x2f8df18f >> 0x3f);
      uVar4 = _AAL_GetADSVolume_4(iVar8);
      *(undefined2 *)(*(int *)(*(int *)(DAT_006d9490 + 0x44) + iVar11 * 4) + 6) = uVar4;
      uVar3 = _AAL_GetADSFlags_4(iVar8);
      *(ushort *)(*(int *)(*(int *)(DAT_006d9490 + 0x44) + iVar11 * 4) + 8) = uVar3 | 8;
      puVar1 = (ushort *)(*(int *)(*(int *)(DAT_006d9490 + 0x44) + iVar11 * 4) + 8);
      *puVar1 = *puVar1 & 0xfffe;
      uVar4 = _AAL_GetLoopType_4(iVar8);
      iVar11 = iVar11 + 1;
      *(undefined2 *)(*(int *)(*(int *)(DAT_006d9490 + 0x44) + -4 + iVar11 * 4) + 10) = uVar4;
      *(int *)(*(int *)(*(int *)(DAT_006d9490 + 0x44) + -4 + iVar11 * 4) + 0x14) = iVar8;
      *(undefined4 **)(*(int *)(*(int *)(DAT_006d9490 + 0x44) + -4 + iVar11 * 4) + 0x10) = puVar6;
      puVar9 = puVar9 + 5;
    } while (iVar11 < 3);
    return 1;
  case 1:
    uVar10 = sub_41EF00(*(int *)(param_1 + 0x1c) << 2);
    *(undefined4 *)(uVar14 + 0x18) = uVar10;
    uVar13 = 0;
    *(undefined4 *)(*(int *)(DAT_006d9490 + 0x50) + 4) = *(undefined4 *)(uVar14 + 0x1c);
    if (*(int *)(uVar14 + 0x1c) != 0) {
      do {
        uVar10 = sub_41EF00(0x18);
        pvVar2 = param_2;
        *(undefined4 *)(*(int *)(uVar14 + 0x18) + uVar13 * 4) = uVar10;
        sub_415AB0(param_2,&param_3);
        sub_415AB0(pvVar2,&param_1);
        puVar9 = operator_new(param_1 + 0x18);
        uVar12 = 8;
        *puVar9 = param_3;
        puVar9[1] = param_1;
        if (8 < param_1 + 8) {
          do {
            sub_415AD0(param_2,uVar12 + (int)puVar9);
            uVar12 = uVar12 + 1;
          } while (uVar12 < param_1 + 8);
        }
        iVar11 = _AAL_LoadResource_8(puVar9,0);
        if (iVar11 == 0) {
          sub_426500(s_Failed_to_load_generic_sound_id___00578e04,uVar13);
        }
        *puVar9 = 0;
        puVar9[1] = 0;
        *(undefined4 *)(iStack_4 + 8 + (int)puVar9) = 0;
        *(undefined4 *)((int)puVar9 + iStack_4 + 0xc) = 0;
        *(undefined4 *)((int)puVar9 + iStack_4 + 0x10) = 0;
        *(undefined4 *)((int)puVar9 + iStack_4 + 0x14) = 0;
        *(int *)(*(int *)(*(int *)(uVar14 + 0x18) + uVar13 * 4) + 0x14) = iVar11;
        *(undefined4 **)(*(int *)(*(int *)(uVar14 + 0x18) + uVar13 * 4) + 0x10) = puVar9;
        uVar10 = _AAL_GetDataSize_4(iVar11);
        **(undefined4 **)(*(int *)(uVar14 + 0x18) + uVar13 * 4) = uVar10;
        iVar8 = _AAL_GetSampleRate_4(iVar11);
        iVar8 = iVar8 << 0xc;
        *(short *)(*(int *)(*(int *)(uVar14 + 0x18) + uVar13 * 4) + 4) =
             ((short)(iVar8 / 0xac44) + (short)(iVar8 >> 0x1f)) -
             (short)((longlong)iVar8 * 0x2f8df18f >> 0x3f);
        uVar4 = _AAL_GetADSVolume_4(iVar11);
        *(undefined2 *)(*(int *)(*(int *)(uVar14 + 0x18) + uVar13 * 4) + 6) = uVar4;
        uVar4 = _AAL_GetADSFlags_4(iVar11);
        *(undefined2 *)(*(int *)(*(int *)(uVar14 + 0x18) + uVar13 * 4) + 8) = uVar4;
        uVar4 = _AAL_GetLoopType_4(iVar11);
        uVar13 = uVar13 + 1;
        *(undefined2 *)(*(int *)(*(int *)(uVar14 + 0x18) + -4 + uVar13 * 4) + 10) = uVar4;
      } while (uVar13 < *(uint *)(uVar14 + 0x1c));
      return 1;
    }
    break;
  case 2:
    sub_415AB0(param_2,&param_2);
    iVar8 = sub_41EF00((int)param_2 << 4);
    uVar14 = 0;
    param_1 = ((uint)param_2 & 0xfffffff) << 2;
    iVar11 = iVar8;
    if (((uint)param_2 & 0xfffffff) != 0) {
      do {
        sub_415AB0(pvVar2,iVar11);
        iVar11 = iVar11 + 4;
        uVar14 = uVar14 + 1;
      } while (uVar14 < param_1);
    }
    sub_5465D0(iVar8,param_2);
    return 1;
  case 4:
    uVar10 = sub_41EF00(*(int *)(param_1 + 0x24) << 2);
    pvVar2 = param_2;
    *(undefined4 *)(uVar14 + 0x20) = uVar10;
    uVar13 = 0;
    if (*(int *)(uVar14 + 0x24) != 0) {
      do {
        uVar10 = sub_41EF00(0x18);
        *(undefined4 *)(*(int *)(uVar14 + 0x20) + uVar13 * 4) = uVar10;
        sub_415AB0(pvVar2,&param_1);
        **(uint **)(*(int *)(uVar14 + 0x20) + uVar13 * 4) = param_1;
        sub_415AB0(pvVar2,&param_3);
        sub_415AB0(pvVar2,&param_1);
        param_2 = operator_new(param_1);
        uVar12 = 0;
        if (param_1 != 0) {
          do {
            sub_415AD0(pvVar2,(int)param_2 + uVar12);
            uVar12 = uVar12 + 1;
          } while (uVar12 < param_1);
        }
        iVar11 = uVar13 * 4;
        uVar13 = uVar13 + 1;
        *(void **)(*(int *)(*(int *)(uVar14 + 0x20) + iVar11) + 0x10) = param_2;
      } while (uVar13 < *(uint *)(uVar14 + 0x24));
    }
    sub_5472A0(4,*(undefined4 *)(**(int **)(uVar14 + 0x20) + 0x10),1,
               *(undefined4 *)((*(int **)(uVar14 + 0x20))[2] + 0x10));
    puVar9 = *(undefined4 **)(*(int *)(uVar14 + 0x20) + 4);
    sub_5471F0(4,puVar9[4],*puVar9);
    sub_415AB0(pvVar2,&param_1);
    if (param_1 != 0) {
      if (DAT_006d949c == 0) {
        sub_415B10(pvVar2,param_1 * 0x28);
      }
      else {
        *(uint *)(DAT_006d949c + 0xa0) = param_1;
        uVar10 = sub_41EF00(param_1 * 4);
        uVar14 = 0;
        *(undefined4 *)(DAT_006d949c + 0xa4) = uVar10;
        if (param_1 != 0) {
          do {
            iVar11 = sub_41EF00(0x28);
            uVar13 = 0;
            do {
              sub_415AD0(pvVar2,iVar11 + uVar13);
              uVar13 = uVar13 + 1;
            } while (uVar13 < 0x28);
            uVar14 = uVar14 + 1;
            *(int *)(*(int *)(DAT_006d949c + 0xa4) + -4 + uVar14 * 4) = iVar11;
          } while (uVar14 < param_1);
          return 1;
        }
      }
    }
  }
  return 1;
}

