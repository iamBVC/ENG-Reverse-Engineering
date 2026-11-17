/* sub_419E00 @ 00419e00   799 bytes */

void sub_419E00(int param_1)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  ushort *puVar6;
  ushort *puVar7;
  int local_8;
  uint local_4;
  
  if (DAT_00582364 < 1) {
    if (0 < DAT_00582370) {
      DAT_00584708 = DAT_00584708 ^ 1;
      DAT_00582370 = -5;
    }
    puVar6 = &DAT_00572100;
    piVar4 = &DAT_00584758;
    *DAT_005fcf70 = 0;
    do {
      if (param_1 != 2) {
        if (param_1 != 0) {
          iVar3 = 0;
          piVar2 = &DAT_005720e8;
          do {
            if (*piVar4 == *piVar2) break;
            piVar2 = piVar2 + 1;
            iVar3 = iVar3 + 1;
          } while ((int)piVar2 < 0x572100);
          if (iVar3 != 6) goto LAB_00419ed5;
        }
        if (0 < (int)(&DAT_0058226c)[*piVar4]) {
          *DAT_005fcf70 = *DAT_005fcf70 | *puVar6;
        }
      }
LAB_00419ed5:
      piVar4 = piVar4 + 1;
      puVar6 = puVar6 + 1;
    } while ((int)piVar4 < 0x584790);
    if (param_1 == 0) {
      if (DAT_00582270 == 0) {
        if ((1 < DAT_00581d74) && (DAT_005822dc == 1)) {
          if (DAT_00584774 == 0x1c) {
            *DAT_005fcf70 = *DAT_005fcf70 & 0xbfff;
          }
          *(byte *)((int)DAT_005fcf70 + 1) = *(byte *)((int)DAT_005fcf70 + 1) | 0x80;
        }
      }
      else {
        *(byte *)DAT_005fcf70 = (byte)*DAT_005fcf70 | 8;
      }
    }
    else {
      if (DAT_0058258c == 1) {
        *(byte *)DAT_005fcf70 = (byte)*DAT_005fcf70 | 0x10;
      }
      if (DAT_005825ac == 1) {
        *(byte *)DAT_005fcf70 = (byte)*DAT_005fcf70 | 0x40;
      }
      if (DAT_00582598 == 1) {
        *(byte *)DAT_005fcf70 = (byte)*DAT_005fcf70 | 0x80;
      }
      if (DAT_005825a0 == 1) {
        *(byte *)DAT_005fcf70 = (byte)*DAT_005fcf70 | 0x20;
      }
      if (DAT_005822dc == 1) {
        *(byte *)((int)DAT_005fcf70 + 1) = *(byte *)((int)DAT_005fcf70 + 1) | 0x40;
      }
      if (DAT_00582270 == 1) {
        *(byte *)((int)DAT_005fcf70 + 1) = *(byte *)((int)DAT_005fcf70 + 1) | 0x10;
      }
      if (DAT_005822a4 == 1) {
        *(byte *)((int)DAT_005fcf70 + 1) = *(byte *)((int)DAT_005fcf70 + 1) | 0x10;
      }
    }
    local_4 = 1;
    iVar3 = 0xc;
    puVar6 = DAT_005fcf70;
    piVar4 = DAT_00582260;
    while (((*piVar4 != 0 || (piVar4[1] == 0)) && (local_4 < DAT_005fcf6c))) {
      ((byte *)(iVar3 + (int)puVar6))[0] = 0;
      ((byte *)(iVar3 + (int)puVar6))[1] = 0;
      *(byte *)(iVar3 + 4 + (int)DAT_005fcf70) = 0x80;
      *(byte *)(iVar3 + 5 + (int)DAT_005fcf70) = 0x80;
      if ((piVar4[0x1d] == 0) || ((piVar4[0x1d] & 0x80000000U) != 0)) {
        local_4 = local_4 + 1;
        *(byte *)(iVar3 + 2 + (int)DAT_005fcf70) = 0x80;
        *(byte *)(iVar3 + 3 + (int)DAT_005fcf70) = 0x80;
        piVar4 = (int *)*piVar4;
        iVar3 = iVar3 + 0xc;
        puVar6 = DAT_005fcf70;
      }
      else {
        *(byte *)(iVar3 + 2 + (int)DAT_005fcf70) = *(byte *)(piVar4 + 0x1e);
        *(byte *)(iVar3 + 3 + (int)DAT_005fcf70) = *(byte *)(piVar4 + 0x1f);
        if ((piVar4[0x1d] & 0x40000000U) == 0) {
          *(byte *)(iVar3 + 9 + (int)DAT_005fcf70) = 0;
        }
        else {
          *(byte *)(iVar3 + 9 + (int)DAT_005fcf70) = 1;
        }
        local_8 = 0;
        puVar7 = &DAT_00572100;
        puVar6 = DAT_005fcf70;
        do {
          switch(*(int *)(piVar4[0x1c] + local_8)) {
          default:
            if (*(int *)(piVar4[0x1b] + *(int *)(piVar4[0x1c] + local_8) * 4) < 1)
            goto switchD_0041a063_caseD_ffffffff;
            goto LAB_0041a0a5;
          case 0x20:
            if (0x3f < piVar4[0x1e]) goto switchD_0041a063_caseD_ffffffff;
            goto LAB_0041a092;
          case 0x21:
            iVar5 = piVar4[0x1e];
            break;
          case 0x22:
            if (0x3f < piVar4[0x1f]) goto switchD_0041a063_caseD_ffffffff;
            bVar1 = *(byte *)(iVar3 + 9 + (int)puVar6);
            goto joined_r0x0041a083;
          case 0x23:
            iVar5 = piVar4[0x1f];
            break;
          case -1:
            goto switchD_0041a063_caseD_ffffffff;
          }
          if (0xc0 < iVar5) {
LAB_0041a092:
            bVar1 = *(byte *)(iVar3 + 9 + (int)puVar6);
joined_r0x0041a083:
            if (bVar1 == 0) {
LAB_0041a0a5:
              *(ushort *)(iVar3 + (int)puVar6) = *(ushort *)(iVar3 + (int)puVar6) | *puVar7;
              puVar6 = DAT_005fcf70;
            }
          }
switchD_0041a063_caseD_ffffffff:
          puVar7 = puVar7 + 1;
          local_8 = local_8 + 4;
        } while ((int)puVar7 < 0x57211c);
        piVar4 = (int *)*piVar4;
        local_4 = local_4 + 1;
        iVar3 = iVar3 + 0xc;
      }
    }
    sub_4256C0(param_1);
  }
  else if (DAT_005846dc == 0) {
    DAT_00584654 = 3;
    DAT_005846d8 = 0xc;
    DAT_005846dc = 1;
    if (DAT_0058372c == 0) {
      sub_415390(1);
      return;
    }
  }
  return;
}

