/* sub_5545C0 @ 005545c0   911 bytes */

void sub_5545C0(int param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  int iVar8;
  int iVar9;
  int local_3c;
  int local_38;
  int local_34;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_1c;
  int local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_18 = sub_54BC00(param_1);
  local_1c = sub_54BC00(param_1);
  iVar8 = sub_54BC00(param_1);
  if (iVar8 != 0) {
    local_2c = __ftol();
    local_28 = __ftol();
    iVar9 = __ftol();
    local_24 = iVar9;
    sub_54BC30(param_1);
    lVar1 = (longlong)local_2c * (longlong)*(int *)(param_1 + 0x70);
    lVar2 = (longlong)local_28 * (longlong)*(int *)(param_1 + 0x7c);
    lVar3 = (longlong)iVar9 * (longlong)*(int *)(param_1 + 0x88);
    lVar4 = (longlong)local_2c * (longlong)*(int *)(param_1 + 0x74);
    lVar5 = (longlong)local_28 * (longlong)*(int *)(param_1 + 0x80);
    lVar6 = (longlong)iVar9 * (longlong)*(int *)(param_1 + 0x8c);
    lVar7 = (longlong)local_2c * (longlong)*(int *)(param_1 + 0x78);
    local_8 = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
    lVar7 = (longlong)local_28 * (longlong)*(int *)(param_1 + 0x84);
    local_10 = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
    lVar7 = (longlong)iVar9 * (longlong)*(int *)(param_1 + 0x90);
    local_c = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
    local_3c = ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
               ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
               ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14) +
               *(int *)(param_1 + 0x94);
    local_38 = ((uint)lVar6 >> 0xc | (int)((ulonglong)lVar6 >> 0x20) << 0x14) +
               ((uint)lVar5 >> 0xc | (int)((ulonglong)lVar5 >> 0x20) << 0x14) +
               ((uint)lVar4 >> 0xc | (int)((ulonglong)lVar4 >> 0x20) << 0x14) +
               *(int *)(param_1 + 0x98);
    local_34 = local_10 + local_c + local_8 + *(int *)(param_1 + 0x9c);
    local_14 = iVar9;
    sub_428D80(iVar8,&local_3c,local_18);
    local_2c = __ftol();
    local_28 = __ftol();
    iVar9 = __ftol();
    local_24 = iVar9;
    sub_54BC30(param_1);
    lVar1 = (longlong)local_2c * (longlong)*(int *)(param_1 + 0x70);
    lVar2 = (longlong)local_28 * (longlong)*(int *)(param_1 + 0x7c);
    lVar3 = (longlong)iVar9 * (longlong)*(int *)(param_1 + 0x88);
    lVar4 = (longlong)local_2c * (longlong)*(int *)(param_1 + 0x74);
    lVar5 = (longlong)local_28 * (longlong)*(int *)(param_1 + 0x80);
    lVar6 = (longlong)iVar9 * (longlong)*(int *)(param_1 + 0x8c);
    lVar7 = (longlong)local_2c * (longlong)*(int *)(param_1 + 0x78);
    local_c = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
    lVar7 = (longlong)local_28 * (longlong)*(int *)(param_1 + 0x84);
    local_14 = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
    lVar7 = (longlong)iVar9 * (longlong)*(int *)(param_1 + 0x90);
    local_10 = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
    local_3c = ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
               ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
               ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14) +
               *(int *)(param_1 + 0x94);
    local_34 = local_10 + local_14 + local_c + *(int *)(param_1 + 0x9c);
    local_38 = ((uint)lVar6 >> 0xc | (int)((ulonglong)lVar6 >> 0x20) << 0x14) +
               ((uint)lVar5 >> 0xc | (int)((ulonglong)lVar5 >> 0x20) << 0x14) +
               ((uint)lVar4 >> 0xc | (int)((ulonglong)lVar4 >> 0x20) << 0x14) +
               *(int *)(param_1 + 0x98);
    local_18 = iVar9;
    sub_428D80(iVar8,&local_3c,local_1c);
  }
  return;
}

