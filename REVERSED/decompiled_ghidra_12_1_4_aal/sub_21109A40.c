/* sub_21109A40 @ 21109a40   320 bytes */

int * __fastcall sub_21109A40(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  int local_18;
  
  if (param_1[2] == 0) {
    iVar2 = *param_1;
    iVar3 = param_1[3];
    iVar1 = iVar2 + 0x20;
    piVar4 = operator_new(iVar1 * 0x30);
    if (piVar4 == (int *)0x0) {
      return (int *)0x0;
    }
    if (0 < iVar2) {
      piVar5 = piVar4;
      local_18 = iVar2;
      do {
        piVar7 = (int *)((iVar3 - (int)piVar4) + (int)piVar5);
        piVar8 = piVar5;
        for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
          *piVar8 = *piVar7;
          piVar7 = piVar7 + 1;
          piVar8 = piVar8 + 1;
        }
        if (*piVar5 != 0) {
          *piVar5 = (int)piVar4 + (*piVar5 - iVar3);
        }
        if (piVar5[1] != 0) {
          piVar5[1] = (int)piVar4 + (piVar5[1] - iVar3);
        }
        piVar5 = piVar5 + 0xc;
        local_18 = local_18 + -1;
      } while (local_18 != 0);
    }
    if (iVar2 < iVar1) {
      piVar5 = piVar4 + iVar2 * 0xc + -0xc;
      iVar6 = iVar1 - iVar2;
      do {
        piVar5[0xe] = -1;
        piVar5[0xd] = (int)piVar5;
        piVar5[0xc] = (int)(piVar5 + 0x18);
        piVar5 = piVar5 + 0xc;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    piVar4[iVar2 * 0xc + 1] = 0;
    piVar4[iVar1 * 0xc + -0xc] = 0;
    param_1[1] = (int)piVar4 + (param_1[1] - iVar3);
    param_1[2] = (int)(piVar4 + iVar2 * 0xc);
    *param_1 = iVar1;
    sub_2110D4F4((LPVOID)param_1[3]);
    param_1[3] = (int)piVar4;
  }
  piVar4 = (int *)param_1[2];
  param_1[2] = *piVar4;
  *piVar4 = param_1[1];
  piVar4[1] = 0;
  if (param_1[1] != 0) {
    *(int **)(param_1[1] + 4) = piVar4;
  }
  param_1[1] = (int)piVar4;
  piVar4[2] = (uint)((int)piVar4 - param_1[3]) / 0x30;
  return piVar4;
}

