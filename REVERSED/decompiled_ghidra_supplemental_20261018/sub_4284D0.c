/* Selected Ghidra export at 004284d0. */

void sub_4284D0(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  
  piVar11 = DAT_006d94b8;
  if (DAT_006d94d0 == 0) {
    iVar5 = sub_414FB0();
    if ((iVar5 != 0) && (DAT_006d94d4 = DAT_006d94d4 + -1, DAT_006d94d4 == 0)) {
      uVar6 = sub_563C89();
      iVar5 = sub_563C89();
      DAT_006d94d0 = iVar5 - (uVar6 & 0x7f) & 0x20;
      if (DAT_006d94d0 == 0) {
        uVar6 = sub_563C89();
        DAT_006d94d4 = (uVar6 & 0x3f) + 1;
      }
      else {
        DAT_006d94d4 = 8;
      }
    }
  }
  else {
    DAT_006d94d4 = DAT_006d94d4 + -1;
    if (DAT_006d94d4 == 0) {
      DAT_006d94d0 = 0;
      uVar6 = sub_563C89();
      DAT_006d94d4 = (uVar6 & 0xff) + 0x20;
    }
  }
  uVar6 = 0;
  if (DAT_006da320 != 0) {
    do {
      if ((char)piVar11[4] == '\0') {
        *(undefined1 *)(piVar11 + 4) = 1;
        iVar5 = sub_414FB0();
        if ((iVar5 == 0) || (DAT_006da320 >> 2 <= DAT_005ff03c)) {
          uVar7 = sub_563C89();
          uVar8 = sub_563C89();
          piVar11[1] = ((uVar7 & 0xfff) - (uVar8 & 0xfff)) + DAT_006d9d84;
        }
        else {
          piVar11[1] = DAT_006d9d84 + 0x1800;
        }
        uVar7 = sub_563C89();
        uVar8 = sub_563C89();
        *piVar11 = DAT_006d9d80 + ((uVar7 & 0xfff) - (uVar8 & 0xfff)) * 4;
        uVar7 = sub_563C89();
        uVar8 = sub_563C89();
        piVar11[2] = DAT_006d9d88 + ((uVar7 & 0xfff) - (uVar8 & 0xfff)) * 4;
        uVar4 = sub_563C89();
        *(ushort *)(piVar11 + 5) = uVar4 & 0x1f;
        uVar4 = sub_563C89();
        *(ushort *)((int)piVar11 + 0x16) = uVar4 & 0x1f;
        uVar4 = sub_563C89();
        *(ushort *)((int)piVar11 + 0x12) = -(uVar4 & 0x7f);
        sub_4281E0(piVar11,DAT_005846ec,DAT_00584648);
      }
      else {
        sVar1 = *(short *)((int)piVar11 + 0x12);
        if (sVar1 < 0) {
          iVar3 = piVar11[5];
          iVar5 = *piVar11;
          if (sVar1 < -0x30) {
            iVar9 = -0x180;
          }
          else {
            iVar9 = (int)sVar1 << 3;
          }
          iVar2 = piVar11[1];
          iVar10 = (int)*(short *)((int)piVar11 + 0x16) + piVar11[2];
          *piVar11 = *piVar11 + (int)(short)piVar11[5];
          piVar11[2] = iVar10;
          piVar11[1] = *(short *)((int)piVar11 + 0x12) + iVar2;
          *(undefined2 *)(piVar11 + 5) = DAT_00578ef0;
          *(undefined2 *)((int)piVar11 + 0x16) = (undefined2)DAT_00578ef4;
          *(undefined2 *)((int)piVar11 + 0x12) = 0xff00;
          if (iVar2 + iVar9 < piVar11[6]) {
            if (piVar11[7] == 0x1e) goto LAB_004285d8;
            *(short *)(piVar11 + 5) = (short)piVar11[5] >> 2;
            *(short *)((int)piVar11 + 0x16) = *(short *)((int)piVar11 + 0x16) >> 2;
            *(short *)((int)piVar11 + 0x12) = -(*(short *)((int)piVar11 + 0x12) >> 2);
            *piVar11 = (short)iVar3 + iVar5;
            piVar11[2] = iVar10;
            piVar11[1] = piVar11[6] + 0x10;
          }
        }
        else {
LAB_004285d8:
          *(undefined1 *)(piVar11 + 4) = 0;
        }
      }
      uVar6 = uVar6 + 1;
      piVar11 = piVar11 + 8;
    } while (uVar6 < DAT_006da320);
  }
  DAT_005ff03c = 0;
  return;
}

