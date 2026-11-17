/* sub_411D60 @ 00411d60   1362 bytes */

undefined4
sub_411D60(int param_1,char *param_2,char *param_3,void *param_4,undefined4 param_5,
          undefined4 *param_6)

{
  int *piVar1;
  int *piVar2;
  undefined1 *puVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  int *piVar9;
  char *pcVar10;
  char *pcVar11;
  undefined *local_44 [2];
  int local_3c;
  undefined **local_38 [2];
  int local_30;
  undefined4 *local_2c;
  int local_28;
  int *local_24;
  undefined **local_20;
  char *local_1c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0056d773;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffa0;
  local_2c = param_6;
  local_28 = 0;
  local_24 = (int *)0x0;
  local_15 = 2;
  ExceptionList = &local_10;
  puVar3 = &stack0xffffffa0;
  if ((DAT_005834d4 != 0) &&
     (ExceptionList = &local_10, sub_562B75(&local_15,1,1,DAT_005834d4), puVar3 = local_14,
     param_3 != (char *)0x0)) {
    uVar6 = 0xffffffff;
    pcVar11 = param_3;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar4 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar4 != '\0');
    sub_562B75(param_3,1,~uVar6,DAT_005834d4);
    puVar3 = local_14;
  }
  local_14 = puVar3;
  local_15 = 6;
  if (DAT_005834d4 != 0) {
    sub_562B75(&local_15,1,1,DAT_005834d4);
    uVar6 = 0xffffffff;
    pcVar11 = &DAT_00571bd0;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar4 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar4 != '\0');
    sub_562B75(&DAT_00571bd0,1,~uVar6,DAT_005834d4);
    if (param_1 != 0) {
      sub_562B75(param_1,0x10,1,DAT_005834d4);
    }
  }
  pcVar11 = param_2;
  uVar6 = 0xffffffff;
  pcVar10 = param_2;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar4 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar4 != '\0');
  param_2 = (char *)CONCAT13(7,param_2._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_2 + 3,1,1,DAT_005834d4);
    uVar7 = 0xffffffff;
    pcVar10 = s_Description_00571bc4;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar4 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar4 != '\0');
    sub_562B75(s_Description_00571bc4,1,~uVar7,DAT_005834d4);
    if (pcVar11 != (char *)0x0) {
      sub_562B75(pcVar11,~uVar6,1,DAT_005834d4);
    }
  }
  pcVar11 = param_3;
  uVar6 = 0xffffffff;
  pcVar10 = param_3;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar4 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar4 != '\0');
  param_2 = (char *)CONCAT13(7,param_2._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_2 + 3,1,1,DAT_005834d4);
    uVar7 = 0xffffffff;
    pcVar10 = &DAT_00571bbc;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar4 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar4 != '\0');
    sub_562B75(&DAT_00571bbc,1,~uVar7,DAT_005834d4);
    if (pcVar11 != (char *)0x0) {
      sub_562B75(pcVar11,~uVar6,1,DAT_005834d4);
    }
  }
  param_2 = (char *)CONCAT13(10,param_2._0_3_);
  iVar5 = (int)param_4;
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_2 + 3,1,1,DAT_005834d4);
    uVar6 = 0xffffffff;
    pcVar11 = s_HW_Device_Desc_00571c24;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar4 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar4 != '\0');
    sub_562B75(s_HW_Device_Desc_00571c24,1,~uVar6,DAT_005834d4);
    iVar5 = (int)param_4;
    if (param_4 != (void *)0x0) {
      sub_562B75(param_4,0xfc,1,DAT_005834d4);
    }
  }
  param_4 = (void *)CONCAT13(10,param_4._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_4 + 3,1,1,DAT_005834d4);
    uVar6 = 0xffffffff;
    pcVar11 = s_HEL_Device_Desc_00571c14;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar4 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar4 != '\0');
    sub_562B75(s_HEL_Device_Desc_00571c14,1,~uVar6,DAT_005834d4);
    if (iVar5 != 0) {
      sub_562B75(iVar5,0xfc,1,DAT_005834d4);
    }
  }
  local_8 = 0;
  param_4 = operator_new(0xd8);
  local_8._0_1_ = 1;
  if (param_4 == (void *)0x0) {
    local_24 = (int *)0x0;
  }
  else {
    local_24 = (int *)sub_413260(param_3,param_1);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  if (local_24 == (int *)0x0) {
    local_1c = s_Couldn_t_create_Direct3D_enumera_00571ae8;
    local_20 = &PTR_sub_413B20_0056e1c4;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_20,&DAT_0056f000);
  }
  cVar4 = sub_412A10(local_24 + 4,iVar5);
  piVar9 = local_24;
  if (cVar4 != '\0') {
    *(undefined1 *)(local_24 + 4) = 0;
    *(undefined1 *)((int)local_24 + 0x11) = 0;
    puVar8 = param_6;
    local_28 = iVar5;
    if (*(char *)((int)local_24 + 0x15) != '\0') {
      param_3 = (char *)CONCAT13(4,param_3._0_3_);
      if (DAT_005834d4 != 0) {
        sub_562B75((int)&param_3 + 3,1,1,DAT_005834d4);
        uVar6 = 0xffffffff;
        pcVar11 = s_Z_Buffer_Formats_00571c00;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar4 = *pcVar11;
          pcVar11 = pcVar11 + 1;
        } while (cVar4 != '\0');
        sub_562B75(s_Z_Buffer_Formats_00571c00,1,~uVar6,DAT_005834d4);
      }
      puVar8 = param_6;
      iVar5 = (**(code **)(*(int *)param_6[1] + 0x28))
                        ((int *)param_6[1],param_1,&LAB_00412640,&local_2c);
      param_3 = (char *)CONCAT13(5,param_3._0_3_);
      if (DAT_005834d4 != 0) {
        sub_562B75((int)&param_3 + 3,1,1,DAT_005834d4);
      }
      if (iVar5 != 0) {
        sub_413D80(s_Couldn_t_enumerate_depth_buffer_f_00571bd8);
        local_38[0] = &PTR_sub_414460_0056e1d0;
        local_30 = iVar5;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(local_38,&DAT_0056f168);
      }
    }
    param_3 = (char *)CONCAT13(4,param_3._0_3_);
    if (DAT_005834d4 != 0) {
      sub_562B75((int)&param_3 + 3,1,1,DAT_005834d4);
      uVar6 = 0xffffffff;
      pcVar11 = s_Display_Modes_00571ad8;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar4 = *pcVar11;
        pcVar11 = pcVar11 + 1;
      } while (cVar4 != '\0');
      sub_562B75(s_Display_Modes_00571ad8,1,~uVar6,DAT_005834d4);
    }
    iVar5 = (**(code **)(*(int *)*puVar8 + 0x20))((int *)*puVar8,0,0,&local_2c,sub_412320);
    param_3 = (char *)CONCAT13(5,param_3._0_3_);
    if (DAT_005834d4 != 0) {
      sub_562B75((int)&param_3 + 3,1,1,DAT_005834d4);
    }
    if (iVar5 != 0) {
      sub_413D80(s_Couldn_t_enumerate_display_modes_00571ab4);
      local_44[0] = &DAT_0056e1c0;
      local_3c = iVar5;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(local_44,&DAT_0056eff0);
    }
    sub_413A60(&LAB_004136a0);
    for (piVar9 = (int *)local_24[0xb]; (*piVar9 != 0 || (piVar9[1] == 0)); piVar9 = (int *)*piVar9)
    {
      sub_413A60(&LAB_00413790);
    }
    piVar9 = local_24;
    if (((int *)local_24[0xb] != local_24 + 0xc) &&
       ((*(char *)((int)local_24 + 0x15) == '\0' || (local_24[0xe] != 0)))) {
      piVar9 = *(int **)(puVar8[3] + 0x24);
      if (local_24 != piVar9) {
        piVar2 = (int *)local_24[1];
        piVar1 = local_24 + 1;
        if ((piVar2 != piVar9) && (*piVar9 != 0)) {
          if ((*local_24 != 0) && (piVar2 != (int *)0x0)) {
            *(int **)(*local_24 + 4) = piVar2;
            *(int *)*piVar1 = *local_24;
            *local_24 = 0;
            *piVar1 = 0;
          }
          iVar5 = *piVar9;
          *piVar1 = (int)piVar9;
          *local_24 = iVar5;
          *(int **)(iVar5 + 4) = local_24;
          *(int **)*piVar1 = local_24;
        }
      }
      goto LAB_0041227c;
    }
  }
  local_24 = piVar9;
  if (piVar9 != (int *)0x0) {
    sub_413390();
    sub_562941(piVar9);
  }
LAB_0041227c:
  param_3 = (char *)CONCAT13(3,param_3._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_3 + 3,1,1,DAT_005834d4);
  }
  ExceptionList = local_10;
  return 1;
}

