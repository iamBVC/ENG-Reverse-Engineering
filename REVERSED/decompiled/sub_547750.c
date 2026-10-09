/* sub_547750 @ 00547750   174 bytes */

bool sub_547750(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int unaff_ESI;
  int local_4;
  
  *(short *)(param_2 + 0x1a) = (short)param_3;
  local_4 = 0;
  *(undefined2 *)(param_2 + 0x18) = 0;
  *(undefined4 *)(param_2 + 8) = 0;
  iVar1 = sub_547710(param_1,&local_4,param_3);
  iVar3 = 0;
  if (local_4 != 0) {
    if (iVar1 == 0) {
      *(undefined2 *)(local_4 + 0xe) = 0;
    }
    else {
      *(undefined2 *)(local_4 + 0xe) = 1;
      *(undefined4 *)(*(int *)(local_4 + 8) + 8) = 0;
    }
    if (*(int *)(param_2 + 0x14) == 1) {
      uVar2 = _AAL_AllocateVoiceForHandle_8(DAT_005834f4,param_4);
      *(undefined4 *)(unaff_ESI + 0x14) = uVar2;
    }
    else {
      uVar2 = _AAL_AllocateVoice_4(0);
      *(undefined4 *)(unaff_ESI + 0x14) = uVar2;
    }
    *(int *)(unaff_ESI + 8) = param_2;
    *(int *)(param_2 + 8) = unaff_ESI;
    iVar3 = unaff_ESI;
    if (*(int *)(unaff_ESI + 0x14) == 0) {
      sub_547800(param_1,param_2);
      iVar3 = 0;
    }
  }
  return iVar3 != 0;
}

