/* sub_54D560 @ 0054d560   179 bytes */

int * sub_54D560(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  uint local_c;
  
  piVar1 = (int *)(param_1 + 0x30);
  piVar2 = (int *)(param_1 + 0x38);
  uVar5 = 0;
  iVar4 = *(int *)(param_1 + 0x34) >> 0xc;
  local_c = 0xffffffff;
  param_1 = 10000000;
  if (*(uint *)(DAT_00584648 + 0x1c) != 0) {
    piVar7 = *(int **)(DAT_00584648 + 0x24);
    do {
      if ((*piVar7 == *piVar1 >> 0xc) && (piVar7[2] == *piVar2 >> 0xc)) {
        if ((piVar7[7] & 1U) == 0) {
          iVar6 = iVar4 + -1;
          if ((piVar7[7] & 2U) == 0) {
            iVar6 = iVar4;
          }
        }
        else {
          iVar6 = iVar4 + 1;
        }
        iVar3 = piVar7[1];
        if ((iVar6 <= iVar3) && (iVar3 < param_1)) {
          param_1 = iVar3;
          local_c = uVar5;
        }
      }
      uVar5 = uVar5 + 1;
      piVar7 = piVar7 + 0x17;
    } while (uVar5 < *(uint *)(DAT_00584648 + 0x1c));
    if (local_c != 0xffffffff) {
      return *(int **)(DAT_00584648 + 0x24) + local_c * 0x17;
    }
  }
  return (int *)0x0;
}

