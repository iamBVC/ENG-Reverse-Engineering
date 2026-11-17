/* sub_42BF40 @ 0042bf40   575 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

byte sub_42BF40(int param_1,int param_2)

{
  int *piVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  byte local_29;
  undefined4 local_28;
  undefined4 local_18;
  float local_14 [3];
  float local_8;
  float local_4;
  
  local_29 = 1;
  uVar3 = __ftol();
  uVar3 = ((int)uVar3 < 0) - 1 & uVar3;
  uVar4 = __ftol();
  uVar5 = *(int *)(param_1 + 0x18) - 1;
  if (uVar5 < uVar4) {
    uVar4 = uVar5;
  }
  uVar5 = __ftol();
  local_28 = __ftol();
  uVar6 = *(int *)(param_1 + 0x14) - 1;
  if (uVar6 < local_28) {
    local_28 = uVar6;
  }
  for (; uVar6 = ((int)uVar5 < 0) - 1 & uVar5, (int)uVar3 <= (int)uVar4; uVar3 = uVar3 + 1) {
    for (; (int)uVar6 <= (int)local_28; uVar6 = uVar6 + 1) {
      for (piVar1 = *(int **)(*(int *)(param_1 + 0x40) +
                             (*(int *)(param_1 + 0x14) * uVar3 + uVar6) * 4); piVar1 != (int *)0x0;
          piVar1 = (int *)piVar1[1]) {
        if ((_DAT_0058642c &
            1 << ((byte)*(undefined4 *)
                         (*(int *)(param_1 + 0x48) + (*(int *)(param_1 + 0x14) * uVar3 + uVar6) * 4)
                 & 0x1f)) != 0) {
          iVar7 = *piVar1 * 0x20 + *(int *)(param_1 + 0x3c);
          local_14[2] = (float)*(int *)(iVar7 + 0x10) * (float)_DAT_0056e020;
          local_8 = (float)*(int *)(iVar7 + 0x14) * (float)_DAT_0056e020;
          local_18 = 0;
          local_4 = -((float)*(int *)(iVar7 + 0x18) * (float)_DAT_0056e020);
          local_14[1] = 0.0;
          local_14[0] = (float)*(int *)(iVar7 + 4) * (float)_DAT_0056e018;
          if (DAT_005865cc == 1) {
            bVar2 = sub_41FB30(param_2 + *(int *)(*(int *)(param_1 + 0x4c) + *piVar1 * 4) * 0x84,
                               &local_18,0x3f800000,0x3f800000,0x3f800000,0x3f800000,0,0,0,
                               0xffffffff,0xffffffff,0xffffffff,1,0);
          }
          else {
            iVar7 = *(int *)(param_1 + 0x58);
            iVar8 = *piVar1 * 4;
            uVar9 = *(uint *)(iVar7 + iVar8);
            if ((*(byte *)(uVar9 + 3) < 2) || (DAT_005865d4 != 1)) {
              uVar9 = -(uint)(iVar7 != 0) & uVar9;
            }
            else if (iVar7 == 0) {
              uVar9 = 0;
            }
            else {
              uVar9 = uVar9 + (uint)*(ushort *)
                                     (param_2 + 0x6c +
                                     *(int *)(*(int *)(param_1 + 0x4c) + iVar8) * 0x84) * 4;
            }
            bVar2 = sub_556510(param_2 + *(int *)(*(int *)(param_1 + 0x4c) + iVar8) * 0x84,
                               local_14 + 2,local_14,uVar9);
          }
          local_29 = local_29 & bVar2;
        }
      }
    }
  }
  return local_29;
}

