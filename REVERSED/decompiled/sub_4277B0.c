/* sub_4277B0 @ 004277b0   1060 bytes */

void sub_4277B0(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  iVar8 = 0;
  if (DAT_00584640 != 0) {
    return;
  }
  if ((DAT_006d9e74 & 0x20000) == 0) {
    DAT_005fd03c = 0;
  }
  else {
    if (DAT_00584e64 == DAT_005fcf90) {
      if (DAT_005fd03c == 0) goto LAB_004279c6;
    }
    else {
      DAT_005fcf90 = DAT_00584e64;
      DAT_005fd03c = 0x5a;
    }
    local_10 = local_10 & 0xffff0000;
    iVar6 = 0;
    iVar7 = 0;
    cVar1 = *(&PTR_s_SEGRETO__0057ba54)[DAT_00584f04];
    uVar5 = DAT_005fd03c - 1;
    while (DAT_005fd03c = uVar5, cVar1 != '\0') {
      iVar2 = sub_436A20(cVar1);
      iVar6 = iVar6 + iVar2;
      iVar7 = iVar7 + 1;
      uVar5 = DAT_005fd03c;
      cVar1 = (&PTR_s_SEGRETO__0057ba54)[DAT_00584f04][iVar7];
    }
    pcVar3 = (&PTR_s_SEGRETO__0057ba54)[DAT_00584f04];
    if (*pcVar3 != '\0') {
      iVar2 = 0;
      local_4 = iVar7 * 4 + 0x20;
      local_8 = 0;
      local_c = local_4;
      do {
        local_10 = CONCAT31(local_10._1_3_,pcVar3[iVar8]);
        if (local_c < uVar5) {
          if (local_8 < 0x5a - uVar5) {
            iVar7 = sub_436A20(local_10,((int)(&DAT_00574318)[(uVar5 + iVar8 & 0x3f) * 0x40] >> 8) +
                                        0x70);
            iVar7 = -(iVar7 / 2);
          }
          else {
            iVar7 = (local_8 - 0x5a) + uVar5;
            if (0x1f < iVar7) goto LAB_00427989;
            iVar4 = sub_436A20(local_10,((int)(&DAT_00574318)[(uVar5 + iVar8 & 0x3f) * 0x40] >> 8) +
                                        0x70);
            iVar7 = *(int *)(&DAT_005738c0 + iVar7 * 4) - iVar4 / 2;
          }
LAB_0042797b:
          sub_436C60(&local_10,iVar2 + iVar7 + 6 + (0x200 - iVar6) / 2);
          uVar5 = DAT_005fd03c;
        }
        else {
          iVar7 = local_4 - uVar5;
          if (iVar7 < 0x20) {
            iVar4 = sub_436A20(local_10,((int)(&DAT_00574318)[(uVar5 + iVar8 & 0x3f) * 0x40] >> 8) +
                                        0x70);
            iVar7 = -*(int *)(&DAT_005738c0 + iVar7 * 4) - iVar4 / 2;
            goto LAB_0042797b;
          }
        }
LAB_00427989:
        local_c = local_c - 4;
        iVar8 = iVar8 + 1;
        local_8 = local_8 + 4;
        pcVar3 = (&PTR_s_SEGRETO__0057ba54)[DAT_00584f04];
        local_4 = local_4 - 4;
        iVar2 = iVar2 + 0x10;
      } while (pcVar3[iVar8] != '\0');
    }
  }
LAB_004279c6:
  iVar8 = 0;
  if ((DAT_006d9e74 & 0x40000) == 0) {
    DAT_005fcf98 = 0;
    DAT_005fd044 = 0;
    return;
  }
  if (DAT_005fcf98 == 0) {
    DAT_005fcf98 = 1;
    DAT_005fd044 = 0x5a;
  }
  else if (DAT_005fd044 == 0) {
    return;
  }
  local_10 = local_10 & 0xffff0000;
  iVar6 = 0;
  iVar7 = 0;
  cVar1 = *(&PTR_s_Punto_di_controllo_0057ba58)[DAT_00584f04];
  uVar5 = DAT_005fd044 - 1;
  while (DAT_005fd044 = uVar5, cVar1 != '\0') {
    iVar2 = sub_436A20(cVar1);
    iVar6 = iVar6 + iVar2;
    iVar7 = iVar7 + 1;
    uVar5 = DAT_005fd044;
    cVar1 = (&PTR_s_Punto_di_controllo_0057ba58)[DAT_00584f04][iVar7];
  }
  pcVar3 = (&PTR_s_Punto_di_controllo_0057ba58)[DAT_00584f04];
  if (*pcVar3 != '\0') {
    iVar2 = 0;
    local_4 = iVar7 * 4 + 0x20;
    local_c = 0;
    local_8 = local_4;
    do {
      local_10 = CONCAT31(local_10._1_3_,pcVar3[iVar8]);
      if (local_8 < uVar5) {
        if (local_c < 0x5a - uVar5) {
          iVar7 = sub_436A20(local_10,((int)(&DAT_00574318)[(uVar5 + iVar8 & 0x3f) * 0x40] >> 8) +
                                      0x70);
          iVar7 = -(iVar7 / 2);
        }
        else {
          iVar7 = (local_c - 0x5a) + uVar5;
          if (0x1f < iVar7) goto LAB_00427b91;
          iVar4 = sub_436A20(local_10,((int)(&DAT_00574318)[(uVar5 + iVar8 & 0x3f) * 0x40] >> 8) +
                                      0x70);
          iVar7 = *(int *)(&DAT_005738c0 + iVar7 * 4) - iVar4 / 2;
        }
LAB_00427b83:
        sub_436C60(&local_10,iVar2 + iVar7 + 6 + (0x200 - iVar6) / 2);
        uVar5 = DAT_005fd044;
      }
      else {
        iVar7 = local_4 - uVar5;
        if (iVar7 < 0x20) {
          iVar4 = sub_436A20(local_10,((int)(&DAT_00574318)[(uVar5 + iVar8 & 0x3f) * 0x40] >> 8) +
                                      0x70);
          iVar7 = -*(int *)(&DAT_005738c0 + iVar7 * 4) - iVar4 / 2;
          goto LAB_00427b83;
        }
      }
LAB_00427b91:
      local_8 = local_8 - 4;
      iVar8 = iVar8 + 1;
      local_c = local_c + 4;
      pcVar3 = (&PTR_s_Punto_di_controllo_0057ba58)[DAT_00584f04];
      local_4 = local_4 - 4;
      iVar2 = iVar2 + 0x10;
    } while (pcVar3[iVar8] != '\0');
  }
  return;
}

