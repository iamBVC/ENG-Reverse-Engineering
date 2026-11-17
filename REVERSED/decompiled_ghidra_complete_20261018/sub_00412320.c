/* sub_412320 @ 00412320   708 bytes */

undefined4 sub_412320(void *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  char *pcVar8;
  char local_138 [276];
  undefined **local_24;
  char *local_20;
  undefined **local_1c;
  char *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  iVar2 = (int)param_1;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0056d79e;
  local_10 = ExceptionList;
  local_14 = &stack0xfffffebc;
  ExceptionList = &local_10;
  sub_562717(local_138,s__dx_dx_d_00571cb0,*(undefined4 *)((int)param_1 + 0xc),
             *(undefined4 *)((int)param_1 + 8),*(undefined4 *)((int)param_1 + 0x54));
  param_1 = (void *)CONCAT13(0xc,param_1._0_3_);
  if (DAT_005834d4 != 0) {
    sub_562B75((int)&param_1 + 3,1,1,DAT_005834d4);
    if (&stack0x00000000 != (undefined1 *)0x138) {
      uVar7 = 0xffffffff;
      pcVar8 = local_138;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar3 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar3 != '\0');
      sub_562B75(local_138,1,~uVar7,DAT_005834d4);
    }
    if (iVar2 != 0) {
      sub_562B75(iVar2,0x7c,1,DAT_005834d4);
    }
  }
  piVar6 = param_2;
  local_8._0_1_ = 0;
  local_8._1_3_ = 0;
  cVar3 = sub_412C00(*(int *)(*param_2 + 0xc) + 0x14,param_2[1],iVar2);
  if (cVar3 != '\0') {
    piVar5 = *(int **)(piVar6[2] + 0x2c);
    do {
      piVar4 = piVar5;
      if (((int *)*piVar4 == (int *)0x0) && (piVar4[1] != 0)) break;
      piVar5 = (int *)*piVar4;
    } while (*(int *)(iVar2 + 0x54) != piVar4[3]);
    if ((*piVar4 == 0) && (piVar4[1] != 0)) {
      sub_562717(local_138,s__d_bit_00571ca8,*(undefined4 *)(iVar2 + 0x54));
      param_1 = operator_new(0x3c);
      local_8._0_1_ = 1;
      if (param_1 == (void *)0x0) {
        piVar4 = (int *)0x0;
      }
      else {
        piVar4 = (int *)sub_413570(local_138,*(undefined4 *)(iVar2 + 0x54),piVar6[2] + 0x38);
      }
      local_8._0_1_ = 0;
      if (piVar4 == (int *)0x0) {
        local_20 = s_Couldn_t_create_display_format_e_00571c74;
        local_24 = &PTR_sub_413B20_0056e1c4;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(&local_24,&DAT_0056f000);
      }
      piVar6 = *(int **)(piVar6[2] + 0x34);
      if (((piVar4 != piVar6) && (piVar5 = (int *)piVar4[1], piVar5 != piVar6)) && (*piVar6 != 0)) {
        if ((*piVar4 != 0) && (piVar5 != (int *)0x0)) {
          *(int **)(*piVar4 + 4) = piVar5;
          *(int *)piVar4[1] = *piVar4;
          *piVar4 = 0;
          piVar4[1] = 0;
        }
        iVar1 = *piVar6;
        piVar4[1] = (int)piVar6;
        *piVar4 = iVar1;
        *(int **)(iVar1 + 4) = piVar4;
        *(int **)piVar4[1] = piVar4;
      }
    }
    piVar6 = (int *)piVar4[0xc];
    do {
      piVar5 = piVar6;
      piVar6 = (int *)*piVar5;
      if ((piVar6 == (int *)0x0) && (piVar5[1] != 0)) break;
    } while ((*(int *)(iVar2 + 0xc) != piVar5[3]) || (*(int *)(iVar2 + 8) != piVar5[4]));
    if ((*piVar5 == 0) && (piVar5[1] != 0)) {
      sub_562717(local_138,s__dx_d_00571c6c,*(undefined4 *)(iVar2 + 0xc),*(undefined4 *)(iVar2 + 8))
      ;
      param_1 = operator_new(0x90);
      local_8._0_1_ = 2;
      if (param_1 == (void *)0x0) {
        piVar6 = (int *)0x0;
      }
      else {
        piVar6 = (int *)sub_413700(local_138,iVar2);
      }
      local_8 = (uint)local_8._1_3_ << 8;
      if (piVar6 == (int *)0x0) {
        local_18 = s_Couldn_t_create_display_resoluti_00571c34;
        local_1c = &PTR_sub_413B20_0056e1c4;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(&local_1c,&DAT_0056f000);
      }
      piVar5 = (int *)piVar4[0xe];
      if (((piVar6 != piVar5) && (piVar4 = (int *)piVar6[1], piVar4 != piVar5)) && (*piVar5 != 0)) {
        if ((*piVar6 != 0) && (piVar4 != (int *)0x0)) {
          *(int **)(*piVar6 + 4) = piVar4;
          *(int *)piVar6[1] = *piVar6;
          *piVar6 = 0;
          piVar6[1] = 0;
        }
        iVar2 = *piVar5;
        piVar6[1] = (int)piVar5;
        *piVar6 = iVar2;
        *(int **)(iVar2 + 4) = piVar6;
        *(int **)piVar6[1] = piVar6;
      }
    }
  }
  ExceptionList = local_10;
  return 1;
}

