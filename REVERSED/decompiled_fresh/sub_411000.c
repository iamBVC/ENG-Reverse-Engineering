/* sub_411000 @ 00411000   1019 bytes */

undefined4 sub_411000(int param_1)

{
  int iVar1;
  char cVar2;
  char cVar3;
  uint uVar4;
  char *pcVar5;
  bool bVar6;
  bool bVar7;
  undefined1 local_a8 [8];
  int local_a0;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined **local_6c;
  char *local_68;
  int local_64;
  undefined **local_60;
  char *local_5c;
  int local_58;
  undefined **local_54;
  char *local_50;
  int local_4c;
  undefined **local_48;
  char *local_44;
  int local_40;
  undefined **local_3c;
  char *local_38;
  int local_34;
  undefined **local_30;
  char *local_2c;
  int local_28;
  undefined **local_24;
  char *local_20;
  undefined **local_1c;
  char *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  iVar1 = param_1;
  cVar2 = DAT_00583380;
  puStack_c = &LAB_0056d72b;
  local_10 = ExceptionList;
  local_14 = &stack0xffffff3c;
  if (*(char *)(param_1 + 0x11) == '\0') {
    local_8 = 0;
    ExceptionList = &local_10;
    local_40 = (**(code **)(*DAT_00582cd0 + 0x20))
                         (DAT_00582cd0,*(undefined4 *)(param_1 + 0xc),DAT_00582ce4,&DAT_00582cd4,0);
    if (local_40 != 0) {
      local_44 = s_Couldn_t_create_Direct3D_device_00571a94;
      local_48 = &PTR_sub_414460_0056e1d0;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(&local_48,&DAT_0056f168);
    }
    local_a0 = iVar1;
    param_1 = CONCAT13(4,(undefined3)param_1);
    if (DAT_005834d4 != 0) {
      sub_562B75((int)&param_1 + 3,1,1,DAT_005834d4);
      uVar4 = 0xffffffff;
      pcVar5 = s_Texture_Formats_00571a84;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
      sub_562B75(s_Texture_Formats_00571a84,1,~uVar4,DAT_005834d4);
    }
    local_58 = (**(code **)(*DAT_00582cd4 + 0x20))(DAT_00582cd4,&LAB_00412710,local_a8);
    param_1 = CONCAT13(5,(undefined3)param_1);
    if (DAT_005834d4 != 0) {
      sub_562B75((int)&param_1 + 3,1,1,DAT_005834d4);
    }
    if (local_58 != 0) {
      local_5c = s_Couldn_t_enumerate_texture_forma_00571a60;
      local_60 = &PTR_sub_414460_0056e1d0;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(&local_60,&DAT_0056f168);
    }
    bVar6 = *(int *)(iVar1 + 0x58) != 0;
    bVar7 = *(int *)(iVar1 + 0x78) != 0;
    *(bool *)(iVar1 + 0x19) = bVar6;
    *(bool *)(iVar1 + 0x1a) = bVar7;
    if ((!bVar6) && (!bVar7)) {
      local_20 = s_Couldn_t_find_suitable_texture_f_00571a38;
      local_24 = &PTR_sub_413B20_0056e1c4;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(&local_24,&DAT_0056f000);
    }
    if ((*(char *)(iVar1 + 0x28) == '\0') || (*(int *)(iVar1 + 0x98) == 0)) {
      cVar2 = '\0';
    }
    else {
      cVar2 = '\x01';
    }
    *(char *)(iVar1 + 0x1c) = cVar2;
    if (((*(char *)(iVar1 + 0x13) == '\0') || (cVar2 == '\0')) || (*(int *)(iVar1 + 0xb8) == 0)) {
      cVar3 = '\0';
    }
    else {
      cVar3 = '\x01';
    }
    *(char *)(iVar1 + 0x14) = cVar3;
    if (((*(char *)(iVar1 + 0x26) == '\0') || (*(char *)(iVar1 + 0x21) == '\0')) ||
       ((cVar2 == '\0' || (*(int *)(iVar1 + 0xb8) == 0)))) {
      cVar2 = '\0';
    }
    else {
      cVar2 = '\x01';
    }
    *(char *)(iVar1 + 0x2b) = cVar2;
    if (((*(char *)(iVar1 + 0x1b) == '\0') && (cVar2 == '\0')) && (cVar3 == '\0')) {
      local_18 = s_Couldn_t_find_a_way_to_colourkey_00571a14;
      local_1c = &PTR_sub_413B20_0056e1c4;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(&local_1c,&DAT_0056f000);
    }
    local_28 = (**(code **)(*DAT_00582cd0 + 0x18))(DAT_00582cd0,&DAT_00582cd8,0);
    if (local_28 != 0) {
      local_2c = s_Couldn_t_create_viewport_005719f8;
      local_30 = &PTR_sub_414460_0056e1d0;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(&local_30,&DAT_0056f168);
    }
    local_64 = (**(code **)(*DAT_00582cd4 + 0x14))(DAT_00582cd4,DAT_00582cd8);
    if (local_64 != 0) {
      local_68 = s_Couldn_t_add_viewport_to_Direct3_005719cc;
      local_6c = &PTR_sub_414460_0056e1d0;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(&local_6c,&DAT_0056f168);
    }
    local_34 = (**(code **)(*DAT_00582cd4 + 0x30))(DAT_00582cd4,DAT_00582cd8);
    if (local_34 != 0) {
      local_38 = s_Couldn_t_select_viewport_005719b0;
      local_3c = &PTR_sub_414460_0056e1d0;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(&local_3c,&DAT_0056f168);
    }
    local_88 = DAT_00583378;
    local_98 = 0x2c;
    local_94 = 0;
    local_90 = 0;
    local_8c = DAT_00583374;
    local_84 = 0xbf800000;
    local_80 = 0xbf800000;
    local_7c = 0x40000000;
    local_78 = 0x40000000;
    local_74 = 0;
    local_70 = 0x3f800000;
    local_4c = (**(code **)(*DAT_00582cd8 + 0x44))(DAT_00582cd8,&local_98);
    if (local_4c != 0) {
      local_50 = s_Couldn_t_set_viewport_up_00571994;
      local_54 = &PTR_sub_414460_0056e1d0;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(&local_54,&DAT_0056f168);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x7c) = 0x40;
    *(undefined4 *)(param_1 + 0x78) = 0x20;
    *(undefined4 *)(param_1 + 0x80) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0x10;
    if (cVar2 == '\0') {
      *(undefined4 *)(param_1 + 0x88) = 0x7c00;
      *(undefined4 *)(param_1 + 0x8c) = 0x3e0;
      *(undefined4 *)(param_1 + 0x90) = 0x1f;
      *(undefined4 *)(param_1 + 0x94) = 0;
      *(undefined4 *)(param_1 + 0x98) = 0x20;
      *(undefined4 *)(param_1 + 0x9c) = 0x41;
      *(undefined4 *)(param_1 + 0xa0) = 0;
      *(undefined4 *)(param_1 + 0xa4) = 0x20;
      *(undefined4 *)(param_1 + 0xa8) = 0x7c00;
      *(undefined4 *)(param_1 + 0xac) = 0x3e00000;
    }
    else {
      *(undefined4 *)(param_1 + 0x88) = 0xf800;
      *(undefined4 *)(param_1 + 0x8c) = 0x7e0;
      *(undefined4 *)(param_1 + 0x90) = 0x1f;
      *(undefined4 *)(param_1 + 0x94) = 0;
      *(undefined4 *)(param_1 + 0x98) = 0x20;
      *(undefined4 *)(param_1 + 0x9c) = 0x41;
      *(undefined4 *)(param_1 + 0xa0) = 0;
      *(undefined4 *)(param_1 + 0xa4) = 0x20;
      *(undefined4 *)(param_1 + 0xa8) = 0xf800;
      *(undefined4 *)(param_1 + 0xac) = 0x7e00000;
    }
    *(undefined4 *)(param_1 + 0xb0) = 0x1f;
    *(undefined4 *)(param_1 + 0xb4) = 0xf8000000;
  }
  ExceptionList = local_10;
  return 1;
}

