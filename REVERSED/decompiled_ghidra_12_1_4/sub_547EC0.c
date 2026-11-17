/* sub_547EC0 @ 00547ec0   1808 bytes */

void sub_547EC0(int param_1,undefined2 *param_2)

{
  byte bVar1;
  undefined2 uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  undefined2 *puVar6;
  short sVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  bool bVar11;
  int local_8;
  int local_4;
  
  puVar6 = param_2;
  iVar5 = param_1;
  iVar4 = *(int *)(param_2 + 6);
  local_4 = *(int *)(iVar4 + 4);
  switch(*param_2) {
  case 0:
    if (*(int *)(iVar4 + 0x10) != 0) {
      sub_547890(*(undefined4 *)(param_1 + 0x3c),*(undefined4 *)(iVar4 + 0x88));
      if ((*(uint *)(iVar4 + 0x3c) & 0x2400) == 0x2400) {
        *puVar6 = 0x13;
        uVar10 = 0;
      }
      else {
        *puVar6 = 7;
        uVar10 = *(undefined4 *)(iVar5 + 0x4c);
      }
      sub_547D70(iVar5 + 0x10,puVar6,uVar10);
      *(undefined4 *)(iVar4 + 0x10) = 3;
      return;
    }
    break;
  case 2:
    local_8 = (int)*(short *)(iVar4 + 0x6a);
    uVar8 = *(uint *)(iVar4 + 0x3c);
    uVar10 = *(undefined4 *)(param_1 + 0x4c);
    if ((uVar8 & 0x2000) == 0) {
      local_8 = (uint)*(ushort *)(DAT_006d9490 + 0x5c) * local_8;
      if ((uVar8 & 8) == 0) {
        *(undefined4 *)(iVar4 + 0x94) = 1;
      }
      else {
        *(undefined4 *)(iVar4 + 0x94) = 0;
      }
    }
    else {
      if ((uVar8 & 0x2400) == 0x2400) {
        uVar3 = *(ushort *)(DAT_006d9490 + 0x5e);
        if (*(int *)(param_1 + 100) != 0) {
          iVar9 = *(int *)(param_1 + 100) + *(int *)(param_1 + 0x68);
          if (iVar9 < 0) {
            iVar9 = 0;
          }
          else if (0x1000 < iVar9) {
            iVar9 = 0x1000;
          }
          *(int *)(param_1 + 0x68) = iVar9;
          if (iVar9 == *(int *)(param_1 + 0x60)) {
            *(undefined4 *)(param_1 + 100) = 0;
          }
        }
        local_8 = (int)(*(int *)(param_1 + 0x68) * (uint)uVar3 * local_8) >> 0xc;
      }
      else {
        local_8 = (uint)*(ushort *)(DAT_006d9490 + 0x62) * local_8;
      }
      *(undefined4 *)(iVar4 + 0x94) = 2;
    }
    if ((*(byte *)(iVar4 + 0x3c) & 8) == 0) {
      sub_547C50(iVar4,&local_8);
    }
    if (((*(uint *)(iVar4 + 0x3c) & 0x2400) != 0x2400) && (local_8 < 1)) {
      if (*(short *)(iVar4 + 0x78) == 0) {
        uVar10 = 0;
        *param_2 = 0x13;
      }
      sub_547D70(iVar5 + 0x10,param_2,uVar10);
      return;
    }
    if (*(int *)(iVar4 + 0x10) == 1) {
      iVar9 = sub_547750(*(undefined4 *)(iVar5 + 0x3c),iVar4 + 0x80,*(undefined2 *)(iVar4 + 0x72),
                         *(undefined4 *)(local_4 + 0x14));
      if (iVar9 == 0) {
        if (*(short *)(iVar4 + 0x78) == 0) {
          uVar10 = 0;
          *param_2 = 0x13;
        }
        sub_547D70(iVar5 + 0x10,param_2,uVar10);
        return;
      }
    }
    else {
      sub_547DF0(iVar5 + 0x10,iVar4);
    }
    *(undefined4 *)(iVar4 + 0x10) = 2;
    if (((*(byte *)(iVar4 + 0x3c) & 0x10) != 0) && ((*(ushort *)(iVar4 + 0x6c) & 0xffe0) != 0)) {
      sVar7 = *(short *)(iVar4 + 0x6c);
      iVar9 = sub_563C89();
      if (iVar9 % ((int)sVar7 >> 5) + (int)sVar7 < 0) {
        sVar7 = 0;
      }
      else {
        sVar7 = *(short *)(iVar4 + 0x6c);
        iVar9 = sub_563C89();
        if (iVar9 % ((int)sVar7 >> 5) + (int)sVar7 < 0x4000) {
          sVar7 = *(short *)(iVar4 + 0x6c);
          iVar9 = sub_563C89();
          sVar7 = (short)(iVar9 % ((int)sVar7 >> 5)) + sVar7;
        }
        else {
          sVar7 = 0x3fff;
        }
      }
      *(short *)(iVar4 + 0x6c) = sVar7;
      uVar8 = sub_563C89();
      if ((int)((uVar8 & 0x7f) + local_8) < 0) {
        local_8 = 0;
      }
      else {
        uVar8 = sub_563C89();
        if ((int)((uVar8 & 0x7f) + local_8) < 0x4000) {
          uVar8 = sub_563C89();
          local_8 = local_8 + (uVar8 & 0x7f);
        }
        else {
          local_8 = 0x3fff;
        }
      }
    }
    sub_547A20(iVar4,iVar4 + 100,local_8,0);
    sVar7 = *(short *)(iVar4 + 0x70);
    if (sVar7 == 0) {
      local_8 = (int)*(short *)(iVar4 + 0x6c);
    }
    else {
      local_8 = (int)(short)(((short)((sVar7 * 0x14) / 0x32) + (sVar7 >> 0xf)) -
                            (short)((longlong)(sVar7 * 0x14) * 0x51eb851f >> 0x3f)) *
                ((int)*(short *)(iVar4 + 0x6c) >> 8) + (int)*(short *)(iVar4 + 0x6c);
    }
    sub_5479B0(*(undefined4 *)(iVar4 + 0x88),*(uint *)(iVar4 + 0x3c) & 1);
    sub_547900(*(undefined4 *)(iVar4 + 0x88),local_8);
    sub_5478C0(*(undefined4 *)(iVar4 + 0x88),iVar4 + 100);
    sub_547950(*(undefined4 *)(iVar4 + 0x88),*(undefined4 *)(local_4 + 0x14));
    sub_547840(*(undefined4 *)(iVar5 + 0x3c),*(undefined4 *)(iVar4 + 0x88));
    puVar6 = param_2;
    iVar9 = (*(uint *)(iVar4 + 0x54) >> 4) * 0x1c;
    *(int *)(iVar4 + 0x1c) = iVar9;
    local_8 = local_8 * 0x1b9 >> 10;
    if (local_8 != 0) {
      *(int *)(iVar4 + 0x1c) = (iVar9 / local_8) * *(int *)(iVar5 + 0x4c);
    }
    if ((*(byte *)(iVar4 + 0x3c) & 2) != 0) {
      *param_2 = 4;
      sub_547D70(iVar5 + 0x10,param_2,*(undefined4 *)(iVar4 + 0x1c));
    }
    if ((*(byte *)(iVar4 + 0x3c) & 0x28) == 0) {
      *puVar6 = 6;
      sub_547D70(iVar5 + 0x10,puVar6,*(undefined4 *)(iVar5 + 0x4c));
    }
    if (*(short *)(iVar4 + 0x78) == 0) {
      *puVar6 = 7;
      sub_547D70(iVar5 + 0x10,puVar6,*(undefined4 *)(iVar4 + 0x1c));
    }
    *(int *)(iVar4 + 0x1c) = *(int *)(iVar4 + 0x1c) + *(int *)(iVar5 + 0x54);
    return;
  case 4:
    sVar7 = 0;
    if (param_2[2] != 0) {
      sVar7 = (short)((*(short *)(iVar4 + 0x70) * 0xb) / 0x32) *
              (short)((uint)*(undefined4 *)(param_2 + 2) >> 8);
    }
    if (*(int *)(iVar4 + 0x10) != 0) {
      sub_547900(*(undefined4 *)(iVar4 + 0x88),
                 CONCAT22((short)((uint)*(int *)(iVar4 + 0x10) >> 0x10),param_2[2] + sVar7));
    }
    *(undefined2 *)(iVar4 + 0x6e) = *(undefined2 *)(iVar4 + 0x6c);
    uVar2 = puVar6[2];
    *(short *)(iVar4 + 100) = *(short *)(iVar4 + 100) + 1;
    *(short *)(iVar4 + 0x66) = *(short *)(iVar4 + 0x66) + 1;
    *(undefined2 *)(iVar4 + 0x6c) = uVar2;
    return;
  case 6:
    sVar7 = *(short *)(iVar4 + 0x6a);
    if (local_4 == 0) {
      return;
    }
    if ((*(uint *)(iVar4 + 0x3c) & 0x2000) == 0) {
      uVar3 = *(ushort *)(DAT_006d9490 + 0x5c);
    }
    else {
      if ((*(uint *)(iVar4 + 0x3c) & 0x2400) == 0x2400) {
        uVar3 = *(ushort *)(DAT_006d9490 + 0x5e);
        if (*(int *)(param_1 + 100) != 0) {
          iVar9 = *(int *)(param_1 + 100) + *(int *)(param_1 + 0x68);
          if (iVar9 < 0) {
            iVar9 = 0;
          }
          else if (0x1000 < iVar9) {
            iVar9 = 0x1000;
          }
          *(int *)(param_1 + 0x68) = iVar9;
          if (iVar9 == *(int *)(param_1 + 0x60)) {
            *(undefined4 *)(param_1 + 100) = 0;
          }
        }
        param_2 = (undefined2 *)((int)(*(int *)(param_1 + 0x68) * (uint)uVar3 * (int)sVar7) >> 0xc);
        goto LAB_005483d0;
      }
      uVar3 = *(ushort *)(DAT_006d9490 + 0x62);
    }
    param_2 = (undefined2 *)((uint)uVar3 * (int)sVar7);
LAB_005483d0:
    sub_547C50(iVar4,&param_2);
    if ((int)param_2 < 1) {
      param_2 = (undefined2 *)0x0;
    }
    sVar7 = sub_547A20(iVar4,&param_1,param_2,1);
    if (sVar7 != 0) {
      *(undefined2 *)(iVar4 + 0x66) = param_1._2_2_;
      *(undefined2 *)(iVar4 + 100) = (undefined2)param_1;
      if (*(int *)(iVar4 + 0x10) != 0) {
        sub_5478C0(*(undefined4 *)(iVar4 + 0x88),(undefined2 *)(iVar4 + 100));
      }
    }
    if ((((param_2 == (undefined2 *)0x0) && ((*(uint *)(iVar4 + 0x3c) & 0x2400) != 0x2400)) &&
        (*(short *)(iVar4 + 0x66) == 0)) && (*(short *)(iVar4 + 100) == 0)) {
      if (*(short *)(iVar4 + 0x78) == 0) {
        *puVar6 = 0;
      }
      else {
        if (*(int *)(iVar4 + 0x10) != 0) {
          sub_547890(*(undefined4 *)(iVar5 + 0x3c),*(undefined4 *)(iVar4 + 0x88));
          sub_547800(*(undefined4 *)(iVar5 + 0x3c),iVar4 + 0x80);
          *(undefined4 *)(iVar4 + 0x10) = 1;
        }
        *puVar6 = 2;
      }
    }
    sub_547D70(iVar5 + 0x10,puVar6,*(undefined4 *)(iVar5 + 0x4c));
    return;
  case 7:
    uVar10 = *(undefined4 *)(param_1 + 0x4c);
    bVar11 = DAT_00584640 == 0;
    bVar1 = *(byte *)(iVar4 + 0x3c);
    if ((*(int *)(iVar4 + 0x88) != 0) &&
       (sVar7 = sub_547990(*(undefined4 *)(param_1 + 0x3c),*(int *)(iVar4 + 0x88)), sVar7 != 0)) {
      sub_547D70(iVar5 + 0x10,param_2,uVar10);
      return;
    }
    if ((bVar1 & 8) != 0 || bVar11) {
      uVar10 = 0;
      *param_2 = 0x13;
      *(undefined4 *)(iVar4 + 0x10) = 3;
    }
    sub_547D70(iVar5 + 0x10,param_2,uVar10);
    return;
  case 0x13:
    sub_547DF0(param_1 + 0x10,iVar4);
    if (1 < *(int *)(iVar4 + 0x10)) {
      sub_547800(*(undefined4 *)(iVar5 + 0x3c),iVar4 + 0x80);
    }
    if (DAT_006d94a4 == iVar4) {
      DAT_006d94a4 = 0;
    }
    if (((*(uint *)(iVar4 + 0x3c) & 0x2400) == 0x2000) && (*(int *)(iVar5 + 0x68) != 0x1000)) {
      *(undefined4 *)(iVar5 + 0x60) = 0x1000;
      *(undefined4 *)(iVar5 + 100) = 0x100;
    }
    if (DAT_006d94b4 == *(int *)(iVar4 + 0x14)) {
      DAT_006d94b4 = -1;
      DAT_006d94a0 = 0;
      if (DAT_006d91d8 != (LPCVOID)0x0) {
        UnmapViewOfFile(DAT_006d91d8);
        DAT_006d91d8 = (LPCVOID)0x0;
      }
    }
    *(undefined4 *)(iVar4 + 0x10) = 0;
    *(undefined4 *)(iVar4 + 4) = 0;
    *(undefined4 *)(iVar4 + 0x20) = 0;
  }
  return;
}

