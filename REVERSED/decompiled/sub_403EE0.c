/* sub_403EE0 @ 00403ee0   864 bytes */

void sub_403EE0(int param_1,undefined4 param_2,undefined4 param_3)

{
  byte *pbVar1;
  uint uVar2;
  undefined2 uVar3;
  int iVar4;
  int local_78;
  int local_70;
  undefined1 local_68 [4];
  int local_64;
  int local_5c;
  undefined4 local_58;
  int local_48;
  undefined4 local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34 [2];
  undefined2 *local_2c;
  int local_28;
  undefined4 local_24;
  int local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  int local_4;
  
  local_24 = 10000000;
  local_58 = 10000000;
  local_34[0] = 0;
  local_2c = (undefined2 *)0x0;
  local_28 = -1;
  local_4 = 0;
  local_8 = 0;
  local_c = 0;
  local_10 = 0;
  local_14 = 0;
  local_64 = 0;
  local_5c = -1;
  local_38 = 0;
  local_3c = 0;
  local_40 = 0;
  local_44 = 0;
  local_48 = 0;
  local_78 = 0;
  local_70 = 0;
  sub_404240(param_1,param_2,param_3,local_34);
  if ((*(uint *)(param_1 + 0xe8) & 0x200) == 0) {
    sub_4046E0(param_1,param_2,param_3,local_68);
  }
  if ((local_8 == 0) || (local_4 == 0)) {
    iVar4 = 0;
  }
  else {
    local_78 = local_14;
    local_70 = local_c;
    iVar4 = local_8;
    if ((local_3c == 0) || (local_38 == 0)) {
      *(ushort *)(*(int *)(param_1 + 0xc0) + 0x3a) =
           (ushort)*(byte *)(*(int *)(local_34[0] + 0x80) + 1 + local_28 * 0x20);
      *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x3c) = *local_2c;
      *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x3e) = (undefined2)local_28;
      pbVar1 = (byte *)(*(int *)(param_1 + 0xc0) + 6);
      *pbVar1 = *pbVar1 | 4;
    }
  }
  if ((local_3c != 0) && (local_38 != 0)) {
    local_78 = local_78 + local_48;
    local_70 = local_70 + local_40;
    iVar4 = iVar4 + local_3c;
    *(ushort *)(*(int *)(param_1 + 0xc0) + 0x3a) =
         (ushort)*(byte *)(*(int *)(*(int *)(local_64 + 0x10) + 0x80) + 1 + local_5c * 0x20);
    *(short *)(*(int *)(param_1 + 0xc0) + 0x3c) =
         (short)((ulonglong)(uint)(local_64 - DAT_006d9dc0) * 0xc0c0c0c1 >> 0x28);
    *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x3e) = (undefined2)local_5c;
    pbVar1 = (byte *)(*(int *)(param_1 + 0xc0) + 6);
    *pbVar1 = *pbVar1 | 8;
    if ((*(uint *)(param_1 + 0xe8) & 0x800) != 0) {
      if ((*(uint *)(local_64 + 0xe8) & 0x34000) != 0) {
        if ((*(uint *)(local_64 + 0xe8) & 0x100000) != 0) {
          *(undefined2 *)(local_64 + 0xd4) = 0;
          *(undefined2 *)(param_1 + 0xd4) = 0;
        }
        *(undefined1 *)(local_64 + 0x130) = 0;
        *(undefined1 *)(param_1 + 0x130) = 0;
        uVar2 = *(uint *)(local_64 + 0xe8);
        if ((uVar2 & 0x4000) == 0) {
          if ((uVar2 & 0x10000) != 0) {
            if ((*(uint *)(param_1 + 0xe8) & 0x10000000) == 0) {
              *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 0x4000000;
              *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(local_64 + 0x140);
            }
            else {
              *(uint *)(local_64 + 0xe8) = uVar2 | 0x4000000;
              *(undefined4 *)(local_64 + 0x144) = *(undefined4 *)(DAT_006d9e1c + 0x140);
            }
          }
          if ((*(uint *)(local_64 + 0xe8) & 0x20000) != 0) {
            *(uint *)(local_64 + 0xe8) = *(uint *)(local_64 + 0xe8) | 0x4000000;
            *(undefined4 *)(local_64 + 0x144) = *(undefined4 *)(param_1 + 0x140);
          }
        }
        else {
          *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 0x4000000;
          *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(local_64 + 0x140);
          *(uint *)(local_64 + 0xe8) = *(uint *)(local_64 + 0xe8) | 0x4000000;
          *(undefined4 *)(local_64 + 0x144) = *(undefined4 *)(DAT_006d9e1c + 0x140);
        }
      }
    }
  }
  if (iVar4 != 0) {
    fpatan((float10)local_78,(float10)local_70);
    uVar3 = __ftol();
    *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x2c) = uVar3;
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + local_78 / iVar4;
    *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + local_70 / iVar4;
    return;
  }
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x2c) = 0xffff;
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x3a) = 0xffff;
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x3c) = 0xffff;
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x3e) = 0xffff;
  return;
}

