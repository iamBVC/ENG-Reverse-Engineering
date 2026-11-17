/* sub_211089E0 @ 211089e0   810 bytes */

undefined4 * __fastcall sub_211089E0(undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  void *pvVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  uint *puVar11;
  undefined4 *puVar12;
  int *piVar13;
  uint local_68;
  undefined4 local_50;
  char *local_4c;
  code *local_48;
  undefined4 local_44;
  undefined4 local_40;
  char *local_3c;
  code *local_38;
  undefined4 local_34;
  undefined4 local_30;
  char *local_2c;
  code *local_28;
  undefined4 local_24;
  undefined4 local_20;
  char *local_1c;
  code *local_18;
  undefined4 local_14;
  undefined4 local_10;
  char *local_c;
  code *local_8;
  undefined4 local_4;
  
  local_50 = 0;
  local_4c = s_MIXER_init_21114128;
  local_48 = sub_2110D159;
  local_44 = 0;
  local_40 = 0;
  local_3c = s_MIXER_shutdown_211141a4;
  local_38 = sub_2110D173;
  local_34 = 0;
  local_30 = 0;
  local_2c = s_MIXER_flush_211144bc;
  local_28 = sub_2110D183;
  local_24 = 0;
  local_20 = 0;
  local_1c = s_MIXER_merge_21114628;
  local_18 = sub_2110D1D7;
  local_14 = 0;
  local_10 = 0;
  local_c = s_MIXER_copy_211144c8;
  local_8 = sub_2110D366;
  local_4 = 0;
  puVar3 = operator_new(0x810);
  if (puVar3 == (uint *)0x0) {
    puVar3 = (uint *)0x0;
  }
  else {
    *puVar3 = 0x80;
    pvVar4 = operator_new(0x9400);
    puVar3[0x203] = (uint)pvVar4;
    uVar9 = 0;
    if (*puVar3 != 0) {
      iVar5 = 0;
      do {
        *(uint *)(puVar3[0x203] + iVar5 + 4) = puVar3[0x203] + iVar5 + -0x128;
        *(uint *)(iVar5 + puVar3[0x203]) = iVar5 + 0x128 + puVar3[0x203];
        *(undefined4 *)(iVar5 + 0x14 + puVar3[0x203]) = 0xffffffff;
        uVar9 = uVar9 + 1;
        iVar5 = iVar5 + 0x128;
      } while (uVar9 < *puVar3);
    }
    *(undefined4 *)(puVar3[0x203] + 4) = 0;
    *(undefined4 *)((puVar3[0x203] - 0x128) + *puVar3 * 0x128) = 0;
    puVar3[2] = puVar3[0x203];
    puVar3[1] = 0;
    puVar11 = puVar3 + 3;
    for (iVar5 = 0x200; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
  }
  param_1[1] = puVar3;
  puVar3 = operator_new(0x10);
  if (puVar3 == (uint *)0x0) {
    puVar3 = (uint *)0x0;
  }
  else {
    *puVar3 = 0x20;
    pvVar4 = operator_new(0x600);
    puVar3[3] = (uint)pvVar4;
    uVar9 = 0;
    if (*puVar3 != 0) {
      iVar5 = 0;
      do {
        *(uint *)(puVar3[3] + iVar5 + 4) = puVar3[3] + iVar5 + -0x30;
        *(uint *)(iVar5 + puVar3[3]) = iVar5 + 0x30 + puVar3[3];
        *(undefined4 *)(iVar5 + 8 + puVar3[3]) = 0xffffffff;
        puVar12 = (undefined4 *)(iVar5 + 0x10 + puVar3[3]);
        for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar12 = 0;
          puVar12 = puVar12 + 1;
        }
        uVar9 = uVar9 + 1;
        iVar5 = iVar5 + 0x30;
      } while (uVar9 < *puVar3);
    }
    *(undefined4 *)(puVar3[3] + 4) = 0;
    *(undefined4 *)(*puVar3 * 0x30 + -0x30 + puVar3[3]) = 0;
    puVar3[1] = 0;
    puVar3[2] = puVar3[3];
  }
  *param_1 = puVar3;
  if (puVar3[2] == 0) {
    uVar1 = *puVar3;
    uVar2 = puVar3[3];
    uVar9 = uVar1 + 0x20;
    piVar6 = operator_new(uVar9 * 0x30);
    if (piVar6 == (int *)0x0) goto LAB_21108cdc;
    if (0 < (int)uVar1) {
      piVar7 = piVar6;
      local_68 = uVar1;
      do {
        piVar10 = (int *)((uVar2 - (int)piVar6) + (int)piVar7);
        piVar13 = piVar7;
        for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
          *piVar13 = *piVar10;
          piVar10 = piVar10 + 1;
          piVar13 = piVar13 + 1;
        }
        if (*piVar7 != 0) {
          *piVar7 = (int)piVar6 + (*piVar7 - uVar2);
        }
        if (piVar7[1] != 0) {
          piVar7[1] = (int)piVar6 + (piVar7[1] - uVar2);
        }
        piVar7 = piVar7 + 0xc;
        local_68 = local_68 - 1;
      } while (local_68 != 0);
    }
    if ((int)uVar1 < (int)uVar9) {
      piVar7 = piVar6 + uVar1 * 0xc + -0xc;
      iVar5 = uVar9 - uVar1;
      do {
        piVar7[0xe] = -1;
        piVar7[0xd] = (int)piVar7;
        piVar7[0xc] = (int)(piVar7 + 0x18);
        piVar7 = piVar7 + 0xc;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    piVar6[uVar1 * 0xc + 1] = 0;
    piVar6[uVar9 * 0xc + -0xc] = 0;
    puVar3[1] = (int)piVar6 + (puVar3[1] - uVar2);
    puVar3[2] = (uint)(piVar6 + uVar1 * 0xc);
    *puVar3 = uVar9;
    sub_2110D4F4((LPVOID)puVar3[3]);
    puVar3[3] = (uint)piVar6;
  }
  puVar11 = (uint *)puVar3[2];
  puVar3[2] = *puVar11;
  *puVar11 = puVar3[1];
  puVar11[1] = 0;
  if (puVar3[1] != 0) {
    *(uint **)(puVar3[1] + 4) = puVar11;
  }
  puVar3[1] = (uint)puVar11;
  puVar11[2] = ((int)puVar11 - puVar3[3]) / 0x30;
LAB_21108cdc:
  param_1[2] = 0;
  piVar6 = sub_21109A40((int *)*param_1);
  param_1[3] = piVar6;
  sub_211090B0(param_1,piVar6[2],(int *)s_AAL_Mixer_21114134,(int)&local_50,5);
  return param_1;
}

