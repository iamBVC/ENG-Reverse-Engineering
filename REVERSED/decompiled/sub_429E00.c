/* sub_429E00 @ 00429e00   2100 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_429E00(int param_1,int param_2,uint param_3,int *param_4,undefined *param_5,int param_6)

{
  int *piVar1;
  char cVar2;
  undefined4 uVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  cVar2 = *(char *)(param_1 + 0x150 + param_6);
  if (cVar2 == -1) {
    iVar6 = sub_427FF0(param_6);
  }
  else {
    iVar6 = (int)cVar2;
    if ((&DAT_005fe250)[iVar6 * 0xd] != 0) {
      (&DAT_005fe250)[iVar6 * 0xd] = (&DAT_005fe250)[iVar6 * 0xd];
    }
  }
  if (iVar6 != -1) {
    iVar9 = iVar6 * 0x34;
    piVar1 = (int *)(&DAT_005fe230 + iVar9);
    (&DAT_005fe260)[iVar9] = 1;
    *(char *)(param_1 + 0x150 + param_6) = (char)iVar6;
    *(undefined4 *)(&DAT_005fe238 + iVar9) = 0;
    *(undefined4 *)(&DAT_005fe234 + iVar9) = 0;
    *piVar1 = 0;
    *(undefined4 *)(&DAT_005fe244 + iVar9) = 0;
    *(undefined2 *)(&DAT_005fe248 + iVar9) = 0;
    (&DAT_005fe25c)[iVar6 * 0xd] = 0x20;
    (&DAT_005fe23c)[iVar6 * 0xd] = 0xffff0000;
    *(undefined2 *)(&DAT_005fe24c + iVar9) = 0;
    iVar8 = 0x1000;
    if (param_2 != 0x1000) {
      iVar8 = param_2;
    }
    iVar10 = iVar8 >> 3;
    if (0xfff < param_3) {
      param_3 = param_3 >> 0xc;
      *(ushort *)(&DAT_005fe24c + iVar9) = (ushort)param_3 & 0xff;
      *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
      bVar4 = (byte)param_3;
      if (((bVar4 & 3) == 1) || ((param_3 & 4) != 0)) {
        if ((param_3 & 0x100) != 0) {
          (&DAT_005fe246)[iVar9] = 0xfc;
        }
        if ((param_3 & 0x200) != 0) {
          *(ushort *)(&DAT_005fe24c + iVar9) = CONCAT11(4,bVar4);
        }
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
      }
      else {
        *(short *)(&DAT_005fe248 + iVar9) = (short)(*param_4 >> 0xc);
        (&DAT_005fe244)[iVar9] = (char)(param_4[1] >> 0xc);
        *(ushort *)(&DAT_005fe24c + iVar9) = CONCAT11(1,bVar4);
      }
      *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
      (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
      *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
      (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
      return;
    }
    if (param_3 - 1 < 0x2b) {
      iVar11 = iVar8 >> 5;
      switch(param_3) {
      case 1:
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        iVar8 = param_4[2];
        (&DAT_005fe246)[iVar9] = 0xfc;
        *(int *)(&DAT_005fe238 + iVar9) = iVar8;
        (&DAT_005fe250)[iVar6 * 0xd] = param_5;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x1e;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x24;
        break;
      case 2:
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 1;
        if (iVar8 < 0x1001) {
          (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        }
        else {
          (&DAT_005fe254)[iVar6 * 0xd] = 0x200;
          *(short *)(&DAT_005fe24a + iVar9) = (short)(iVar8 + -0x1000 >> 0xc);
        }
        break;
      case 3:
        *(undefined4 *)(&DAT_005fe238 + iVar9) = 0;
        *piVar1 = 0;
        uVar7 = sub_563C89();
        *(uint *)(&DAT_005fe234 + iVar9) = (uVar7 & 0x7f) + 0x1e;
        iVar10 = *param_4;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        (&DAT_005fe23c)[iVar6 * 0xd] = iVar10 >> 0xc;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 1000;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar8 >> 6;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x209;
        break;
      case 6:
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        iVar10 = *param_4;
        (&DAT_005fe244)[iVar9] = 0x20;
        *(short *)(&DAT_005fe248 + iVar9) = (short)(iVar10 >> 0xc);
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar8 >> 6;
        (&DAT_005fe25c)[iVar6 * 0xd] = 0x20;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x138;
        _DAT_006d9bd4 = param_5;
        break;
      case 7:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
        (&DAT_005fe245)[iVar9] = 7;
        (&DAT_005fe247)[iVar9] = 7;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar11;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x3b;
        break;
      case 8:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x10;
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
        (&DAT_005fe254)[iVar6 * 0xd] = iVar11;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x3b;
        break;
      case 9:
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
        if (param_5 == (undefined *)0x0) {
          iVar8 = sub_563C89();
          switch(iVar8 % 6) {
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
        (&DAT_005fe250)[iVar6 * 0xd] = param_5;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = 0;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x1e;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x24;
        break;
      case 0xb:
        uVar7 = sub_563C89();
        *piVar1 = (uVar7 & 0xf) - 3;
        uVar7 = sub_563C89();
        *(uint *)(&DAT_005fe238 + iVar9) = (uVar7 & 0xf) - 3;
        uVar7 = sub_563C89();
        (&DAT_005fe246)[iVar9] = 0xfc;
        *(uint *)(&DAT_005fe234 + iVar9) = (uVar7 & 0x5f) + 5;
        (&DAT_005fe250)[iVar6 * 0xd] = param_5;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x78;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x24;
        break;
      case 0xd:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        uVar7 = _DAT_005ff030;
        _DAT_005ff030 = _DAT_005ff030 & 0xffffff07;
        *piVar1 = *(int *)(&DAT_00573ac0 + (uVar7 & 7) * 4) << 4;
        *(int *)(&DAT_005fe238 + iVar9) = *(int *)(&DAT_00573ae0 + (_DAT_005ff030 & 0xff) * 4) << 4;
        _DAT_005ff030 = CONCAT31(DAT_005ff030_1,DAT_005ff030 + '\x01');
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x39;
        break;
      case 0xe:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        if (iVar8 < 0) {
          *piVar1 = *param_4;
          *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
          *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
          *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x39;
        }
        else {
          *(undefined4 *)(&DAT_005fe234 + iVar9) = 0x3c;
          (&DAT_005fe245)[iVar9] = 7;
          (&DAT_005fe247)[iVar9] = 7;
          *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x39;
        }
        break;
      case 0x14:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        bVar4 = sub_563C89();
        bVar5 = sub_563C89();
        (&DAT_005fe246)[iVar9] = (bVar4 & 0x1f) - (bVar5 & 0x1f);
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
        (&DAT_005fe245)[iVar9] = 0x1f;
        (&DAT_005fe247)[iVar9] = 0x1f;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar8 >> 7;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x39;
        break;
      case 0x15:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        bVar4 = sub_563C89();
        bVar5 = sub_563C89();
        (&DAT_005fe246)[iVar9] = (bVar4 & 0xf) - (bVar5 & 0xf);
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
        (&DAT_005fe245)[iVar9] = 0xf;
        (&DAT_005fe247)[iVar9] = 0xf;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar8 >> 7;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 1;
        break;
      case 0x1a:
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x40;
        *(short *)(&DAT_005fe248 + iVar9) = (short)(*param_4 >> 0xc);
        (&DAT_005fe244)[iVar9] = 0;
        (&DAT_005fe250)[iVar6 * 0xd] = 0xa0a0a0;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar11;
        (&DAT_005fe25c)[iVar6 * 0xd] = 0x40;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x138;
        break;
      case 0x1d:
        uVar7 = sub_563C89();
        *piVar1 = (uVar7 & 0xf) - 3;
        uVar7 = sub_563C89();
        *(uint *)(&DAT_005fe238 + iVar9) = (uVar7 & 0xf) - 3;
        uVar7 = sub_563C89();
        (&DAT_005fe246)[iVar9] = 0xfc;
        (&DAT_005fe250)[iVar6 * 0xd] = 0xffffff;
        *(uint *)(&DAT_005fe234 + iVar9) = (uVar7 & 0x5f) + 5;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x78;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 4;
        break;
      case 0x1f:
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        iVar8 = *param_4;
        (&DAT_005fe244)[iVar9] = 0;
        *(short *)(&DAT_005fe248 + iVar9) = (short)(iVar8 >> 0xc);
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        (&DAT_005fe25c)[iVar6 * 0xd] = 0x20;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x13a;
        break;
      case 0x20:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        (&DAT_005fe25c)[iVar6 * 0xd] = 0x20;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 9;
        break;
      case 0x22:
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x400;
        (&DAT_005fe23c)[iVar6 * 0xd] = 0x800;
      case 0x21:
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        iVar8 = param_4[2];
        *(ushort *)(&DAT_005fe24c + iVar9) = *(ushort *)(&DAT_005fe24c + iVar9) | 0x828;
        *(int *)(&DAT_005fe238 + iVar9) = iVar8;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x1e;
        (&DAT_005fe250)[iVar6 * 0xd] = param_5;
        break;
      case 0x23:
      case 0x24:
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x2000;
      case 0xf:
      case 0x10:
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x40;
        (&DAT_005fe246)[iVar9] = 0xfc;
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
        uVar7 = sub_563C89();
        uVar3 = *(undefined4 *)(&DAT_00573b00 + (uVar7 & 7) * 4);
        (&DAT_005fe24c)[iVar9] = (&DAT_005fe24c)[iVar9] | 0x39;
        (&DAT_005fe250)[iVar6 * 0xd] = uVar3;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar11;
        break;
      case 0x25:
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x2000;
      case 0x11:
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        (&DAT_005fe250)[iVar6 * 0xd] = 0x1002060;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        (&DAT_005fe240)[iVar9] = 0;
        if (((param_4[1] == 0) && (*param_4 == 0)) && (param_4[2] == 0)) {
          *(undefined4 *)(&DAT_005fe234 + iVar9) = 0x3c;
        }
        else {
          *piVar1 = *param_4;
          *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
          *(int *)(&DAT_005fe238 + iVar9) = param_4[2];
        }
        (&DAT_005fe24c)[iVar9] = (&DAT_005fe24c)[iVar9] | 0x59;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        (&DAT_005fe245)[iVar9] = 7;
        (&DAT_005fe247)[iVar9] = 7;
        break;
      case 0x26:
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x2000;
      case 0x12:
      case 0x1c:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        iVar8 = param_4[2];
        *(ushort *)(&DAT_005fe24c + iVar9) = *(ushort *)(&DAT_005fe24c + iVar9) | 1;
        *(int *)(&DAT_005fe238 + iVar9) = iVar8;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        break;
      case 0x27:
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x2000;
      case 0x13:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        (&DAT_005fe246)[iVar9] = 0xfc;
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        iVar8 = param_4[2];
        *(ushort *)(&DAT_005fe24c + iVar9) = *(ushort *)(&DAT_005fe24c + iVar9) | 1;
        *(int *)(&DAT_005fe238 + iVar9) = iVar8;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        break;
      case 0x28:
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x2000;
      case 0x16:
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        (&DAT_005fe24c)[iVar9] = (&DAT_005fe24c)[iVar9] | 0x39;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        (&DAT_005fe250)[iVar6 * 0xd] = 0x7090;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar11;
        break;
      case 0x29:
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x2000;
      case 0x17:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        iVar8 = param_4[2];
        (&DAT_005fe24c)[iVar9] = (&DAT_005fe24c)[iVar9] | 0x39;
        *(int *)(&DAT_005fe238 + iVar9) = iVar8;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        break;
      case 0x2a:
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x2000;
      case 0x18:
        (&DAT_005fe250)[iVar6 * 0xd] = 0x808080;
        *(undefined2 *)(&DAT_005fe258 + iVar9) = param_5._0_2_;
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x20;
        (&DAT_005fe246)[iVar9] = 0xfc;
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        iVar8 = param_4[2];
        (&DAT_005fe24c)[iVar9] = (&DAT_005fe24c)[iVar9] | 0x39;
        *(int *)(&DAT_005fe238 + iVar9) = iVar8;
        (&DAT_005fe254)[iVar6 * 0xd] = iVar10;
        break;
      case 0x2b:
        *piVar1 = *param_4;
        *(int *)(&DAT_005fe234 + iVar9) = param_4[1];
        iVar8 = param_4[2];
        *(undefined2 *)(&DAT_005fe24a + iVar9) = 0x1e;
        *(int *)(&DAT_005fe238 + iVar9) = iVar8;
        (&DAT_005fe250)[iVar6 * 0xd] = param_5;
        *(undefined2 *)(&DAT_005fe24c + iVar9) = 0x4828;
      }
    }
    if (*(short *)(&DAT_005fe24a + iVar9) != 0) {
      iVar9 = (int)(0xff / (longlong)(int)*(short *)(&DAT_005fe24a + iVar9));
      if (iVar9 == 0) {
        (&DAT_005fe250)[iVar6 * 0xd] = (&DAT_005fe250)[iVar6 * 0xd] | 0x1000000;
        return;
      }
      (&DAT_005fe250)[iVar6 * 0xd] = (&DAT_005fe250)[iVar6 * 0xd] | iVar9 << 0x18;
    }
  }
  return;
}

