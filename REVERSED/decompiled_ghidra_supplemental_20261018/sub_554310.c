/* Selected Ghidra export at 00554310. */

void sub_554310(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  
  iVar3 = sub_54BC00(param_1);
  piVar4 = (int *)sub_54BC00(param_1);
  piVar4[6] = iVar3;
  sub_42C4A0(((int)piVar4 - DAT_00586598) / 0x1c);
  iVar1 = *piVar4;
  iVar9 = (piVar4[5] + 0x800 >> 0xc) + 1;
  iVar5 = -iVar9;
  if (-iVar9 == iVar9 || iVar5 < iVar9) {
    uVar8 = iVar5 + (piVar4[2] >> 0xc);
    do {
      if (*(uint *)(DAT_00584648 + 0x18) <= uVar8) {
        return;
      }
      iVar11 = -iVar9;
      if (-iVar9 == iVar9 || iVar11 < iVar9) {
        uVar10 = (iVar1 >> 0xc) + iVar11;
        iVar7 = DAT_00584648;
        do {
          if (*(uint *)(iVar7 + 0x14) <= uVar10) break;
          if ((-1 < (int)uVar10) && (-1 < (int)uVar8)) {
            piVar4 = *(int **)(*(int *)(iVar7 + 0x40) +
                              (uVar8 * *(uint *)(iVar7 + 0x14) + uVar10) * 4);
            for (; piVar4 != (int *)0x0; piVar4 = (int *)piVar4[1]) {
              iVar2 = *piVar4;
              iVar7 = *(int *)(*(int *)(iVar7 + 0x54) + iVar2 * 4);
              if (iVar7 != 0) {
                bVar6 = *(byte *)(iVar7 + 7) & 0x3f;
                *(byte *)(iVar7 + 7) = bVar6;
                if (iVar3 == 0) {
                  *(byte *)(iVar7 + 7) = bVar6 | 0x40;
                }
                else if ((iVar3 != 0x1000) && (*(char *)(iVar7 + 3) == '\x03')) {
                  *(byte *)(iVar7 + 7) = bVar6 | 0x80;
                  sub_5541B0(iVar7,*(undefined2 *)
                                    (DAT_005846ec + 0x6c +
                                    *(int *)(*(int *)(DAT_00584648 + 0x4c) + iVar2 * 4) * 0x84),
                             iVar3);
                }
              }
              iVar7 = DAT_00584648;
            }
          }
          iVar11 = iVar11 + 1;
          uVar10 = uVar10 + 1;
        } while (iVar11 <= iVar9);
      }
      iVar5 = iVar5 + 1;
      uVar8 = uVar8 + 1;
    } while (iVar5 <= iVar9);
  }
  return;
}

