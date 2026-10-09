/* sub_428EA0 @ 00428ea0   3069 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_428EA0(int param_1,uint param_2,int *param_3,uint *param_4,undefined *param_5,int param_6)

{
  int *piVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char cVar8;
  short sVar9;
  int iVar10;
  int iVar11;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  
  sVar9 = 0;
  local_b = 0;
  local_a = 0;
  local_9 = 0;
  if (param_2 == 0x19) {
    if (*(char *)(param_6 + 0x153) == -1) {
      iVar4 = sub_427FF0(param_6);
    }
    else {
      iVar4 = (int)*(char *)(param_6 + 0x153);
    }
    if (iVar4 == -1) {
      return;
    }
    iVar5 = iVar4 * 0x34;
    (&DAT_005fe254)[iVar4 * 0xd] = *param_4;
    *(short *)(&DAT_005fe24a + iVar5) = (short)((int)param_4[1] >> 0xc);
    if (param_5 != (undefined *)0x0) {
      (&DAT_005fe246)[iVar5] = (char)param_5;
      (&DAT_005fe23c)[iVar4 * 0xd] = param_4[2];
      (&DAT_005fe260)[iVar5] = 1;
      *(char *)(param_6 + 0x153) = (char)iVar4;
      return;
    }
    if ((int)param_4[2] >> 0xc != 0) {
      (&DAT_005fe25c)[iVar4 * 0xd] = ((int)param_4[2] >> 0xc) * 0x20 + -0x20;
    }
    (&DAT_005fe260)[iVar5] = 1;
    *(char *)(param_6 + 0x153) = (char)iVar4;
    return;
  }
  if (param_2 == 0x1e) {
    if (*(char *)(param_6 + 0x153) == -1) {
      iVar4 = sub_427FF0(param_6);
    }
    else {
      iVar4 = (int)*(char *)(param_6 + 0x153);
    }
    if (iVar4 == -1) {
      return;
    }
    iVar5 = iVar4 * 0x34;
    (&DAT_005fe250)[iVar4 * 0xd] = param_5;
    bVar2 = (byte)((int)*param_4 >> 0xc);
    if ((*param_4 & 0xfff) == 0) {
      (&DAT_005fe243)[iVar5] = bVar2 & 0x7f;
    }
    else {
      (&DAT_005fe240)[iVar5] = bVar2;
      (&DAT_005fe241)[iVar5] = (char)((int)param_4[1] >> 0xc);
      (&DAT_005fe242)[iVar5] = (char)((int)param_4[2] >> 0xc);
      (&DAT_005fe243)[iVar5] = 0x80;
    }
    (&DAT_005fe260)[iVar5] = 1;
    *(char *)(param_6 + 0x153) = (char)iVar4;
    return;
  }
  if (param_2 == 0x1b) {
    uVar7 = *param_4;
    *(undefined **)(&DAT_005fd0c0 + (uVar7 >> 0xc) * 4) = param_5;
    *(uint *)(&DAT_005fef70 + (uVar7 >> 0xc) * 4) = param_4[1] >> 0xc;
    return;
  }
  iVar4 = sub_428700(param_3);
  piVar1 = DAT_006d9bd8;
  if (iVar4 != 0) {
    return;
  }
  if ((param_2 < 0x1000) && ((&DAT_00573960)[param_2 * 8] != '\0')) {
    *(short *)(&DAT_00573962 + param_2 * 8) = *(short *)(&DAT_00573962 + param_2 * 8) + 1;
    if (((int)(uint)*(ushort *)(&DAT_00573962 + param_2 * 8) < DAT_005724d4) &&
       (DAT_00586400 - *(int *)(&DAT_00573964 + param_2 * 8) < 10)) {
      return;
    }
    *(int *)(&DAT_00573964 + param_2 * 8) = DAT_00586400;
    *(undefined2 *)(&DAT_00573962 + param_2 * 8) = 0;
  }
  if (piVar1 == (int *)0x0) {
    return;
  }
  DAT_006d9bd8 = (int *)*piVar1;
  *piVar1 = (int)DAT_006d9bdc;
  if (DAT_006d9bdc != (int *)0x0) {
    *(int **)((int)DAT_006d9bdc + 4) = piVar1;
  }
  DAT_006d9bdc = piVar1;
  piVar1[2] = *param_3;
  piVar1[3] = param_3[1];
  iVar4 = param_3[2];
  piVar1[8] = 0;
  piVar1[7] = 0;
  piVar1[6] = 0;
  piVar1[0xb] = 0;
  *(undefined2 *)(piVar1 + 0xc) = 0;
  *(undefined2 *)(piVar1 + 0xd) = 0;
  piVar1[4] = iVar4;
  piVar1[0x11] = 0x20;
  iVar5 = (int)*(char *)(param_6 + 0x153);
  iVar4 = 0x1000;
  if (iVar5 == -1) {
    cVar8 = '\0';
  }
  else {
    sVar9 = *(short *)(&DAT_005fe24a + iVar5 * 0x34);
    cVar8 = (&DAT_005fe246)[iVar5 * 0x34];
    piVar1[9] = (&DAT_005fe23c)[iVar5 * 0xd];
    if ((&DAT_005fe254)[iVar5 * 0xd] != 0x1000) {
      iVar4 = (&DAT_005fe254)[iVar5 * 0xd];
    }
  }
  if (param_1 != 0x1000) {
    iVar4 = param_1;
  }
  iVar10 = iVar4 >> 3;
  if (0xfff < param_2) {
    param_2 = param_2 >> 0xc;
    *(ushort *)(piVar1 + 0xd) = (ushort)param_2 & 0xff;
    piVar1[7] = param_4[1];
    if ((((byte)param_2 & 3) == 1) || ((param_2 & 4) != 0)) {
      if ((param_2 & 0x100) != 0) {
        *(char *)((int)piVar1 + 0x2e) = -4 - cVar8;
      }
      if ((param_2 & 0x200) != 0) {
        *(byte *)((int)piVar1 + 0x35) = *(byte *)((int)piVar1 + 0x35) | 4;
      }
      piVar1[6] = *param_4;
      piVar1[8] = param_4[2];
    }
    else {
      *(short *)(piVar1 + 0xc) = (short)((int)*param_4 >> 0xc);
      uVar7 = param_4[1];
      *(byte *)((int)piVar1 + 0x35) = *(byte *)((int)piVar1 + 0x35) | 1;
      *(char *)(piVar1 + 0xb) = (char)((int)uVar7 >> 0xc);
    }
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    piVar1[0xe] = 0x808080;
    piVar1[0xf] = iVar10;
    goto switchD_004290d8_caseD_4;
  }
  if (0x2a < param_2 - 1) goto switchD_004290d8_caseD_4;
  iVar11 = iVar4 >> 5;
  switch(param_2) {
  case 1:
    piVar1[0xe] = (int)param_5;
    *(char *)((int)piVar1 + 0x2e) = -4 - cVar8;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x1e;
    *(undefined2 *)(piVar1 + 0xd) = 0x24;
    piVar1[0xf] = iVar4;
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    piVar1[8] = param_4[2];
    break;
  case 2:
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    piVar1[8] = param_4[2];
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x80;
    *(undefined2 *)(piVar1 + 0xd) = 1;
    if (0x1000 < iVar4) {
      *(short *)((int)piVar1 + 0x32) = (short)(iVar4 + -0x1000 >> 0xc);
      iVar4 = 0x1000;
    }
    piVar1[0xf] = iVar4 >> 3;
    break;
  case 3:
    uVar7 = sub_563C89();
    piVar1[2] = piVar1[2] + ((uVar7 & 0x3ff) - 0x200);
    uVar7 = sub_563C89();
    piVar1[4] = piVar1[4] + ((uVar7 & 0x3ff) - 0x200);
    piVar1[8] = 0;
    piVar1[6] = 0;
    uVar7 = sub_563C89();
    piVar1[7] = (uVar7 & 0x7f) + 0x1e;
    piVar1[9] = *param_4;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 1000;
    piVar1[0xf] = iVar4 >> 6;
    *(undefined2 *)(piVar1 + 0xd) = 0x209;
    break;
  case 6:
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    *(short *)(piVar1 + 0xc) = (short)((int)*param_4 >> 0xc);
    *(undefined1 *)(piVar1 + 0xb) = 0x20;
    piVar1[0xe] = 0x808080;
    piVar1[0xf] = iVar4 >> 6;
    piVar1[0x11] = 0x20;
    *(undefined2 *)(piVar1 + 0xd) = 0x138;
    _DAT_006d9bd4 = param_5;
    break;
  case 7:
    piVar1[0xe] = 0x808080;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    piVar1[8] = param_4[2];
    *(undefined1 *)((int)piVar1 + 0x2d) = 7;
    *(undefined1 *)((int)piVar1 + 0x2f) = 7;
    piVar1[0xf] = iVar11;
    *(undefined2 *)(piVar1 + 0xd) = 0x3b;
    break;
  case 8:
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    piVar1[0xe] = 0x808080;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x10;
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    piVar1[8] = param_4[2];
    piVar1[0xf] = iVar11;
    *(undefined2 *)(piVar1 + 0xd) = 0x3b;
    break;
  case 9:
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    piVar1[8] = param_4[2];
    if (param_5 == (undefined *)0x0) {
      iVar4 = sub_563C89();
      switch(iVar4 % 6) {
      case 0:
        param_5 = (undefined *)0xff6060;
        break;
      case 1:
        param_5 = &DAT_0060ff60;
        break;
      case 2:
        param_5 = &DAT_006060ff;
        break;
      case 3:
        param_5 = (undefined *)0xff60ff;
        break;
      case 4:
        param_5 = (undefined *)0xffff60;
        break;
      case 5:
        param_5 = &DAT_0060ffff;
      }
    }
    piVar1[0xe] = (int)param_5;
    *(undefined2 *)(piVar1 + 0x10) = 0;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x1e;
    *(undefined2 *)(piVar1 + 0xd) = 0x24;
    break;
  case 0xb:
    uVar7 = sub_563C89();
    piVar1[6] = (uVar7 & 0xf) - 3;
    uVar7 = sub_563C89();
    piVar1[8] = (uVar7 & 0xf) - 3;
    uVar7 = sub_563C89();
    piVar1[7] = (uVar7 & 0x5f) + 5;
    *(char *)((int)piVar1 + 0x2e) = -4 - cVar8;
    piVar1[0xe] = (int)param_5;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x78;
    *(undefined2 *)(piVar1 + 0xd) = 0x24;
    break;
  case 0xd:
    piVar1[0xe] = 0x808080;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    piVar1[0xf] = iVar10;
    uVar7 = _DAT_005ff030;
    _DAT_005ff030 = _DAT_005ff030 & 0xffffff07;
    piVar1[6] = *(int *)(&DAT_00573ac0 + (uVar7 & 7) * 4) << 4;
    piVar1[8] = *(int *)(&DAT_00573ae0 + (_DAT_005ff030 & 0xff) * 4) << 4;
    _DAT_005ff030 = CONCAT31(DAT_005ff030_1,DAT_005ff030 + '\x01');
    *(undefined2 *)(piVar1 + 0xd) = 0x39;
    break;
  case 0xe:
    piVar1[0xe] = 0x808080;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    piVar1[0xf] = iVar10;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    if (iVar4 < 0) {
      piVar1[6] = *param_4;
      piVar1[7] = param_4[1];
      piVar1[8] = param_4[2];
      *(undefined2 *)(piVar1 + 0xd) = 0x39;
    }
    else {
      piVar1[7] = 0x3c;
      *(undefined1 *)((int)piVar1 + 0x2d) = 7;
      *(undefined1 *)((int)piVar1 + 0x2f) = 7;
      *(undefined2 *)(piVar1 + 0xd) = 0x39;
    }
    break;
  case 0x14:
    piVar1[0xe] = 0x808080;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    bVar2 = sub_563C89();
    bVar3 = sub_563C89();
    *(byte *)((int)piVar1 + 0x2e) = (bVar2 & 0x1f) - (bVar3 & 0x1f);
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    piVar1[8] = param_4[2];
    *(undefined1 *)((int)piVar1 + 0x2d) = 0x1f;
    *(undefined1 *)((int)piVar1 + 0x2f) = 0x1f;
    piVar1[0xf] = iVar4 >> 7;
    *(undefined2 *)(piVar1 + 0xd) = 0x39;
    break;
  case 0x15:
    piVar1[0xe] = 0x808080;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    bVar2 = sub_563C89();
    bVar3 = sub_563C89();
    *(byte *)((int)piVar1 + 0x2e) = (bVar2 & 0xf) - (bVar3 & 0xf);
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    piVar1[8] = param_4[2];
    *(undefined1 *)((int)piVar1 + 0x2d) = 0xf;
    *(undefined1 *)((int)piVar1 + 0x2f) = 0xf;
    piVar1[0xf] = iVar4 >> 7;
    *(undefined2 *)(piVar1 + 0xd) = 1;
    break;
  case 0x1a:
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x40;
    *(short *)(piVar1 + 0xc) = (short)((int)*param_4 >> 0xc);
    *(undefined1 *)(piVar1 + 0xb) = 0;
    piVar1[0xe] = 0xa0a0a0;
    piVar1[0xf] = iVar11;
    piVar1[0x11] = 0x40;
    *(undefined2 *)(piVar1 + 0xd) = 0x138;
    break;
  case 0x1d:
    uVar7 = sub_563C89();
    piVar1[6] = (uVar7 & 0xf) - 3;
    uVar7 = sub_563C89();
    piVar1[8] = (uVar7 & 0xf) - 3;
    uVar7 = sub_563C89();
    piVar1[0xe] = 0xffffff;
    piVar1[7] = (uVar7 & 0x5f) + 5;
    *(char *)((int)piVar1 + 0x2e) = -4 - cVar8;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x78;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(undefined2 *)(piVar1 + 0xd) = 4;
    break;
  case 0x1f:
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    *(short *)(piVar1 + 0xc) = (short)((int)*param_4 >> 0xc);
    *(undefined1 *)(piVar1 + 0xb) = 0;
    piVar1[0xe] = 0x808080;
    piVar1[0xf] = iVar10;
    piVar1[0x11] = 0x20;
    *(undefined2 *)(piVar1 + 0xd) = 0x13a;
    break;
  case 0x20:
    piVar1[0xe] = 0x808080;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    piVar1[0xf] = iVar10;
    piVar1[0x11] = 0x20;
    *(undefined2 *)(piVar1 + 0xd) = 9;
    break;
  case 0x22:
    *(undefined2 *)(piVar1 + 0xd) = 0x400;
  case 0x21:
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    uVar7 = param_4[2];
    *(ushort *)(piVar1 + 0xd) = *(ushort *)(piVar1 + 0xd) | 0x828;
    piVar1[8] = uVar7;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x1e;
    piVar1[0xe] = (int)param_5;
    break;
  case 0x23:
  case 0x24:
    *(undefined2 *)(piVar1 + 0xd) = 0x2000;
  case 0xf:
  case 0x10:
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x40;
    piVar1[7] = param_4[1];
    *(char *)((int)piVar1 + 0x2e) = -4 - cVar8;
    piVar1[6] = *param_4;
    piVar1[8] = param_4[2];
    uVar7 = sub_563C89();
    iVar4 = *(int *)(&DAT_00573b00 + (uVar7 & 7) * 4);
    *(byte *)(piVar1 + 0xd) = *(byte *)(piVar1 + 0xd) | 0x39;
    piVar1[0xe] = iVar4;
    piVar1[0xf] = iVar11;
    break;
  case 0x25:
    *(undefined2 *)(piVar1 + 0xd) = 0x2000;
  case 0x11:
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    piVar1[0xe] = 0x1002060;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    *(undefined1 *)(piVar1 + 10) = 0;
    if (((param_4[1] == 0) && (*param_4 == 0)) && (param_4[2] == 0)) {
      uVar7 = sub_563C89();
      uVar6 = sub_563C89();
      piVar1[2] = piVar1[2] + ((uVar7 & 0x7f) - (uVar6 & 0x7f));
      piVar1[4] = piVar1[4] + ((uVar6 & 0x7f) - (uVar7 & 0x7f));
      piVar1[3] = piVar1[3] + (uVar7 & 0x3f);
      piVar1[7] = 0x3c;
    }
    else {
      piVar1[6] = *param_4;
      piVar1[7] = param_4[1];
      piVar1[8] = param_4[2];
    }
    *(byte *)(piVar1 + 0xd) = *(byte *)(piVar1 + 0xd) | 0x59;
    piVar1[0xf] = iVar11;
    *(undefined1 *)((int)piVar1 + 0x2d) = 7;
    *(undefined1 *)((int)piVar1 + 0x2f) = 7;
    break;
  case 0x26:
    *(undefined2 *)(piVar1 + 0xd) = 0x2000;
  case 0x12:
  case 0x1c:
    piVar1[0xe] = 0x808080;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    goto LAB_00429482;
  case 0x27:
    *(undefined2 *)(piVar1 + 0xd) = 0x2000;
  case 0x13:
    piVar1[0xe] = 0x808080;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    *(char *)((int)piVar1 + 0x2e) = -4 - cVar8;
LAB_00429482:
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    uVar7 = param_4[2];
    *(byte *)(piVar1 + 0xd) = *(byte *)(piVar1 + 0xd) | 1;
    piVar1[8] = uVar7;
    piVar1[0xf] = iVar10;
    break;
  case 0x28:
    *(undefined2 *)(piVar1 + 0xd) = 0x2000;
  case 0x16:
    *(byte *)(piVar1 + 0xd) = *(byte *)(piVar1 + 0xd) | 0x39;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    piVar1[0xe] = 0x7090;
    piVar1[0xf] = iVar11;
    break;
  case 0x29:
    *(undefined2 *)(piVar1 + 0xd) = 0x2000;
  case 0x17:
    piVar1[0xe] = 0x808080;
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    piVar1[7] = param_4[1];
    piVar1[6] = *param_4;
    uVar7 = param_4[2];
    *(byte *)(piVar1 + 0xd) = *(byte *)(piVar1 + 0xd) | 0x39;
    piVar1[8] = uVar7;
    piVar1[0xf] = iVar10;
    break;
  case 0x2a:
    *(undefined2 *)(piVar1 + 0xd) = 0x2000;
  case 0x18:
    *(undefined2 *)(piVar1 + 0x10) = param_5._0_2_;
    piVar1[0xe] = 0x808080;
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x20;
    *(char *)((int)piVar1 + 0x2e) = -4 - cVar8;
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    uVar7 = param_4[2];
    *(byte *)(piVar1 + 0xd) = *(byte *)(piVar1 + 0xd) | 0x39;
    piVar1[8] = uVar7;
    piVar1[0xf] = iVar10;
    break;
  case 0x2b:
    piVar1[6] = *param_4;
    piVar1[7] = param_4[1];
    piVar1[8] = param_4[2];
    *(short *)((int)piVar1 + 0x32) = sVar9 + 0x1e;
    piVar1[0xe] = (int)param_5;
    *(undefined2 *)(piVar1 + 0xd) = 0x4828;
  }
switchD_004290d8_caseD_4:
  if (iVar5 == -1) {
    uVar7 = 0;
  }
  else {
    iVar4 = iVar5 * 0x34;
    if ((&DAT_005fe250)[iVar5 * 0xd] == 0) {
      uVar7 = 0;
    }
    else {
      piVar1[0xe] = (&DAT_005fe250)[iVar5 * 0xd];
      local_b = (&DAT_005fe240)[iVar4];
      local_a = (&DAT_005fe241)[iVar4];
      local_9 = (&DAT_005fe242)[iVar4];
      uVar7 = (uint)(byte)(&DAT_005fe243)[iVar4];
    }
    if ((&DAT_005fe25c)[iVar5 * 0xd] != -1) {
      piVar1[0x11] = (&DAT_005fe25c)[iVar5 * 0xd];
    }
    (&DAT_005fe240)[iVar4] = 0;
    (&DAT_005fe241)[iVar4] = 0;
    (&DAT_005fe242)[iVar4] = 0;
    (&DAT_005fe243)[iVar4] = 0;
    (&DAT_005fe25c)[iVar5 * 0xd] = 0xffffffff;
    (&DAT_005fe250)[iVar5 * 0xd] = 0;
    (&DAT_005fe23c)[iVar5 * 0xd] = 0xffff0000;
    *(undefined2 *)(&DAT_005fe24a + iVar4) = 0;
    (&DAT_005fe254)[iVar5 * 0xd] = 0x1000;
    *(undefined1 *)(param_6 + 0x153) = 0xff;
    (&DAT_005fe260)[iVar4] = 0;
  }
  if (*(short *)((int)piVar1 + 0x32) == 0) {
    return;
  }
  if (uVar7 == 0) {
    uVar7 = (uint)(0xff / (longlong)(int)*(short *)((int)piVar1 + 0x32));
  }
  else if (uVar7 == 0x80) {
    *(undefined1 *)(piVar1 + 10) = local_b;
    *(undefined1 *)((int)piVar1 + 0x29) = local_a;
    *(undefined1 *)((int)piVar1 + 0x2a) = local_9;
    goto LAB_0042993d;
  }
  if (uVar7 == 0) {
    piVar1[0xe] = piVar1[0xe] | 0x1000000;
    return;
  }
LAB_0042993d:
  piVar1[0xe] = piVar1[0xe] | uVar7 << 0x18;
  return;
}

