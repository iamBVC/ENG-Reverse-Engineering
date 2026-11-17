/* sub_40C000 @ 0040c000   581 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_40C000(int param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
               int param_6)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_10;
  int local_c;
  
  local_10 = 0;
  if (0 < param_6) {
    local_c = 0;
    do {
      iVar6 = 0;
      if (0 < param_5) {
        do {
          iVar7 = -1;
          do {
            iVar5 = -1;
            do {
              iVar5 = iVar5 + 1;
            } while (iVar5 < 2);
            iVar7 = iVar7 + 1;
          } while (iVar7 < 2);
          uVar1 = __ftol();
          uVar2 = __ftol();
          uVar3 = __ftol();
          uVar4 = __ftol();
          iVar7 = local_c + iVar6;
          iVar6 = iVar6 + 1;
          *(ushort *)(param_1 + iVar7 * 2) =
               uVar1 & 0x7c00 | uVar2 & 0x3e0 | uVar3 & 0x1f | uVar4 & 0x8000;
        } while (iVar6 < param_5);
      }
      local_c = local_c + param_2;
      local_10 = local_10 + 1;
    } while (local_10 < param_6);
  }
  return;
}

