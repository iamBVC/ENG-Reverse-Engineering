/* sub_410700 @ 00410700   1874 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_410700(int param_1,int param_2,int param_3,float param_4)

{
  longlong lVar1;
  int iVar2;
  undefined4 *puVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  char local_60c [1024];
  undefined4 local_20c [20];
  undefined4 local_1bc;
  undefined4 local_1a8;
  LONG local_1a4;
  LONG local_1a0;
  LONG local_19c;
  LONG local_198;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_134;
  undefined4 local_100 [8];
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  WINDOWPLACEMENT local_cc;
  undefined *local_a0;
  char *local_9c;
  int local_98;
  undefined *local_94;
  char *local_90;
  int local_8c;
  undefined *local_88;
  char *local_84;
  int local_80;
  undefined *local_7c;
  char *local_78;
  int local_74;
  undefined *local_70;
  char *local_6c;
  int local_68;
  undefined *local_64;
  char *local_60;
  int local_5c;
  undefined *local_58;
  char *local_54;
  int local_50;
  undefined *local_4c;
  char *local_48;
  int local_44;
  undefined *local_40;
  char *local_3c;
  int local_38;
  undefined *local_34;
  char *local_30;
  int local_2c;
  undefined *local_28;
  char *local_24;
  int local_20;
  undefined **local_1c;
  char *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0056d716;
  local_10 = ExceptionList;
  local_14 = &stack0xfffff9e8;
  local_8 = 0;
  ExceptionList = &local_10;
  local_38 = (**(code **)(*DAT_00582ccc + 0x50))(DAT_00582ccc,DAT_005855d0,0x11);
  if (local_38 != 0) {
    local_3c = s_Couldn_t_set_exclusive_cooperati_0057194c;
    local_40 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_40,&DAT_0056eff0);
  }
  local_cc.length = 0x2c;
  local_cc.showCmd = 1;
  local_1a8 = 0x48;
  iVar2 = sub_41DB40(*(undefined4 *)(param_3 + 0x10),&local_1a8);
  if (iVar2 == 0) {
    local_cc.rcNormalPosition.left = 0;
    local_cc.rcNormalPosition.top = 0;
    local_cc.rcNormalPosition.right = sub_41DAD0(0);
    local_cc.rcNormalPosition.bottom = sub_41DAD0(1);
  }
  else {
    local_cc.rcNormalPosition.left = local_1a4;
    local_cc.rcNormalPosition.top = local_1a0;
    local_cc.rcNormalPosition.right = local_19c;
    local_cc.rcNormalPosition.bottom = local_198;
  }
  SetWindowPlacement(DAT_005855d0,&local_cc);
  ShowWindow(DAT_005855d0,1);
  UpdateWindow(DAT_005855d0);
  iVar2 = (**(code **)(*DAT_00582ccc + 0x54))
                    (DAT_00582ccc,*(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 0x10),
                     *(undefined4 *)(param_1 + 0xc),0x3c,0);
  if ((iVar2 != 0) &&
     (local_8c = (**(code **)(*DAT_00582ccc + 0x54))
                           (DAT_00582ccc,*(undefined4 *)(param_2 + 0xc),
                            *(undefined4 *)(param_2 + 0x10),*(undefined4 *)(param_1 + 0xc),0,0),
     local_8c != 0)) {
    local_90 = s_Couldn_t_set_the_display_mode_0057192c;
    local_94 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_94,&DAT_0056eff0);
  }
  local_148 = 0x7c;
  local_144 = 0x21;
  local_e0 = 0x2218;
  local_dc = 0;
  local_d8 = 0;
  local_d4 = 0;
  local_134 = 1;
  local_50 = (**(code **)(*DAT_00582ccc + 0x18))(DAT_00582ccc,&local_148,&DAT_00582cdc,0);
  if (local_50 != 0) {
    local_54 = s_Couldn_t_create_the_screen_buffe_00571908;
    local_58 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_58,&DAT_0056eff0);
  }
  local_20c[0] = 100;
  local_1bc = 0;
  (**(code **)(*DAT_00582cdc + 0x14))(DAT_00582cdc,0,0,0,0x400,local_20c);
  local_e0 = 4;
  puVar3 = &DAT_00582ce0;
  if (*(char *)((int)param_4 + 0x10) == '\0') {
    puVar3 = &DAT_00582ce4;
  }
  local_74 = (**(code **)(*DAT_00582cdc + 0x30))(DAT_00582cdc,&local_e0,puVar3);
  if (local_74 == 0) {
    if (*(char *)((int)param_4 + 0x10) != '\0') {
      local_140 = *(undefined4 *)(param_2 + 0x10);
      local_13c = *(undefined4 *)(param_2 + 0xc);
      local_144 = 0x1007;
      local_e0 = 0x2800;
      puVar3 = (undefined4 *)(param_2 + 0x5c);
      puVar7 = local_100;
      for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar7 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar7 = puVar7 + 1;
      }
      local_68 = (**(code **)(*DAT_00582ccc + 0x18))(DAT_00582ccc,&local_148,&DAT_00582ce4,0);
      if (local_68 != 0) {
        local_6c = s_Couldn_t_create_the_offscreen_bu_005718bc;
        local_70 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(&local_70,&DAT_0056eff0);
      }
    }
    if (*(char *)((int)param_4 + 0x15) != '\0') {
      if (*(char *)((int)param_4 + 0x11) == '\0') {
        local_144 = 0x1007;
        local_e0 = 0x22000;
        if (*(char *)((int)param_4 + 0x10) != '\0') {
          local_e0 = 0x22800;
        }
        local_140 = *(undefined4 *)(param_2 + 0x10);
        local_13c = *(undefined4 *)(param_2 + 0xc);
        puVar3 = (undefined4 *)(param_1 + 0x10);
        puVar7 = local_100;
        for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar7 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar7 = puVar7 + 1;
        }
        local_80 = (**(code **)(*DAT_00582ccc + 0x18))(DAT_00582ccc,&local_148,&DAT_00582ce8,0);
        if (local_80 != 0) {
          local_84 = s_Couldn_t_create_the_depth_buffer_00571898;
          local_88 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
          __CxxThrowException_8(&local_88,&DAT_0056eff0);
        }
        local_98 = (**(code **)(*DAT_00582ce4 + 0xc))(DAT_00582ce4,DAT_00582ce8);
        if (local_98 != 0) {
          local_9c = s_Couldn_t_attach_the_depth_buffer_00571874;
          local_a0 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
          __CxxThrowException_8(&local_a0,&DAT_0056eff0);
        }
      }
      else {
        DAT_005832f0 = _malloc(*(int *)(param_2 + 0x10) * *(int *)(param_2 + 0xc) * 2);
        if (DAT_005832f0 == (void *)0x0) {
          local_18 = s_Couldn_t_create_the_depth_buffer_00571898;
          local_1c = &PTR_sub_413B20_0056e1c4;
                    /* WARNING: Subroutine does not return */
          __CxxThrowException_8(&local_1c,&DAT_0056f000);
        }
      }
    }
    if ((*(byte *)(param_2 + 0x60) & 0x20) != 0) {
      for (param_4 = 0.0; (int)param_4 < 8; param_4 = (float)((int)param_4 + 1)) {
        for (uVar6 = 0; (int)uVar6 < 4; uVar6 = uVar6 + 1) {
          for (uVar8 = 0; (int)uVar8 < 8; uVar8 = uVar8 + 1) {
            iVar2 = (int)param_4 * 0xff;
            iVar5 = (((int)param_4 * 4 | uVar6) << 3 | uVar8) * 4;
            local_60c[iVar5] =
                 ((char)(iVar2 / 7) + (char)(iVar2 >> 0x1f)) -
                 (char)((longlong)iVar2 * 0x92492493 >> 0x3f);
            lVar1 = (longlong)(int)(uVar6 * 0xff) * 0x55555556;
            local_60c[iVar5 + 1] = (char)((ulonglong)lVar1 >> 0x20) - (char)(lVar1 >> 0x3f);
            iVar2 = uVar8 * 0xff;
            local_60c[iVar5 + 2] =
                 ((char)(iVar2 / 7) + (char)(iVar2 >> 0x1f)) -
                 (char)((longlong)iVar2 * 0x92492493 >> 0x3f);
          }
        }
      }
      local_20 = (**(code **)(*DAT_00582ccc + 0x14))(DAT_00582ccc,0x44,local_60c,&DAT_005832f4,0);
      if (local_20 != 0) {
        local_24 = s_Couldn_t_create_the_palette_00571858;
        local_28 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(&local_28,&DAT_0056eff0);
      }
      local_2c = (**(code **)(*DAT_00582cdc + 0x7c))(DAT_00582cdc,DAT_005832f4);
      if (local_2c != 0) {
        local_30 = s_Couldn_t_attach_the_palette_to_t_00571824;
        local_34 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(&local_34,&DAT_0056eff0);
      }
      local_44 = (**(code **)(*DAT_00582ce4 + 0x7c))(DAT_00582ce4,DAT_005832f4);
      if (local_44 != 0) {
        local_48 = s_Couldn_t_attach_the_palette_to_t_00571824;
        local_4c = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(&local_4c,&DAT_0056eff0);
      }
    }
    if (*(char *)(param_3 + 0x16) != '\0') {
      (**(code **)*DAT_00582cdc)(DAT_00582cdc,&DAT_0056e6fc,&DAT_00582cec);
      if (DAT_00582cec == (int *)0x0) {
        *(undefined1 *)(param_3 + 0x16) = 0;
      }
      iVar2 = (**(code **)(*DAT_00582cec + 0xc))(DAT_00582cec,0,&DAT_00582cf0);
      if (iVar2 != 0) {
        for (iVar2 = 0; iVar2 < 0x100; iVar2 = iVar2 + 1) {
          sVar4 = (short)(iVar2 << 8) + (short)iVar2;
          (&DAT_005830f0)[iVar2] = sVar4;
          (&DAT_00582ef0)[iVar2] = sVar4;
          (&DAT_00582cf0)[iVar2] = sVar4;
        }
      }
    }
    local_5c = (**(code **)(*DAT_00582ce4 + 0x54))(DAT_00582ce4,param_2 + 0x5c);
    if (local_5c == 0) {
      DAT_00583374 = *(int *)(param_2 + 0xc);
      DAT_00583378 = *(int *)(param_2 + 0x10);
      _DAT_00583388 = (float)DAT_00583374;
      DAT_0058337c = *(undefined4 *)(param_1 + 0xc);
      DAT_00583380 = *(int *)(param_2 + 0x70) == 0x7e0;
      _DAT_00583384 = 0x3f400000;
      uVar6 = ((uint)_DAT_00583388 >> 0x17 & 0xff) - 0x17;
      if ((int)uVar6 < 1) {
        if (uVar6 == 0xffffffe9) {
          param_4 = (float)CONCAT31((uint3)((uint)_DAT_00583388 >> 8) & 0x800000,1);
        }
        else {
          param_4 = (float)(0x400000 >> (-(char)uVar6 & 0x1fU) | (uint)_DAT_00583388 & 0x80000000);
        }
      }
      else {
        param_4 = (float)((uVar6 & 0xff) << 0x17 | (uint)_DAT_00583388 & 0x80000000);
      }
      DAT_00583390 = _DAT_00583388 - param_4;
      _DAT_0058338c = (float)DAT_00583378;
      uVar6 = ((uint)_DAT_0058338c >> 0x17 & 0xff) - 0x17;
      if ((int)uVar6 < 1) {
        if (uVar6 == 0xffffffe9) {
          param_4 = (float)CONCAT31((uint3)((uint)_DAT_0058338c >> 8) & 0x800000,1);
        }
        else {
          param_4 = (float)(0x400000 >> (-(char)uVar6 & 0x1fU) | (uint)_DAT_0058338c & 0x80000000);
        }
      }
      else {
        param_4 = (float)((uVar6 & 0xff) << 0x17 | (uint)_DAT_0058338c & 0x80000000);
      }
      DAT_00583394 = _DAT_0058338c - param_4;
      _DAT_00583388 = _DAT_00583388 * _DAT_0056e158;
      _DAT_0058338c = _DAT_0058338c * _DAT_0056e158;
      sub_4138A0(0,0,0x200,0xf0);
      ExceptionList = local_10;
      return 1;
    }
    local_60 = s_Couldn_t_check_display_pixel_for_00571800;
    local_64 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_64,&DAT_0056eff0);
  }
  local_78 = s_Couldn_t_get_the_offscreen_buffe_005718e4;
  local_7c = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(&local_7c,&DAT_0056eff0);
}

