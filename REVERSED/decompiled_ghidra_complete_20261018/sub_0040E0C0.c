/* sub_40E0C0 @ 0040e0c0   1067 bytes */

void sub_40E0C0(int param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  char in_stack_00000058;
  
  bVar2 = false;
  DAT_00571498 = 0;
  iVar8 = 0;
  piVar6 = &DAT_0058226c;
  do {
    if ((((*(byte *)(iVar8 + param_1) & 0x80) == 0) || ((*(byte *)(param_1 + 0x38) & 0x80) != 0)) ||
       ((*(byte *)(param_1 + 0xb8) & 0x80) != 0)) {
      *piVar6 = 0;
    }
    else {
      *piVar6 = *piVar6 + 1;
      bVar2 = true;
      DAT_00571498 = 1;
    }
    iVar1 = DAT_00582270;
    piVar6 = piVar6 + 1;
    iVar8 = iVar8 + 1;
  } while ((int)piVar6 < 0x58266c);
  if (DAT_00582cac != 0) {
    DAT_00582270 = 0;
  }
  DAT_00582cac = iVar1;
  piVar6 = DAT_00582260;
  if ((!bVar2) || (in_stack_00000058 == '\0')) {
    for (; (iVar5 = DAT_005825ac, iVar4 = DAT_005825a0, iVar3 = DAT_00582598, iVar1 = DAT_0058258c,
           iVar8 = DAT_005822dc, *piVar6 != 0 || (piVar6[1] == 0)); piVar6 = (int *)*piVar6) {
      if ((piVar6[0x1d] != 0) && ((piVar6[0x1d] & 0x80000000U) == 0)) {
        uVar7 = piVar6[0x17];
        if (((uVar7 & 0x80000000) == 0) && ((piVar6[0x18] & 0x80000000U) == 0)) {
          if ((uVar7 & 0x40000000) == 0) {
            piVar6[0x1e] = *(int *)((uVar7 & 0xfffffff) + 0xc + (int)piVar6);
          }
          else {
            piVar6[0x1e] = 0xff - *(int *)((uVar7 & 0xfffffff) + 0xc + (int)piVar6);
          }
          uVar7 = piVar6[0x18];
          if ((uVar7 & 0x40000000) == 0) {
            piVar6[0x1f] = *(int *)((uVar7 & 0xfffffff) + 0xc + (int)piVar6);
          }
          else {
            piVar6[0x1f] = 0xff - *(int *)((uVar7 & 0xfffffff) + 0xc + (int)piVar6);
          }
          uVar7 = piVar6[0x19];
          if (((uVar7 & 0x80000000) == 0) && ((piVar6[0x1a] & 0x80000000U) == 0)) {
            if ((uVar7 & 0x40000000) == 0) {
              iVar8 = *(int *)((uVar7 & 0xfffffff) + 0xc + (int)piVar6) + -0x80;
            }
            else {
              iVar8 = 0x80 - *(int *)((uVar7 & 0xfffffff) + 0xc + (int)piVar6);
            }
            piVar6[0x1e] = piVar6[0x1e] + iVar8;
            uVar7 = piVar6[0x1a];
            if ((uVar7 & 0x40000000) == 0) {
              iVar8 = *(int *)((uVar7 & 0xfffffff) + 0xc + (int)piVar6) + -0x80;
            }
            else {
              iVar8 = 0x80 - *(int *)((uVar7 & 0xfffffff) + 0xc + (int)piVar6);
            }
            piVar6[0x1f] = piVar6[0x1f] + iVar8;
            if (0xff < piVar6[0x1e]) {
              piVar6[0x1e] = 0xff;
            }
            if (0xff < piVar6[0x1f]) {
              piVar6[0x1f] = 0xff;
            }
            if (piVar6[0x1e] < 0) {
              piVar6[0x1e] = 0;
            }
            if (piVar6[0x1f] < 0) {
              piVar6[0x1f] = 0;
            }
          }
        }
        else {
          piVar6[0x1f] = 0x80;
          piVar6[0x1e] = 0x80;
        }
        iVar8 = piVar6[0x56];
        uVar7 = ((piVar6[0x1f] - piVar6[iVar8 + 0x53]) - piVar6[iVar8 + 0x50]) + piVar6[0x1e];
        uVar9 = (int)uVar7 >> 0x1f;
        if ((6 < (int)((uVar7 ^ uVar9) - uVar9)) &&
           (iVar8 = (iVar8 + -1) % 3,
           uVar7 = ((piVar6[0x1f] - piVar6[iVar8 + 0x53]) - piVar6[iVar8 + 0x50]) + piVar6[0x1e],
           uVar9 = (int)uVar7 >> 0x1f, 6 < (int)((uVar7 ^ uVar9) - uVar9))) {
          iVar8 = (piVar6[0x56] + 1) % 3;
          piVar6[0x56] = iVar8;
          piVar6[iVar8 + 0x50] = piVar6[0x1e];
          piVar6[piVar6[0x56] + 0x53] = piVar6[0x1f];
          uVar7 = ((piVar6[0x53] - piVar6[0x54]) - piVar6[0x51]) + piVar6[0x50];
          uVar9 = (int)uVar7 >> 0x1f;
          if ((int)((uVar7 ^ uVar9) - uVar9) < 0x61) {
LAB_0040e36e:
            uVar7 = piVar6[0x1d] | 0x40000000;
          }
          else {
            uVar7 = ((piVar6[0x53] - piVar6[0x52]) - piVar6[0x55]) + piVar6[0x50];
            uVar9 = (int)uVar7 >> 0x1f;
            if (((int)((uVar7 ^ uVar9) - uVar9) < 0x61) ||
               (uVar7 = ((piVar6[0x54] - piVar6[0x52]) - piVar6[0x55]) + piVar6[0x51],
               uVar9 = (int)uVar7 >> 0x1f, (int)((uVar7 ^ uVar9) - uVar9) < 0x61))
            goto LAB_0040e36e;
            uVar7 = piVar6[0x1d] & 0xbfffffff;
          }
          piVar6[0x1d] = uVar7;
        }
        iVar8 = 0;
        piVar10 = piVar6 + 0xf;
        do {
          iVar1 = piVar6[0x1b];
          if ((char)*piVar10 == '\0') {
            *(undefined4 *)(iVar1 + iVar8) = 0;
          }
          else {
            *(int *)(iVar1 + iVar8) = *(int *)(iVar1 + iVar8) + 1;
          }
          iVar8 = iVar8 + 4;
          piVar10 = (int *)((int)piVar10 + 1);
        } while (iVar8 < 0x80);
        if (DAT_005846e4 != 3) {
          if (*(int *)(piVar6[0x1b] + *(int *)(piVar6[0x1c] + 0x1c) * 4) != 0) {
            DAT_005822dc = DAT_005822dc + 1;
          }
          if (*(int *)(piVar6[0x1b] + *(int *)(piVar6[0x1c] + 0x18) * 4) != 0) {
            DAT_00582270 = DAT_00582270 + 1;
          }
          if (piVar6[0x1f] < 0x40) {
            DAT_0058258c = DAT_0058258c + 1;
          }
          if (0xbf < piVar6[0x1f]) {
            DAT_005825ac = DAT_005825ac + 1;
          }
          if (0xbf < piVar6[0x1e]) {
            DAT_005825a0 = DAT_005825a0 + 1;
          }
          if (piVar6[0x1e] < 0x40) {
            DAT_00582598 = DAT_00582598 + 1;
          }
        }
      }
    }
    if (in_stack_00000058 != '\0') {
      if (DAT_00582ca8 != 0) {
        DAT_005822dc = 0;
      }
      DAT_00582ca8 = iVar8;
      if (DAT_00582cb4 != 0) {
        DAT_005825ac = 0;
      }
      DAT_00582cb4 = iVar5;
      if (DAT_00582cb0 != 0) {
        DAT_0058258c = 0;
      }
      DAT_00582cb0 = iVar1;
      if (DAT_00582cb8 != 0) {
        DAT_00582598 = 0;
      }
      DAT_00582cb8 = iVar3;
      if (DAT_00582cbc != 0) {
        DAT_005825a0 = 0;
        DAT_00582cbc = iVar4;
        return;
      }
      DAT_00582cbc = DAT_005825a0;
    }
  }
  return;
}

