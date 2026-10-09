/* sub_568A4A @ 00568a4a   391 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong sub_568A4A(char *param_1)

{
  uint uVar1;
  byte bVar2;
  ulonglong uVar3;
  undefined4 *puVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  longlong lVar9;
  longlong lVar10;
  uint local_8;
  
  puVar4 = (undefined4 *)param_1;
  uVar1 = *(uint *)((int)param_1 + 0x10);
  if (*(int *)((int)param_1 + 4) < 0) {
    *(undefined4 *)((int)param_1 + 4) = 0;
  }
  lVar9 = sub_56BBB3(uVar1,0,0,1);
  if ((lVar9 < 0x100000000) && (lVar9 < 0)) {
LAB_00568aec:
    uVar3 = 0xffffffffffffffff;
  }
  else {
    if ((*(ushort *)((int)param_1 + 0xc) & 0x108) == 0) {
      return lVar9 - *(int *)((int)param_1 + 4);
    }
    pcVar5 = *(char **)param_1;
    pcVar6 = *(char **)((int)param_1 + 8);
    local_8 = (int)pcVar5 - (int)pcVar6;
    if ((*(uint *)((int)param_1 + 0xc) & 3) == 0) {
      if ((*(uint *)((int)param_1 + 0xc) & 0x80) == 0) {
        _DAT_006da364 = 0x16;
        goto LAB_00568aec;
      }
    }
    else {
      pcVar7 = pcVar6;
      if ((*(byte *)((&DAT_006da7e0)[(int)uVar1 >> 5] + 4 + (uVar1 & 0x1f) * 8) & 0x80) != 0) {
        for (; pcVar7 < pcVar5; pcVar7 = pcVar7 + 1) {
          if (*pcVar7 == '\n') {
            local_8 = local_8 + 1;
          }
        }
      }
    }
    if (lVar9 == 0) {
      uVar3 = (ulonglong)local_8;
    }
    else {
      if ((*(byte *)((int)param_1 + 0xc) & 1) != 0) {
        if (*(int *)((int)param_1 + 4) == 0) {
          local_8 = 0;
        }
        else {
          pcVar5 = pcVar5 + (*(int *)((int)param_1 + 4) - (int)pcVar6);
          iVar8 = (uVar1 & 0x1f) * 8;
          if ((*(byte *)(iVar8 + 4 + (&DAT_006da7e0)[(int)uVar1 >> 5]) & 0x80) != 0) {
            lVar10 = sub_56BBB3(uVar1,0,0,2);
            if (lVar10 == lVar9) {
              pcVar6 = *(char **)((int)param_1 + 8);
              pcVar7 = pcVar6 + (int)pcVar5;
              param_1 = pcVar5;
              for (; pcVar6 < pcVar7; pcVar6 = pcVar6 + 1) {
                if (*pcVar6 == '\n') {
                  param_1 = param_1 + 1;
                }
              }
              bVar2 = *(byte *)((int)puVar4 + 0xd) & 0x20;
            }
            else {
              sub_56BBB3(uVar1,lVar9,0);
              pcVar6 = (char *)0x200;
              if ((((char *)0x200 < pcVar5) || ((*(uint *)((int)param_1 + 0xc) & 8) == 0)) ||
                 ((*(uint *)((int)param_1 + 0xc) & 0x400) != 0)) {
                pcVar6 = *(char **)((int)param_1 + 0x18);
              }
              bVar2 = *(byte *)(iVar8 + 4 + (&DAT_006da7e0)[(int)uVar1 >> 5]) & 4;
              param_1 = pcVar6;
            }
            pcVar5 = param_1;
            if (bVar2 != 0) {
              pcVar5 = param_1 + 1;
            }
          }
          param_1 = pcVar5;
          lVar9 = CONCAT44((int)((ulonglong)lVar9 >> 0x20) - (uint)((char *)lVar9 < param_1),
                           (int)(char *)lVar9 - (int)param_1);
        }
      }
      uVar3 = lVar9 + (ulonglong)local_8;
    }
  }
  return uVar3;
}

