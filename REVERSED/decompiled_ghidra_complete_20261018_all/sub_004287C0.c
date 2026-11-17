/* sub_4287C0 @ 004287c0   1431 bytes */

/* WARNING: Removing unreachable block (ram,0x00428bbe) */
/* WARNING: Removing unreachable block (ram,0x00428bd8) */

void sub_4287C0(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  ushort uVar10;
  uint uVar11;
  uint uVar12;
  byte bVar13;
  char cVar14;
  byte bVar15;
  char cVar16;
  uint uVar17;
  uint uStack_38;
  uint uStack_34;
  uint uStack_30;
  uint uStack_2c;
  
  piVar8 = DAT_006d9bdc;
  (*DAT_005ff034)();
  do {
    while( true ) {
      if (piVar8 == (int *)0x0) {
        return;
      }
      if (*(short *)((int)piVar8 + 0x32) != 0) break;
      piVar5 = (int *)*piVar8;
      piVar6 = (int *)piVar8[1];
      if (piVar5 != (int *)0x0) {
        piVar5[1] = (int)piVar6;
      }
      piVar9 = piVar5;
      if (piVar6 != (int *)0x0) {
        *piVar6 = (int)piVar5;
        piVar9 = DAT_006d9bdc;
      }
      DAT_006d9bdc = piVar9;
      piVar8[1] = 0;
      *piVar8 = (int)DAT_006d9bd8;
      DAT_006d9bd8 = piVar8;
      piVar8 = piVar5;
    }
    uVar10 = *(ushort *)(&DAT_005fef30 + DAT_006d9bf0 * 2);
    uVar1 = (&DAT_005fef32)[DAT_006d9bf0];
    uVar2 = *(ushort *)(&DAT_005fef34 + DAT_006d9bf0 * 2);
    uVar3 = *(ushort *)(&DAT_005fef36 + DAT_006d9bf0 * 2);
    DAT_006d9bf0 = DAT_006d9bf0 + 4;
    if (0x1f < DAT_006d9bf0) {
      DAT_006d9bf0 = 0;
    }
    *(short *)((int)piVar8 + 0x32) = *(short *)((int)piVar8 + 0x32) + -1;
    uVar4 = *(ushort *)(piVar8 + 0xd);
    if (*(short *)((int)piVar8 + 0x32) != 0) {
      if ((uVar4 & 0x100) == 0) {
        piVar8[2] = piVar8[2] + piVar8[6];
        piVar8[3] = piVar8[3] + piVar8[7];
        piVar8[4] = piVar8[4] + piVar8[8];
        uVar11 = (uint)*(char *)((int)piVar8 + 0x2d);
        piVar8[7] = (int)*(char *)((int)piVar8 + 0x2e) + piVar8[7];
        if ((uVar4 & 0x800) == 0) {
          if ((((uVar4 & 0x400) != 0) && (piVar8[3] <= piVar8[9])) && (piVar8[7] < 0)) {
            uVar12 = -(piVar8[7] >> 1);
            goto LAB_004288ea;
          }
        }
        else if ((((uVar4 & 0x400) != 0) && (piVar8[3] <= piVar8[9])) && (piVar8[7] < 0)) {
          uVar12 = (byte)(&DAT_005fef30)[DAT_006d9bf0 * 2] & 0x1f;
LAB_004288ea:
          piVar8[7] = uVar12;
        }
        if (uVar11 != 0) {
          piVar8[6] = piVar8[6] + ((uVar11 & uVar10) - (uVar11 & uVar2));
        }
        uVar11 = (uint)*(char *)((int)piVar8 + 0x2f);
        if (uVar11 != 0) {
          piVar8[8] = piVar8[8] + ((uVar11 & uVar1) - (uVar11 & uVar3));
        }
        if (((uVar4 & 0x200) != 0) && (piVar8[9] < piVar8[3])) {
          *(undefined2 *)((int)piVar8 + 0x32) = 0x14;
          *(undefined1 *)((int)piVar8 + 0x2e) = 0;
          *(undefined1 *)((int)piVar8 + 0x2f) = 0;
          *(undefined1 *)((int)piVar8 + 0x2d) = 0;
          *(undefined1 *)(piVar8 + 0xb) = 0x11;
          uVar10 = sub_563C89();
          *(ushort *)(piVar8 + 0xc) = uVar10 & 0xfff;
          piVar8[8] = 0;
          piVar8[7] = 0;
          piVar8[6] = 0;
          piVar8[3] = piVar8[9];
          piVar8[0xe] = 0x808080;
          piVar8[0xf] = 0x40;
          piVar8[0x11] = 0x20;
          *(undefined2 *)(piVar8 + 0xd) = 0x138;
          *(undefined2 *)(piVar8 + 0x10) = DAT_006d9bd4;
        }
      }
      else {
        piVar8[0xf] = piVar8[0xf] + (int)(char)piVar8[0xb];
        if (*(short *)((int)piVar8 + 0x32) < 0x11) {
          uVar11 = piVar8[0xe];
          uVar17 = uVar11 & 0xff000000;
          uVar12 = uVar11 >> 0x18 & 0x7f;
          bVar15 = (byte)(uVar11 >> 8);
          bVar13 = (byte)(uVar11 >> 0x10);
          if ((uVar11 & 0x80000000) == 0) {
            cVar14 = (char)uVar12;
            if (uVar12 < (uVar11 & 0xff)) {
              uStack_38 = (uint)(byte)((char)uVar11 - cVar14);
            }
            else {
              uStack_38 = 0;
            }
            if (uVar12 < bVar15) {
              cVar16 = bVar15 - cVar14;
            }
            else {
              cVar16 = '\0';
            }
            if (uVar12 < bVar13) {
              cVar14 = bVar13 - cVar14;
            }
            else {
              cVar14 = '\0';
            }
          }
          else {
            uStack_38 = (uint)(byte)((char)piVar8[10] + (char)uVar11);
            cVar16 = bVar15 + *(char *)((int)piVar8 + 0x29);
            cVar14 = bVar13 + *(char *)((int)piVar8 + 0x2a);
            if (*(short *)((int)piVar8 + 0x32) == 0x10) {
              uVar17 = 0x10000000;
            }
          }
          piVar8[0xe] = (uint)CONCAT11(cVar14,cVar16) << 8 | uStack_38 | uVar17;
        }
      }
    }
    if (*(ushort *)((int)piVar8 + 0x32) != 0) {
      if ((*(ushort *)(piVar8 + 0x10) < 0x30) && ((*(ushort *)((int)piVar8 + 0x32) & 1) != 0)) {
        *(undefined2 *)(piVar8 + 0x10) =
             *(undefined2 *)(&DAT_005fef70 + (uint)*(ushort *)(piVar8 + 0x10) * 4);
      }
      if ((uVar4 & 0x40) == 0) {
        if ((uVar4 & 0x20) != 0) {
          uVar11 = piVar8[0xe];
          uVar17 = uVar11 & 0xff000000;
          uVar12 = uVar11 >> 0x18 & 0x7f;
          bVar15 = (byte)(uVar11 >> 8);
          bVar13 = (byte)(uVar11 >> 0x10);
          if ((uVar11 & 0x80000000) == 0) {
            cVar14 = (char)uVar12;
            if (uVar12 < (uVar11 & 0xff)) {
              uStack_2c = (uint)(byte)((char)uVar11 - cVar14);
            }
            else {
              uStack_2c = 0;
            }
            if (uVar12 < bVar15) {
              cVar16 = bVar15 - cVar14;
            }
            else {
              cVar16 = '\0';
            }
            if (uVar12 < bVar13) {
              cVar14 = bVar13 - cVar14;
            }
            else {
              cVar14 = '\0';
            }
          }
          else {
            uStack_2c = (uint)(byte)((char)piVar8[10] + (char)uVar11);
            cVar16 = bVar15 + *(char *)((int)piVar8 + 0x29);
            cVar14 = bVar13 + *(char *)((int)piVar8 + 0x2a);
            if (*(short *)((int)piVar8 + 0x32) == 0x10) {
              uVar17 = 0x10000000;
            }
          }
          piVar8[0xe] = (uint)CONCAT11(cVar14,cVar16) << 8 | uStack_2c | uVar17;
        }
      }
      else {
        if ((char)piVar8[10] == '\0') {
          uStack_34 = piVar8[0xe];
          uVar12 = uStack_34 & 0xff000000;
          uVar11 = uStack_34 >> 0x18 & 0x7f;
          bVar15 = (byte)(uStack_34 >> 8);
          bVar13 = (byte)(uStack_34 >> 0x10);
          if ((uStack_34 & 0x80000000) == 0) {
            cVar14 = (char)uVar11;
            if (uVar11 < (uStack_34 & 0xff)) {
              uStack_34 = (uint)(byte)((char)uStack_34 - cVar14);
            }
            else {
              uStack_34 = 0;
            }
            if (uVar11 < bVar15) {
              cVar16 = bVar15 - cVar14;
            }
            else {
              cVar16 = '\0';
            }
            if (uVar11 < bVar13) {
              cVar14 = bVar13 - cVar14;
            }
            else {
              cVar14 = '\0';
            }
          }
          else {
            uStack_34 = uStack_34 & 0xff;
            cVar14 = bVar13 + *(char *)((int)piVar8 + 0x2a);
            cVar16 = bVar15 + *(char *)((int)piVar8 + 0x29);
            if (*(short *)((int)piVar8 + 0x32) == 0x10) {
              uVar12 = 0x10000000;
            }
          }
          piVar8[0xe] = (uint)CONCAT11(cVar14,cVar16) << 8 | uStack_34 | uVar12;
          if (CONCAT11(cVar14,cVar16) == 0 && uStack_34 == 0) {
            piVar8[0xe] = 0x8010101;
            *(undefined1 *)(piVar8 + 10) = 1;
          }
          if (0x20 < piVar8[0xf]) {
            piVar8[0xf] = piVar8[0xf] + -0x20;
          }
        }
        else if (*(short *)((int)piVar8 + 0x32) < 9) {
          uVar11 = piVar8[0xe];
          *(undefined1 *)(piVar8 + 10) = 0;
          uVar12 = uVar11 & 0xffffff;
          piVar8[0xe] = uVar12 | 0x10000000;
          bVar15 = (byte)(uVar12 >> 8);
          bVar13 = (byte)(uVar12 >> 0x10);
          if ((uVar11 & 0xff) < 0x11) {
            uStack_30 = 0;
          }
          else {
            uStack_30 = (uint)(byte)((char)uVar12 - 0x10);
          }
          if (bVar15 < 0x11) {
            cVar14 = '\0';
          }
          else {
            cVar14 = bVar15 - 0x10;
          }
          if (bVar13 < 0x11) {
            cVar16 = '\0';
          }
          else {
            cVar16 = bVar13 - 0x10;
          }
          piVar8[0xe] = (uint)CONCAT11(cVar16,cVar14) << 8 | uStack_30 | 0x10000000;
        }
        else {
          sub_428010(piVar8);
          piVar8[0xf] = piVar8[0xf] + 0x10;
        }
        if (piVar8[7] < 0x3c) {
          piVar8[7] = piVar8[7] + 4;
          if (piVar8[6] < -7) {
            piVar8[6] = piVar8[6] + 4;
          }
          else if (7 < piVar8[6]) {
            piVar8[6] = piVar8[6] + -4;
          }
          iVar7 = piVar8[8];
          if (iVar7 < -7) {
            piVar8[8] = iVar7 + 4;
          }
          else if (7 < iVar7) {
            piVar8[8] = iVar7 + -4;
          }
        }
      }
    }
    piVar8 = (int *)*piVar8;
  } while( true );
}

