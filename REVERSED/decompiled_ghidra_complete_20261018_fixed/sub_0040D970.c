/* sub_40D970 @ 0040d970   509 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_40D970(char *param_1)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  char *pcVar7;
  uint uVar8;
  char *pcVar9;
  
  if (*param_1 == '\0') {
    return;
  }
  if (*param_1 == -1) {
    *param_1 = '\0';
    return;
  }
  if ((DAT_005fd08c < 0x20) && (param_1 == &DAT_006d94e8)) {
    _DAT_006d9844 = 0;
    return;
  }
  if (((*(int *)(param_1 + 0x35c) != 0) && (*(int *)(param_1 + 0x364) == 0)) ||
     ((*(int *)(param_1 + 0x364) == 1 && (iVar4 = sub_546600(DAT_006d94b4,0), iVar4 != 2)))) {
    bVar2 = param_1[1];
    bVar3 = param_1[3];
    if ((int)((uint)bVar2 - (uint)(byte)param_1[2]) <= (int)(uint)bVar3) {
      if (DAT_006d94b4 != -1) {
        sub_546990(DAT_006d94b4);
        DAT_006d94b4 = -1;
      }
      *param_1 = -1;
      param_1[0x360] = '\x01';
      param_1[0x361] = '\0';
      param_1[0x362] = '\0';
      param_1[0x363] = '\0';
      param_1[0x364] = '\0';
      param_1[0x365] = '\0';
      param_1[0x366] = '\0';
      param_1[0x367] = '\0';
      return;
    }
    bVar5 = bVar3 + param_1[2];
    iVar4 = *(int *)(param_1 + 0x364);
    param_1[0x35c] = '\0';
    param_1[0x35d] = '\0';
    param_1[0x35e] = '\0';
    param_1[0x35f] = '\0';
    param_1[2] = bVar5;
    if (iVar4 == 1) {
      param_1[0x364] = '\0';
      param_1[0x365] = '\0';
      param_1[0x366] = '\0';
      param_1[0x367] = '\0';
      if ((int)((uint)bVar2 - (uint)bVar5) < (int)(uint)bVar3) {
        param_1[3] = bVar2 - bVar5;
      }
      uVar8 = (uint)(byte)param_1[3];
      if (uVar8 != 0) {
        pcVar7 = param_1 + (uint)(byte)param_1[2] * 0x40 + 4;
        do {
          uVar6 = 0xffffffff;
          pcVar9 = pcVar7;
          do {
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            cVar1 = *pcVar9;
            pcVar9 = pcVar9 + 1;
          } while (cVar1 != '\0');
          uVar8 = uVar8 - 1;
          *(uint *)(param_1 + 0x364) = *(int *)(param_1 + 0x364) + (~uVar6 - 1);
          pcVar7 = pcVar7 + 0x40;
        } while (uVar8 != 0);
      }
      *(int *)(param_1 + 0x364) = *(int *)(param_1 + 0x364) << 2;
    }
  }
  iVar4 = *(int *)(param_1 + 0x358);
  uVar8 = 0;
  if (param_1[3] != '\0') {
    do {
      sub_436C60(param_1 + ((byte)param_1[2] + uVar8) * 0x40 + 4,*(undefined2 *)(param_1 + 0x304),
                 iVar4);
      iVar4 = iVar4 + 0xe;
      uVar8 = uVar8 + 1;
    } while (uVar8 < (byte)param_1[3]);
  }
  if (1 < *(uint *)(param_1 + 0x364)) {
    *(uint *)(param_1 + 0x364) = *(uint *)(param_1 + 0x364) - 1;
  }
  sub_43C960(*(undefined4 *)(param_1 + 0x348),*(undefined4 *)(param_1 + 0x34c),
             *(undefined4 *)(param_1 + 0x350),*(int *)(param_1 + 0x354) + 1,0,0,0);
  if ((((byte)DAT_00584650 & 0x10) != 0) && (DAT_00581d74 == 0)) {
    sub_4368D0(&DAT_00571480,0xeb,1,1,4,0x1dd);
  }
  return;
}

