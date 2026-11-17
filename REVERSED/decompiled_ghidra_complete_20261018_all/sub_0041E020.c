/* sub_41E020 @ 0041e020   355 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41E020(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  iVar4 = DAT_00584648;
  uVar6 = DAT_005790b0 >> 0xc;
  uVar7 = DAT_005790b8 >> 0xc;
  _DAT_0058642c = 0xffffffff;
  iVar3 = DAT_006d9e38;
  if (((((int)uVar6 < 0) || (*(uint *)(DAT_00584648 + 0x14) <= uVar6)) || ((int)uVar7 < 0)) ||
     ((*(uint *)(DAT_00584648 + 0x18) <= uVar7 ||
      (iVar5 = *(uint *)(DAT_00584648 + 0x14) * uVar7 + uVar6, DAT_006da350 == 0)))) {
    DAT_00586424 = -0x10000;
  }
  else {
    _DAT_0058642c =
         *(uint *)(DAT_006da350 + *(int *)(*(int *)(DAT_00584648 + 0x48) + iVar5 * 4) * 8);
    if (DAT_0058641c == 0) {
      DAT_00586424 = *(int *)(DAT_006da350 + 4 +
                             *(int *)(*(int *)(DAT_00584648 + 0x48) + iVar5 * 4) * 8);
      piVar1 = *(int **)(*(int *)(DAT_00584648 + 0x40) + iVar5 * 4);
      if (piVar1 != (int *)0x0) {
        for (piVar2 = (int *)piVar1[1]; piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
          piVar1 = piVar2;
        }
        DAT_00586424 = DAT_00586424 +
                       *(int *)(*piVar1 * 0x20 + 0x14 + *(int *)(DAT_00584648 + 0x3c));
      }
    }
    else {
      DAT_00586424 = DAT_0058641c;
    }
    if (_DAT_0058642c == 0) {
      _DAT_0058642c = 0xffffffff;
    }
  }
  do {
    if (iVar3 == 0) {
      return;
    }
    if ((*(uint *)(iVar3 + 0xe8) & 4) == 0) {
      uVar6 = *(uint *)(iVar3 + 0xec);
      if ((*(uint *)(iVar3 + 0xe8) & 0x800) == 0) {
        *(uint *)(iVar3 + 0xec) = uVar6 & 0xfffbffff;
        uVar6 = *(int *)(iVar3 + 0x30) >> 0xc;
        uVar7 = *(int *)(iVar3 + 0x38) >> 0xc;
        if (((-1 < (int)uVar6) && (uVar6 < *(uint *)(iVar4 + 0x14))) &&
           ((-1 < (int)uVar7 &&
            ((uVar7 < *(uint *)(iVar4 + 0x18) &&
             ((_DAT_0058642c &
              1 << ((byte)*(undefined4 *)
                           (*(int *)(iVar4 + 0x48) + (*(uint *)(iVar4 + 0x14) * uVar7 + uVar6) * 4)
                   & 0x1f)) == 0)))))) goto LAB_0041e120;
        uVar6 = *(uint *)(iVar3 + 0xec);
      }
      *(uint *)(iVar3 + 0xec) = uVar6 | 0x40000;
    }
LAB_0041e120:
    iVar3 = *(int *)(iVar3 + 4);
  } while( true );
}

