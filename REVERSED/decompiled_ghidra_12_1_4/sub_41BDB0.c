/* sub_41BDB0 @ 0041bdb0   296 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall sub_41BDB0(int param_1,float *param_2,int *param_3,int param_4)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  float local_8;
  
  iVar6 = 0;
  piVar8 = *(int **)(param_1 + 0x20);
  iVar7 = param_4;
  while ((piVar8 != (int *)0x0 && (iVar7 != 0))) {
    iVar1 = *piVar8;
    if ((*(int *)(iVar1 + 0x68) == 1) || (*(char *)(iVar1 + 0x6c) != '\0')) {
      *param_3 = iVar1;
      piVar9 = param_3 + 2;
      param_3[1] = (int)piVar9;
      iVar7 = iVar7 + -1;
    }
    else {
      iVar6 = iVar6 + 1;
      piVar9 = param_3;
    }
    piVar8 = (int *)piVar8[1];
    param_3 = piVar9;
  }
  if ((iVar7 <= iVar6) || (iVar7 != 0)) {
    local_8 = 0.0;
    for (; iVar7 != 0; iVar7 = iVar7 + -1) {
      piVar8 = *(int **)(param_1 + 0x20);
      iVar6 = 0;
      fVar5 = _DAT_0056e2f8;
      if (piVar8 == (int *)0x0) break;
      do {
        iVar1 = *piVar8;
        if (((*(int *)(iVar1 + 0x68) == 2) &&
            (fVar2 = *(float *)(iVar1 + 0x28) - param_2[2],
            fVar4 = *(float *)(iVar1 + 0x24) - param_2[1],
            fVar3 = *(float *)(iVar1 + 0x20) - *param_2,
            fVar2 = fVar2 * fVar2 + fVar4 * fVar4 + fVar3 * fVar3, fVar2 < fVar5)) &&
           (local_8 < fVar2)) {
          iVar6 = iVar1;
          fVar5 = fVar2;
        }
        piVar8 = (int *)piVar8[1];
      } while (piVar8 != (int *)0x0);
      if (iVar6 == 0) break;
      *param_3 = iVar6;
      param_3[1] = (int)(param_3 + 2);
      local_8 = fVar5;
      param_3 = param_3 + 2;
    }
  }
  if (param_4 <= iVar7) {
    *param_3 = 0;
    param_3[1] = 0;
    return 0;
  }
  param_3[-1] = 0;
  return 1;
}

