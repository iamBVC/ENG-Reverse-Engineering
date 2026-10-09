/* sub_418D80 @ 00418d80   346 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_418D80(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int local_c;
  
  iVar6 = 0;
  iVar5 = *param_1;
  if (0 < param_1[2]) {
    local_c = 0;
    do {
      iVar3 = param_1[3];
      uVar4 = ((int *)(param_1[4] + local_c))[4];
      if ((uVar4 & 0x10) != 0) {
        iVar3 = -1;
      }
      if (((uVar4 & 0x20) != 0) && (iVar3 == iVar6 + -1)) {
        iVar3 = iVar6;
      }
      iVar2 = *(int *)(param_1[4] + local_c);
      if ((iVar2 != 0) && ((uVar4 & 8) == 0)) {
        if ((uVar4 & 1) == 0) {
          if ((uVar4 & 2) == 0) {
            sub_436770(iVar2,iVar5,iVar6,iVar3);
          }
          else {
            sub_4368D0(iVar2,iVar5,iVar6,iVar3,1,0x1ec);
          }
        }
        else {
          sub_4368D0(iVar2,iVar5,iVar6,iVar3,0,0x14);
        }
      }
      piVar1 = (int *)(param_1[4] + local_c);
      if (((*(byte *)(param_1[4] + 0x14 + local_c) & 0xa0) != 0) && (param_1[3] == iVar6)) {
        fsin((float10)(DAT_00584650 & 0x7f) * (float10)_DAT_0056e230);
        uVar4 = __ftol();
        uVar4 = uVar4 | (uVar4 << 8 | uVar4) << 8;
        if ((*(byte *)(piVar1 + 4) & 1) == 0) {
          iVar3 = *piVar1;
          if (iVar3 != 0) {
            iVar3 = sub_436510(iVar3);
            sub_424710(iVar5,uVar4,iVar3 / 2,0x100);
          }
        }
        else {
          sub_424710(iVar5,uVar4,0xec,0x100);
        }
      }
      if ((*(byte *)(param_1[4] + 0x10 + local_c) & 4) != 0) {
        iVar5 = iVar5 + param_1[1];
      }
      iVar6 = iVar6 + 1;
      local_c = local_c + 0x18;
    } while (iVar6 < param_1[2]);
  }
  return;
}

