/* sub_403020 @ 00403020   1698 bytes */

void sub_403020(int param_1,undefined4 param_2,undefined4 param_3)

{
  ushort *puVar1;
  byte *pbVar2;
  undefined2 uVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  int local_88 [3];
  undefined4 local_7c;
  int local_74;
  int local_70;
  undefined4 local_6c;
  int local_68;
  undefined4 local_64;
  int local_5c;
  int local_54;
  int local_50;
  int local_4c;
  undefined4 local_48;
  int local_44 [4];
  int local_34;
  int local_30;
  int local_2c;
  undefined4 local_28;
  int local_1c;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  undefined4 local_4;
  
  if ((*(uint *)(param_1 + 0xe8) & 0x200000) == 0) {
    DAT_0057dd98 = 0x400;
  }
  else {
    DAT_0057dd98 = *(int *)(*(int *)(param_1 + 0xc0) + 0x18) >> 1;
  }
  uVar5 = *(uint *)(param_1 + 0xe8);
  piVar6 = local_88;
  for (iVar4 = 0x11; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  uVar5 = uVar5 & 0x200000;
  local_88[0] = -0x10000;
  local_88[1] = 1000000;
  local_88[2] = 0;
  local_7c = 0xffffffff;
  local_74 = -1;
  local_70 = 10000000;
  local_6c = 0xfff0bdc0;
  local_68 = 0;
  local_64 = 0xffffffff;
  local_5c = -1;
  if (uVar5 != 0) {
    local_54 = 0;
    local_50 = -1;
    local_4c = 10000000;
    local_48 = 0xff676980;
  }
  piVar6 = local_44;
  for (iVar4 = 0x11; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  local_44[0] = -0x10000;
  local_44[1] = 1000000;
  local_34 = 0;
  local_30 = -1;
  local_2c = 10000000;
  local_28 = 0xfff0bdc0;
  local_1c = 0;
  local_18 = -1;
  if (uVar5 != 0) {
    local_14 = 0;
    local_c = -1;
    local_8 = 10000000;
    local_4 = 0xff676980;
  }
  sub_4036D0(param_1,param_2,param_3,local_88);
  if ((*(uint *)(param_1 + 0xe8) & 0x400) == 0) {
    sub_403AD0(param_1,param_2,param_3,local_44);
  }
  if ((*(uint *)(param_1 + 0xe8) & 0x200000) != 0) {
    puVar1 = (ushort *)(*(int *)(param_1 + 0xc0) + 6);
    *puVar1 = *puVar1 & 0xffef;
    *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x30) = 0xffff;
    *(undefined4 *)(*(int *)(param_1 + 0xc0) + 0x28) = 0x3e8000;
    if ((local_50 != -1) || (local_c != -1)) {
      if (local_4c < local_8) {
        *(int *)(*(int *)(param_1 + 0xc0) + 0x28) = local_4c;
        if (local_4c <= *(int *)(*(int *)(param_1 + 0xc0) + 0x18) + *(int *)(param_1 + 0x34)) {
          pbVar2 = (byte *)(*(int *)(param_1 + 0xc0) + 6);
          *pbVar2 = *pbVar2 | 0x10;
          if ((*(uint *)(param_1 + 0xe8) & 0x40200) != 0) {
            *(ushort *)(*(int *)(param_1 + 0xc0) + 0x30) =
                 (ushort)*(byte *)(*(int *)(local_54 + 0x80) + 1 + local_50 * 0x20);
          }
          *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x10) = (undefined2)local_54;
          iVar4 = *(int *)(param_1 + 0xc0);
          uVar3 = (undefined2)local_50;
LAB_004032a6:
          *(undefined2 *)(iVar4 + 0x12) = uVar3;
        }
      }
      else {
        *(int *)(*(int *)(param_1 + 0xc0) + 0x28) = local_8;
        if (local_8 <= *(int *)(*(int *)(param_1 + 0xc0) + 0x18) + *(int *)(param_1 + 0x34)) {
          pbVar2 = (byte *)(*(int *)(param_1 + 0xc0) + 6);
          *pbVar2 = *pbVar2 | 0x10;
          if ((*(uint *)(param_1 + 0xe8) & 0x40200) != 0) {
            *(ushort *)(*(int *)(param_1 + 0xc0) + 0x30) =
                 (ushort)*(byte *)(*(int *)(*(int *)(local_14 + 0x10) + 0x80) + 1 + local_c * 0x20);
          }
          *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x10) = (undefined2)local_14;
          iVar4 = *(int *)(param_1 + 0xc0);
          uVar3 = (undefined2)local_c;
          goto LAB_004032a6;
        }
      }
    }
  }
  if ((local_74 == -1) && (local_30 == -1)) {
    if (((local_5c == -1) && (local_18 == -1)) || ((*(uint *)(param_1 + 0xe8) & 0x40200) != 0)) {
      if ((*(uint *)(param_1 + 0xec) & 0x100) == 0) {
        iVar4 = *(int *)(param_1 + 0xc0);
        if ((*(ushort *)(iVar4 + 6) & 4) == 0) {
          if ((*(uint *)(param_1 + 0xe8) & 0x40200) == 0) {
            *(ushort *)(iVar4 + 6) = *(ushort *)(iVar4 + 6) & 0xfffc;
            *(undefined2 *)(*(int *)(param_1 + 0xc0) + 4) = 0xffff;
            **(undefined4 **)(param_1 + 0xc0) = 0xffff0000;
          }
          else {
            fpatan((float10)(*(int *)(param_1 + 0x50) - *(int *)(param_1 + 0x30)),
                   (float10)(*(int *)(param_1 + 0x58) - *(int *)(param_1 + 0x38)));
            uVar3 = __ftol();
            *(undefined2 *)(iVar4 + 0x2c) = uVar3;
            *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x58);
            *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x50);
            puVar1 = (ushort *)(*(int *)(param_1 + 0xc0) + 6);
            *puVar1 = *puVar1 & 0xfffd;
            pbVar2 = (byte *)(*(int *)(param_1 + 0xc0) + 6);
            *pbVar2 = *pbVar2 | 5;
          }
        }
      }
      goto LAB_0040353e;
    }
    if (local_70 < local_2c) {
      *(ushort *)(*(int *)(param_1 + 0xc0) + 4) =
           (ushort)*(byte *)(*(int *)(local_68 + 0x80) + 1 + local_5c * 0x20);
      **(int **)(param_1 + 0xc0) = local_70;
      pbVar2 = (byte *)(*(int *)(param_1 + 0xc0) + 6);
      *pbVar2 = *pbVar2 | 1;
      puVar1 = (ushort *)(*(int *)(param_1 + 0xc0) + 6);
      *puVar1 = *puVar1 & 0xfffd;
      *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0xc) = (undefined2)local_64;
      *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0xe) = (undefined2)local_5c;
      goto LAB_0040353e;
    }
    *(ushort *)(*(int *)(param_1 + 0xc0) + 4) =
         (ushort)*(byte *)(*(int *)(*(int *)(local_1c + 0x10) + 0x80) + 1 + local_18 * 0x20);
    **(int **)(param_1 + 0xc0) = local_2c;
    *(short *)(*(int *)(param_1 + 0xc0) + 8) =
         (short)((ulonglong)(uint)(local_1c - DAT_006d9dc0) * 0xc0c0c0c1 >> 0x28);
    iVar4 = *(int *)(param_1 + 0xc0);
    uVar3 = (undefined2)local_18;
  }
  else {
    if ((local_44[0] < local_88[0]) || (local_34 == 0)) {
      *(ushort *)(*(int *)(param_1 + 0xc0) + 4) =
           (ushort)*(byte *)(*(int *)(local_88[2] + 0x80) + 1 + local_74 * 0x20);
      **(int **)(param_1 + 0xc0) = local_88[0];
      puVar1 = (ushort *)(*(int *)(param_1 + 0xc0) + 6);
      *puVar1 = *puVar1 & 0xfffd;
      pbVar2 = (byte *)(*(int *)(param_1 + 0xc0) + 6);
      *pbVar2 = *pbVar2 | 1;
      *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0xc) = (undefined2)local_7c;
      *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0xe) = (undefined2)local_74;
      goto LAB_0040353e;
    }
    *(ushort *)(*(int *)(param_1 + 0xc0) + 4) =
         (ushort)*(byte *)(*(int *)(*(int *)(local_34 + 0x10) + 0x80) + 1 + local_30 * 0x20);
    **(int **)(param_1 + 0xc0) = local_44[0];
    *(short *)(*(int *)(param_1 + 0xc0) + 8) =
         (short)((ulonglong)(uint)(local_34 - DAT_006d9dc0) * 0xc0c0c0c1 >> 0x28);
    iVar4 = *(int *)(param_1 + 0xc0);
    uVar3 = (undefined2)local_30;
  }
  *(undefined2 *)(iVar4 + 10) = uVar3;
  puVar1 = (ushort *)(*(int *)(param_1 + 0xc0) + 6);
  *puVar1 = *puVar1 & 0xfffe;
  pbVar2 = (byte *)(*(int *)(param_1 + 0xc0) + 6);
  *pbVar2 = *pbVar2 | 2;
