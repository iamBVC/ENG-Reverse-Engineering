/* sub_401430 @ 00401430   435 bytes */

bool sub_401430(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,int *param_6,int param_7,undefined4 param_8)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int local_8;
  
  iVar2 = sub_4010F0(param_1,param_2 + *param_6 * 0xc);
  local_8 = 1;
  iVar5 = iVar2;
  iVar3 = iVar2;
  piVar1 = param_6;
  if (1 < param_6[10]) {
    do {
      piVar6 = piVar1 + 1;
      iVar3 = sub_4010F0(param_1,param_2 + *piVar6 * 0xc);
      if (iVar5 == 1) {
        *(int *)(param_7 + *(int *)(param_7 + 0x28) * 4) = *piVar1;
        iVar5 = *(int *)(param_7 + 0x28) + 1;
        *(int *)(param_7 + 0x28) = iVar5;
        if (iVar3 == 0) {
          *(int *)(param_7 + iVar5 * 4) = *piVar6;
          *(int *)(param_7 + 0x28) = *(int *)(param_7 + 0x28) + 1;
        }
        else if (iVar3 == -1) {
LAB_004014ea:
          uVar4 = sub_401210(param_1,param_2,param_3,param_4,param_5,*piVar1,*piVar6,param_8);
          *(undefined4 *)(param_7 + *(int *)(param_7 + 0x28) * 4) = uVar4;
          *(int *)(param_7 + 0x28) = *(int *)(param_7 + 0x28) + 1;
        }
      }
      else if (iVar5 == 0) {
        if (iVar3 == 1) {
          *(int *)(param_7 + *(int *)(param_7 + 0x28) * 4) = *piVar1;
          *(int *)(param_7 + 0x28) = *(int *)(param_7 + 0x28) + 1;
        }
      }
      else if ((iVar5 == -1) && (iVar3 == 1)) goto LAB_004014ea;
      local_8 = local_8 + 1;
      iVar5 = iVar3;
      piVar1 = piVar6;
    } while (local_8 < param_6[10]);
  }
  if (iVar3 == 1) {
    *(int *)(param_7 + *(int *)(param_7 + 0x28) * 4) = param_6[param_6[10] + -1];
    iVar5 = *(int *)(param_7 + 0x28) + 1;
    *(int *)(param_7 + 0x28) = iVar5;
    if (iVar2 == 0) {
      *(int *)(param_7 + iVar5 * 4) = *param_6;
    }
    else {
      if (iVar2 != -1) goto LAB_004015d0;
LAB_00401599:
      uVar4 = sub_401210(param_1,param_2,param_3,param_4,param_5,param_6[param_6[10] + -1],*param_6,
                         param_8);
      *(undefined4 *)(param_7 + *(int *)(param_7 + 0x28) * 4) = uVar4;
    }
  }
  else {
    if (iVar3 != 0) {
      if ((iVar3 != -1) || (iVar2 != 1)) goto LAB_004015d0;
      goto LAB_00401599;
    }
    if (iVar2 != 1) goto LAB_004015d0;
    *(int *)(param_7 + *(int *)(param_7 + 0x28) * 4) = param_6[param_6[10] + -1];
  }
  *(int *)(param_7 + 0x28) = *(int *)(param_7 + 0x28) + 1;
LAB_004015d0:
  return 2 < *(int *)(param_7 + 0x28);
}

