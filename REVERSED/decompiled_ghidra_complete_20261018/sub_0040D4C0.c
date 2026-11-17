/* sub_40D4C0 @ 0040d4c0   973 bytes */

void sub_40D4C0(char *param_1,int *param_2)

{
  int *piVar1;
  size_t sVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  byte bVar10;
  int iVar11;
  uint uVar12;
  size_t sVar13;
  size_t sVar14;
  uint uVar15;
  char *pcVar16;
  size_t local_14;
  char *local_10;
  int local_8;
  
  param_1[0x360] = '\0';
  param_1[0x361] = '\0';
  param_1[0x362] = '\0';
  param_1[0x363] = '\0';
  param_1[0x35c] = '\0';
  param_1[0x35d] = '\0';
  param_1[0x35e] = '\0';
  param_1[0x35f] = '\0';
  *(int **)(param_1 + 0x368) = param_2;
  iVar5 = *param_1 * 0x10;
  piVar1 = (int *)(s_Logfile__s_started_now_today__wr_005713e8 + iVar5 + 0x28);
  iVar8 = *(int *)*param_2;
  *param_2 = (int)((int *)*param_2 + 1);
  pcVar16 = *(char **)(DAT_006da334 + -4 + (iVar8 + 1) * DAT_006da338 * 4);
  if (*pcVar16 == '#') {
    if (DAT_006d94b4 != -1) {
      sub_546990(DAT_006d94b4);
    }
    uVar6 = sub_40D890(pcVar16 + 1);
    DAT_006d94b4 = sub_546620(0,param_2,uVar6);
  }
  bVar10 = 0;
  param_2 = (int *)0x0;
  pcVar16 = *(char **)(DAT_006da334 + (DAT_006da338 * iVar8 + DAT_00584f04) * 4);
  iVar8 = *(int *)(s_Logfile__s_started_now_today__wr_005713e8 + iVar5 + 0x2c);
  iVar9 = *piVar1;
  local_14 = 0;
  if (*pcVar16 == '\"') {
    pcVar16 = pcVar16 + 1;
  }
  pcVar7 = param_1 + 4;
  iVar11 = 0xc;
  do {
    *pcVar7 = '\0';
    pcVar7 = pcVar7 + 0x40;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  pcVar7 = &DAT_00581974;
  do {
    cVar3 = sub_40D450(*pcVar16);
    if (cVar3 == '\0') {
      if ((*pcVar16 == ' ') && (cVar3 = sub_40D450(pcVar16[1]), cVar3 != '\0')) {
        if ((pcVar16[2] == ',') || (pcVar16[2] == '.')) {
          pcVar16 = pcVar16 + 1;
          goto LAB_0040d5d8;
        }
      }
      *pcVar7 = *pcVar16;
      pcVar7 = pcVar7 + 1;
    }
    else if (pcVar16[1] == ' ') {
      pcVar16 = pcVar16 + 1;
    }
LAB_0040d5d8:
    if (*pcVar16 == '\0') break;
    pcVar16 = pcVar16 + 1;
  } while( true );
  uVar15 = 0;
  pcVar16 = &DAT_00581974;
  if ((DAT_00581974 == '*') && (param_1 == &DAT_006d9858)) {
    sub_546960(DAT_006d94b4,0);
    DAT_006d9858 = 0;
    return;
  }
  local_10 = param_1 + 4;
  local_8 = 0;
  sVar13 = 0;
  while( true ) {
    while( true ) {
      bVar4 = pcVar16[uVar15];
      sVar14 = uVar15;
      sVar2 = uVar15;
      if (bVar4 == 0x20) {
        param_2 = (int *)((int)param_2 + 10);
      }
      else if (((bVar4 != 0x22) && (bVar4 != 0)) && (sVar14 = sVar13, sVar2 = local_14, bVar4 != 10)
              ) {
        param_2 = (int *)((int)param_2 + (uint)*(ushort *)(DAT_006da354 + 4 + (uint)bVar4 * 8));
        sVar14 = local_14;
      }
      local_14 = sVar2;
      sVar13 = sVar14;
      if (((bVar4 == 0x22) || (bVar4 == 0)) ||
         ((bVar4 == 10 || (((iVar8 - iVar9) - 0xcU < param_2 || (0x40 < uVar15)))))) break;
      uVar15 = uVar15 + 1;
    }
    _strncpy(local_10,pcVar16,sVar14);
    bVar10 = bVar10 + 1;
    iVar11 = local_8 + sVar14;
    local_8 = local_8 + 0x40;
    local_10 = local_10 + 0x40;
    param_1[iVar11 + 4] = '\0';
    if ((pcVar16[uVar15] == '\"') || (pcVar16[uVar15] == '\0')) break;
    uVar15 = 0;
    pcVar16 = pcVar16 + sVar14 + 1;
    param_2 = (int *)0x0;
  }
  param_1[1] = bVar10;
  param_1[2] = '\0';
  param_1[3] = bVar10;
  if (bVar10 == 1) {
    *(short *)(param_1 + 0x304) =
         (short)((uint)((*(int *)(s_Logfile__s_started_now_today__wr_005713e8 + iVar5 + 0x2c) -
                        (int)param_2) + *piVar1) >> 1);
  }
  else {
    *(short *)(param_1 + 0x304) = (short)*piVar1 + 6;
  }
  uVar15 = (int)*(uint *)(&DAT_0057141c + iVar5) >> 0x1f;
  iVar8 = (*(uint *)(&DAT_0057141c + iVar5) ^ uVar15) - uVar15;
  if ((1 < iVar8) && (bVar4 = (byte)iVar8, param_1[3] = bVar4, bVar10 < bVar4)) {
    param_1[3] = bVar10;
  }
  if (*(int *)(param_1 + 0x364) != 0) {
    uVar15 = (int)*(uint *)(&DAT_0057141c + iVar5) >> 0x1f;
    if ((int)((*(uint *)(&DAT_0057141c + iVar5) ^ uVar15) - uVar15) < 2) {
      uVar15 = 0xffffffff;
      pcVar16 = &DAT_00581974;
      do {
        if (uVar15 == 0) break;
        uVar15 = uVar15 - 1;
        cVar3 = *pcVar16;
        pcVar16 = pcVar16 + 1;
      } while (cVar3 != '\0');
      *(uint *)(param_1 + 0x364) = (~uVar15 - 1) * 4;
    }
    else {
      cVar3 = param_1[3];
      uVar15 = 0;
      param_1[0x364] = '\0';
      param_1[0x365] = '\0';
      param_1[0x366] = '\0';
      param_1[0x367] = '\0';
      if (cVar3 != '\0') {
        pcVar16 = param_1 + 4;
        do {
          uVar12 = 0xffffffff;
          pcVar7 = pcVar16;
          do {
            if (uVar12 == 0) break;
            uVar12 = uVar12 - 1;
            cVar3 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar3 != '\0');
          uVar15 = uVar15 + 1;
          *(uint *)(param_1 + 0x364) = *(int *)(param_1 + 0x364) + (~uVar12 - 1);
          pcVar16 = pcVar16 + 0x40;
        } while (uVar15 < (byte)param_1[3]);
      }
      *(int *)(param_1 + 0x364) = *(int *)(param_1 + 0x364) << 2;
    }
  }
  if (*(int *)(&DAT_0057141c + iVar5) < 1) {
    if (*(int *)(&DAT_0057141c + iVar5) < 0) {
      param_2 = *(int **)(s_Logfile__s_started_now_today__wr_005713e8 + iVar5 + 0x30);
      iVar9 = (int)param_2 + (uint)(byte)param_1[3] * -0xe;
      iVar8 = iVar9 + 10;
    }
    else {
      iVar8 = *(int *)(s_Logfile__s_started_now_today__wr_005713e8 + iVar5 + 0x30);
      uVar15 = (uint)(byte)param_1[3];
      iVar11 = (int)(uVar15 * 0xe + -4) / 2;
      iVar9 = iVar8 - iVar11;
      param_2 = (int *)(iVar11 + 4 + iVar8);
      iVar8 = ((int)(uVar15 * -4 + 4) / 2 - (uVar15 * 10) / 2) + 10 + iVar8;
    }
    iVar9 = iVar9 + -4;
    *(int *)(param_1 + 0x358) = iVar8;
  }
  else {
    iVar9 = *(int *)(s_Logfile__s_started_now_today__wr_005713e8 + iVar5 + 0x30);
    param_2 = (int *)(iVar9 + 4 + (uint)(byte)param_1[3] * 0xe);
    *(int *)(param_1 + 0x358) = iVar9 + 0xe;
  }
  *(int *)(param_1 + 0x348) = *piVar1;
  uVar6 = *(undefined4 *)(s_Logfile__s_started_now_today__wr_005713e8 + iVar5 + 0x2c);
  *(int *)(param_1 + 0x350) = iVar9;
  *(undefined4 *)(param_1 + 0x34c) = uVar6;
  *(int **)(param_1 + 0x354) = param_2;
  return;
}

