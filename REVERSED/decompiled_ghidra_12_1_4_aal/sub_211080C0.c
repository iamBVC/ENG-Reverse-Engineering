/* sub_211080C0 @ 211080c0   216 bytes */

uint sub_211080C0(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 local_c [4];
  int local_8;
  uint local_4;
  
  if (param_1 == (int *)0x0) {
    return 0;
  }
  local_8 = param_1[1];
  uVar4 = param_1[4];
  iVar3 = 0;
  if (0 < *param_1) {
    do {
      piVar1 = *(int **)(uVar4 + 4);
      local_4 = uVar4;
      if (iVar3 == 0) {
LAB_2110812d:
        if (piVar1 != (int *)0x0) {
LAB_21108131:
          _AAL_Lock_0();
          iVar2 = (**(code **)(*piVar1 + 0x24))(piVar1,local_c);
          _AAL_Unlock_0();
          if ((-1 < iVar2) && ((local_c[0] & 1) != 1)) break;
        }
      }
      else {
        if (piVar1 != (int *)0x0) goto LAB_21108131;
        if (*(int *)(param_1[4] + 4) == 0) goto LAB_2110812d;
        _AAL_Lock_0();
        iVar2 = (**(code **)(*(int *)param_1[3] + 0x14))
                          ((int *)param_1[3],*(undefined4 *)(param_1[4] + 4),uVar4 + 4);
        _AAL_Unlock_0();
        if (iVar2 == 0) break;
      }
      iVar3 = iVar3 + 1;
      uVar4 = uVar4 + local_8;
    } while (iVar3 < *param_1);
  }
  if (iVar3 == *param_1) {
    AAL_SetError(s_Could_not_get_free_sound_object_211145ac);
  }
  return (iVar3 == *param_1) - 1 & local_4;
}

