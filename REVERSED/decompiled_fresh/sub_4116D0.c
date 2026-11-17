/* sub_4116D0 @ 004116d0   1540 bytes */

undefined4
sub_4116D0(undefined4 *param_1,char *param_2,char *param_3,undefined4 param_4,undefined4 param_5)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  undefined1 *puVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  undefined4 *puVar10;
  char *pcVar11;
  undefined4 local_38c [95];
  undefined4 local_210 [100];
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined **local_70 [2];
  int local_68;
  undefined *local_64 [2];
  int local_5c;
  undefined *local_58;
  char *local_54;
  int local_50;
  undefined *local_4c;
  char *local_48;
  int local_44;
  undefined *local_40 [2];
  int local_38;
  undefined **local_34;
  char *local_30;
  int *local_2c;
  int *local_28;
  undefined4 *local_24;
  int *local_20;
  int *local_1c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0056d756;
  local_10 = ExceptionList;
  local_7c = 0;
  local_14 = &stack0xfffffc68;
  local_78 = 0;
  local_24 = local_210;
  local_1c = (int *)0x0;
  local_80 = 0;
  local_74 = 0;
  local_2c = (int *)0x0;
  local_28 = (int *)0x0;
  local_20 = (int *)0x0;
  local_15 = 2;
  pcVar9 = param_3;
  ExceptionList = &local_10;
  puVar4 = &stack0xfffffc68;
  if ((DAT_005834d4 != 0) &&
     (ExceptionList = &local_10, sub_562B75(&local_15,1,1,DAT_005834d4), pcVar9 = param_3,
     puVar4 = local_14, param_3 != (char *)0x0)) {
    uVar7 = 0xffffffff;
    pcVar11 = param_3;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar5 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar5 != '\0');
    sub_562B75(param_3,1,~uVar7,DAT_005834d4);
    puVar4 = local_14;
  }
  local_14 = puVar4;
  puVar10 = param_1;
  if (param_1 == (undefined4 *)0x0) {
    puVar10 = &local_80;
  }
  param_3 = (char *)CONCAT13(6,param_3._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_3 + 3,1,1,DAT_005834d4);
    uVar7 = 0xffffffff;
    pcVar11 = &DAT_00571bd0;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar5 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar5 != '\0');
    sub_562B75(&DAT_00571bd0,1,~uVar7,DAT_005834d4);
    if (puVar10 != (undefined4 *)0x0) {
      sub_562B75(puVar10,0x10,1,DAT_005834d4);
    }
  }
  uVar7 = 0xffffffff;
  param_3 = (char *)CONCAT13(7,param_3._0_3_);
  pcVar11 = param_2;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar5 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar5 != '\0');
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_3 + 3,1,1,DAT_005834d4);
    uVar8 = 0xffffffff;
    pcVar11 = s_Description_00571bc4;
    do {
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      cVar5 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar5 != '\0');
    sub_562B75(s_Description_00571bc4,1,~uVar8,DAT_005834d4);
    if (param_2 != (char *)0x0) {
      sub_562B75(param_2,~uVar7,1,DAT_005834d4);
    }
  }
  uVar7 = 0xffffffff;
  param_3 = (char *)CONCAT13(7,param_3._0_3_);
  pcVar11 = pcVar9;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar5 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar5 != '\0');
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_3 + 3,1,1,DAT_005834d4);
    uVar8 = 0xffffffff;
    pcVar11 = &DAT_00571bbc;
    do {
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      cVar5 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar5 != '\0');
    sub_562B75(&DAT_00571bbc,1,~uVar8,DAT_005834d4);
    if (pcVar9 != (char *)0x0) {
      sub_562B75(pcVar9,~uVar7,1,DAT_005834d4);
    }
  }
  param_3 = (char *)CONCAT13(8,param_3._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_3 + 3,1,1,DAT_005834d4);
    uVar7 = 0xffffffff;
    pcVar9 = s_Monitor_00571bb4;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar5 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar5 != '\0');
    sub_562B75(s_Monitor_00571bb4,1,~uVar7,DAT_005834d4);
    if (&stack0x00000000 != (undefined1 *)0xffffffec) {
      sub_562B75(&param_5,4,1,DAT_005834d4);
    }
  }
  local_8 = 0;
  param_3 = operator_new(0x28);
  local_8._0_1_ = 1;
  if (param_3 == (void *)0x0) {
    local_20 = (int *)0x0;
  }
  else {
    local_20 = (int *)sub_4130B0(param_2,param_1,param_5);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  if (local_20 == (int *)0x0) {
    local_30 = s_Couldn_t_create_DirectDraw_enume_00571b84;
    local_34 = &PTR_sub_413B20_0056e1c4;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_34,&DAT_0056f000);
  }
  local_44 = DirectDrawCreate(param_1,&local_1c,0);
  if (local_44 != 0) {
    local_48 = s_Couldn_t_create_DirectDraw_devic_005717dc;
    local_4c = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_4c,&DAT_0056eff0);
  }
  local_50 = (**(code **)*local_1c)(local_1c,&DAT_0056e71c,&local_2c);
  if (local_50 != 0) {
    local_54 = s_Couldn_t_get_DirectDraw4_interfa_005717b8;
    local_58 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_58,&DAT_0056eff0);
  }
  local_38 = (**(code **)*local_1c)(local_1c,&DAT_0056e6ec,&local_28);
  if (local_38 != 0) {
    sub_413D80(s_Couldn_t_get_Direct3D3_interface_00571794);
    local_40[0] = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_40,&DAT_0056eff0);
  }
  local_210[0] = 0x17c;
  local_38c[0] = 0x17c;
  local_5c = (**(code **)(*local_2c + 0x2c))(local_2c,local_210,local_38c);
  if (local_5c != 0) {
    sub_413D80(s_Couldn_t_get_DirectDraw_capabili_00571b5c);
    local_64[0] = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_64,&DAT_0056eff0);
  }
  param_1 = (undefined4 *)CONCAT13(9,param_1._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_1 + 3,1,1,DAT_005834d4);
    uVar7 = 0xffffffff;
    pcVar9 = s_Driver_Caps_00571b50;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar5 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar5 != '\0');
    sub_562B75(s_Driver_Caps_00571b50,1,~uVar7,DAT_005834d4);
    if (&stack0x00000000 != (undefined1 *)0x210) {
      sub_562B75(local_210,0x17c,1,DAT_005834d4);
    }
  }
  param_1 = (undefined4 *)CONCAT13(9,param_1._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_1 + 3,1,1,DAT_005834d4);
    uVar7 = 0xffffffff;
    pcVar9 = s_HEL_Caps_00571b44;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar5 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar5 != '\0');
    sub_562B75(s_HEL_Caps_00571b44,1,~uVar7,DAT_005834d4);
    if (&stack0x00000000 != (undefined1 *)0x38c) {
      sub_562B75(local_38c,0x17c,1,DAT_005834d4);
    }
  }
  cVar5 = sub_412940(local_20 + 5,local_210);
  piVar1 = local_20;
  if (cVar5 != '\0') {
    param_1 = (undefined4 *)CONCAT13(4,param_1._0_3_);
    if (DAT_005834d4 != 0) {
      sub_562B75((int)&param_1 + 3,1,1,DAT_005834d4);
      uVar7 = 0xffffffff;
      pcVar9 = s_D3D_Devices_00571b38;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar5 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar5 != '\0');
      sub_562B75(s_D3D_Devices_00571b38,1,~uVar7,DAT_005834d4);
    }
    iVar6 = (**(code **)(*local_28 + 0xc))(local_28,sub_411D60,&local_2c);
    param_1 = (undefined4 *)CONCAT13(5,param_1._0_3_);
    if (DAT_005834d4 != 0) {
      sub_562B75((int)&param_1 + 3,1,1,DAT_005834d4);
    }
    if (iVar6 != 0) {
      sub_413D80(s_Couldn_t_enumerate_Direct3D_devi_00571b14);
      local_70[0] = &PTR_sub_414460_0056e1d0;
      local_68 = iVar6;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(local_70,&DAT_0056f168);
    }
    sub_413A60(&LAB_00413480);
    piVar3 = DAT_00583418;
    piVar1 = local_20;
    if ((int *)local_20[7] != local_20 + 8) {
      if (local_20 != DAT_00583418) {
        piVar2 = (int *)local_20[1];
        piVar1 = local_20 + 1;
        if ((piVar2 != DAT_00583418) && (*DAT_00583418 != 0)) {
          if ((*local_20 != 0) && (piVar2 != (int *)0x0)) {
            *(int **)(*local_20 + 4) = piVar2;
            *(int *)*piVar1 = *local_20;
            *local_20 = 0;
            *piVar1 = 0;
          }
          iVar6 = *piVar3;
          *piVar1 = (int)piVar3;
          *local_20 = iVar6;
          *(int **)(iVar6 + 4) = local_20;
          *(int **)*piVar1 = local_20;
        }
      }
      goto LAB_00411c83;
    }
  }
  local_20 = piVar1;
  if (piVar1 != (int *)0x0) {
    sub_413170();
    sub_562941(piVar1);
  }
LAB_00411c83:
  (**(code **)(*local_28 + 8))(local_28);
  (**(code **)(*local_2c + 8))(local_2c);
  (**(code **)(*local_1c + 8))(local_1c);
  param_1 = (undefined4 *)CONCAT13(3,param_1._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_1 + 3,1,1,DAT_005834d4);
  }
  ExceptionList = local_10;
  return 1;
}