LAB_0040353e:
  if (*(short *)(*(int *)(param_1 + 0xc0) + 4) == 0x1e) {
    *(undefined2 *)(*(int *)(param_1 + 0xc0) + 4) = 0xffff;
    **(undefined4 **)(param_1 + 0xc0) = 0xffff0000;
    puVar1 = (ushort *)(*(int *)(param_1 + 0xc0) + 6);
    *puVar1 = *puVar1 & 0xfffc;
  }
  if (local_74 == -1) {
    if ((local_5c == -1) || ((*(uint *)(param_1 + 0xe8) & 0x40200) != 0)) {
      *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x24) = 0xffff;
      *(undefined4 *)(*(int *)(param_1 + 0xc0) + 0x1c) = 0xffff0000;
    }
    else {
      *(ushort *)(*(int *)(param_1 + 0xc0) + 0x24) =
           (ushort)*(byte *)(*(int *)(local_68 + 0x80) + 1 + local_5c * 0x20);
      *(int *)(*(int *)(param_1 + 0xc0) + 0x1c) = local_70;
    }
  }
  else {
    *(ushort *)(*(int *)(param_1 + 0xc0) + 0x24) =
         (ushort)*(byte *)(*(int *)(local_88[2] + 0x80) + 1 + local_74 * 0x20);
    *(int *)(*(int *)(param_1 + 0xc0) + 0x1c) = local_88[0];
  }
  if (*(short *)(*(int *)(param_1 + 0xc0) + 0x24) == 0x1e) {
    *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x24) = 0xffff;
    *(undefined4 *)(*(int *)(param_1 + 0xc0) + 0x1c) = 0xffff0000;
  }
  if (local_30 == -1) {
    if ((local_18 == -1) || ((*(uint *)(param_1 + 0xe8) & 0x40200) != 0)) {
      *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x26) = 0xffff;
      *(undefined4 *)(*(int *)(param_1 + 0xc0) + 0x20) = 0xffff0000;
    }
    else {
      *(ushort *)(*(int *)(param_1 + 0xc0) + 0x26) =
           (ushort)*(byte *)(*(int *)(*(int *)(local_1c + 0x10) + 0x80) + 1 + local_18 * 0x20);
      *(int *)(*(int *)(param_1 + 0xc0) + 0x20) = local_2c;
    }
  }
  else {
    *(ushort *)(*(int *)(param_1 + 0xc0) + 0x26) =
         (ushort)*(byte *)(*(int *)(*(int *)(local_34 + 0x10) + 0x80) + 1 + local_30 * 0x20);
    *(int *)(*(int *)(param_1 + 0xc0) + 0x20) = local_44[0];
  }
  if (*(short *)(*(int *)(param_1 + 0xc0) + 0x26) == 0x1e) {
    *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x26) = 0xffff;
    *(undefined4 *)(*(int *)(param_1 + 0xc0) + 0x20) = 0xffff0000;
  }
  return;
}

