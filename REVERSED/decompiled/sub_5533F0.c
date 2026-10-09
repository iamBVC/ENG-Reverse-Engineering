/* sub_5533F0 @ 005533f0   489 bytes */

void sub_5533F0(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined1 local_68 [16];
  int local_58;
  int local_54;
  int local_50;
  undefined1 local_48 [20];
  undefined4 local_34;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_1c;
  int local_18;
  int local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  piVar1 = param_1;
  local_1c = sub_54BC00(param_1);
  sub_553170(piVar1,local_48,&param_1);
  local_34 = 0;
  *piVar1 = *piVar1 + 4;
  local_2c = __ftol();
  iVar2 = __ftol();
  local_28 = iVar2;
  iVar3 = __ftol();
  local_24 = iVar3;
  sub_54BC30(piVar1);
  local_8 = (uint)((longlong)local_2c * (longlong)piVar1[0x1e]) >> 0xc |
            (int)((ulonglong)((longlong)local_2c * (longlong)piVar1[0x1e]) >> 0x20) << 0x14;
  local_10 = (uint)((longlong)iVar2 * (longlong)piVar1[0x21]) >> 0xc |
             (int)((ulonglong)((longlong)iVar2 * (longlong)piVar1[0x21]) >> 0x20) << 0x14;
  local_18 = piVar1[0x24];
  local_c = (uint)((longlong)iVar3 * (longlong)local_18) >> 0xc |
            (int)((ulonglong)((longlong)iVar3 * (longlong)local_18) >> 0x20) << 0x14;
  local_58 = ((uint)((longlong)iVar3 * (longlong)piVar1[0x22]) >> 0xc |
             (int)((ulonglong)((longlong)iVar3 * (longlong)piVar1[0x22]) >> 0x20) << 0x14) +
             ((uint)((longlong)iVar2 * (longlong)piVar1[0x1f]) >> 0xc |
             (int)((ulonglong)((longlong)iVar2 * (longlong)piVar1[0x1f]) >> 0x20) << 0x14) +
             ((uint)((longlong)local_2c * (longlong)piVar1[0x1c]) >> 0xc |
             (int)((ulonglong)((longlong)local_2c * (longlong)piVar1[0x1c]) >> 0x20) << 0x14) +
             piVar1[0x25];
  local_54 = ((uint)((longlong)iVar3 * (longlong)piVar1[0x23]) >> 0xc |
             (int)((ulonglong)((longlong)iVar3 * (longlong)piVar1[0x23]) >> 0x20) << 0x14) +
             ((uint)((longlong)iVar2 * (longlong)piVar1[0x20]) >> 0xc |
             (int)((ulonglong)((longlong)iVar2 * (longlong)piVar1[0x20]) >> 0x20) << 0x14) +
             ((uint)((longlong)local_2c * (longlong)piVar1[0x1d]) >> 0xc |
             (int)((ulonglong)((longlong)local_2c * (longlong)piVar1[0x1d]) >> 0x20) << 0x14) +
             piVar1[0x26];
  local_50 = local_10 + local_c + local_8 + piVar1[0x27];
  local_14 = iVar3;
  sub_54BFC0(local_48,local_68,local_1c,param_1,1);
  return;
}

