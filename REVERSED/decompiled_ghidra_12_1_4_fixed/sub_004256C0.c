/* sub_4256C0 @ 004256c0   1249 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_4256C0(int param_1)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  byte *pbVar11;
  int iVar12;
  uint local_8;
  
  uVar8 = 0;
  if ((param_1 != 0) || (DAT_00582260 == &DAT_00582264)) {
    *(byte *)(DAT_005fcf70 + 0xb) = *(byte *)(DAT_005fcf70 + 0xb) | 0x7f;
  }
  uVar6 = 0;
  if (DAT_005fcf6c != 0) {
    do {
      iVar4 = uVar6 * 0xc;
      *(undefined1 *)(iVar4 + 0xb + DAT_005fcf70) = 0x7f;
      DAT_005fcf18 = 3;
      if ((((((_DAT_00584f08 == 0) || (*(char *)(iVar4 + 10 + DAT_005fcf70) == '\0')) ||
            ((*(byte *)(iVar4 + 0xb + DAT_005fcf70) & 0x40) == 0)) ||
           ((DAT_005846e4 != 3 && (DAT_005846e4 != 5)))) ||
          ((DAT_00584640 != 0 && (DAT_00573400 != '\x02')))) ||
         ((DAT_0058372c != 0 || (uVar6 != 0)))) {
        *(undefined1 *)(iVar4 + 7 + DAT_005fcf70) = 0;
        *(undefined1 *)(iVar4 + 8 + DAT_005fcf70) = 0;
      }
      else if (DAT_005fcf64 == 0) {
        *(undefined1 *)(DAT_005fcf70 + 7) = 0;
        *(undefined1 *)(DAT_005fcf70 + 8) = DAT_005fcf14;
      }
      else {
        *(undefined1 *)(DAT_005fcf70 + 7) = 1;
        *(undefined1 *)(DAT_005fcf70 + 8) = DAT_005fcf14;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < DAT_005fcf6c);
  }
  iVar4 = DAT_005fcf0c;
  DAT_005fcf2c = 0;
  DAT_005fcf00 = (short)DAT_005790a4;
  DAT_005fcf1c = 0;
  DAT_005fcefc = 0;
  if (DAT_005fcf3c == 0) {
    local_8 = DAT_005fcf6c;
    if (DAT_005846e4 == 4) {
      local_8 = 1;
    }
    if (local_8 == 0) goto LAB_00425b31;
    pbVar11 = (byte *)(DAT_005fcf70 + 0xb);
    sVar3 = DAT_005fcf4e;
    do {
      uVar6 = DAT_005fcefc;
      uVar2 = *(ushort *)(pbVar11 + -0xb);
      uVar7 = (uint)uVar2;
      uVar9 = uVar8;
      if (*pbVar11 != 0) {
        uVar9 = uVar8 | uVar7 & 9;
      }
      uVar8 = uVar9;
      if (((*pbVar11 & 1) != 0) && (DAT_005fcefc < 0x2a)) {
        if ((uVar2 & 0x10) != 0) {
          DAT_005fcf2c = 0x1fc0;
        }
        if ((uVar2 & 0x40) != 0) {
          DAT_005fcf2c = -0x2000;
        }
        if ((uVar2 & 0x80) != 0) {
          DAT_005fcf1c = 0x1fc0;
        }
        if ((uVar2 & 0x20) != 0) {
          DAT_005fcf1c = -0x2000;
        }
        fpatan((float10)DAT_005fcf1c,(float10)DAT_005fcf2c);
        uVar8 = uVar9 | uVar7 & 0xf0;
        DAT_005fcf4e = __ftol();
        if ((uVar2 & 0xf0) != 0) {
          uVar6 = 0xb5;
          DAT_005fcf18 = 2;
          DAT_005fcefc = 0xb5;
        }
        sVar3 = DAT_005fcf4e;
        if ((pbVar11[-2] != 0) && (uVar6 < 0x2a)) {
          bVar1 = pbVar11[-9];
          if (bVar1 < 0x40) {
            uVar8 = CONCAT31((int3)(uVar9 >> 8),(char)uVar8) | 0x80;
          }
          if (0xbf < bVar1) {
            uVar8 = uVar8 | 0x20;
          }
          if (pbVar11[-8] < 0x40) {
            uVar8 = uVar8 | 0x10;
          }
          if (0xbf < pbVar11[-8]) {
            uVar8 = uVar8 | 0x40;
          }
          iVar4 = 0x80 - (uint)bVar1;
          iVar5 = 0x80 - (uint)pbVar11[-8];
          if (iVar4 < 0x80) {
            if (iVar4 < -0x80) {
              iVar4 = -0x80;
            }
          }
          else {
            iVar4 = 0x7f;
          }
          if (iVar5 < 0x80) {
            if (iVar5 < -0x80) {
              iVar5 = -0x80;
            }
          }
          else {
            iVar5 = 0x7f;
          }
          DAT_005fcf2c = iVar5 * 0x40;
          DAT_005fcf1c = iVar4 * 0x40;
          iVar4 = __ftol();
          DAT_005fcefc = iVar4 >> 0xc;
          fpatan((float10)DAT_005fcf1c,(float10)DAT_005fcf2c);
          DAT_005fcf4e = __ftol();
          sVar3 = DAT_005fcf4e;
        }
      }
      bVar1 = *pbVar11;
      if ((bVar1 & 2) != 0) {
        uVar8 = uVar8 | uVar7 & 0x8000;
      }
      if ((bVar1 & 4) != 0) {
        uVar8 = uVar8 | uVar7 & 0x4000;
      }
      if ((bVar1 & 8) != 0) {
        uVar8 = uVar8 | uVar7 & 0xc00;
      }
      if ((bVar1 & 0x10) != 0) {
        uVar8 = uVar8 | uVar7 & 0x2000;
      }
      if ((bVar1 & 0x20) != 0) {
        uVar8 = uVar8 | uVar7 & 0x1000;
      }
      pbVar11 = pbVar11 + 0xc;
      local_8 = local_8 - 1;
    } while (local_8 != 0);
  }
  else {
    if (DAT_005fcf04 <= DAT_005fcf0c) goto LAB_00425b31;
    _DAT_0058471c = (uint)*(ushort *)(DAT_005fcf5c + 4 + DAT_005fcf0c * 8);
    uVar6 = (uint)*(ushort *)(DAT_005fcf5c + DAT_005fcf0c * 8);
    DAT_005fcf00 = *(short *)(DAT_005fcf5c + 2 + DAT_005fcf0c * 8);
    iVar12 = *(char *)(DAT_005fcf5c + 6 + DAT_005fcf0c * 8) * 0x40;
    iVar10 = *(char *)(DAT_005fcf5c + 7 + DAT_005fcf0c * 8) * 0x40;
    DAT_005fcf1c = iVar12;
    DAT_005fcf2c = iVar10;
    iVar5 = __ftol();
    DAT_005fcefc = iVar5 >> 0xc;
    fpatan((float10)DAT_005fcf1c,(float10)DAT_005fcf2c);
    DAT_005fcf4e = __ftol();
    DAT_005fcf0c = iVar4 + 1;
    DAT_005fcf54 = DAT_005fcf54 + -1;
    sVar3 = DAT_005fcf4e;
    if (((uVar6 != 0) || (iVar12 != 0)) || (uVar8 = 0, iVar10 != 0)) {
      uVar8 = uVar6 + 1;
    }
  }
  if ((0x54 < DAT_005fcefc) && (DAT_006d9e1c != 0)) {
    sVar3 = (short)((sVar3 + DAT_005fcf00) * 0x10 -
                   ((ushort)((uint)*(undefined4 *)(DAT_006d9e1c + 0x24) >> 8) & 0xfff0)) >> 4;
    if ((-0x200 < sVar3) && (sVar3 < 0x200)) {
      uVar8 = uVar8 | 0x10000;
    }
    if ((-0x680 < sVar3) && (sVar3 < -0x180)) {
      uVar8 = uVar8 | 0x80000;
    }
    if ((0x180 < sVar3) && (sVar3 < 0x680)) {
      uVar8 = uVar8 | 0x40000;
    }
    if ((sVar3 < -0x600) || (0x600 < sVar3)) {
      uVar8 = uVar8 | 0x20000;
    }
  }
LAB_00425b31:
  DAT_005fcf20 = uVar8;
  DAT_005fcf44 = uVar8;
  if (*(char *)(DAT_005fcf70 + 9) != '\0') {
    if (*(byte *)(DAT_005fcf70 + 2) < 0x40) {
      uVar8 = uVar8 | 0x80;
    }
    DAT_005fcf44 = uVar8;
    if (0xbf < *(byte *)(DAT_005fcf70 + 2)) {
      DAT_005fcf44 = uVar8 | 0x20;
    }
    if (*(byte *)(DAT_005fcf70 + 3) < 0x40) {
      DAT_005fcf44 = DAT_005fcf44 | 0x10;
    }
    if (0xbf < *(byte *)(DAT_005fcf70 + 3)) {
      DAT_005fcf44 = DAT_005fcf44 | 0x40;
    }
  }
  if (1 < DAT_005fcf6c) {
    DAT_005fcf58 = 0;
  }
  return;
}

