/* sub_4067B0 @ 004067b0   207 bytes */

undefined4 sub_4067B0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  uint *puVar4;
  uint uVar5;
  int iVar6;
  
  DAT_00581140 = (int *)sub_41EF00(param_2);
  if (DAT_00581140 == (int *)0x0) {
    return 0;
  }
  sub_415A90(param_1,DAT_00581140,param_2);
  iVar6 = *DAT_00581140;
  piVar2 = DAT_00581140 + 1;
  if (0 < iVar6) {
    do {
      iVar1 = piVar2[1];
      piVar2 = piVar2 + 2;
      if (iVar1 * 2 != 0) {
        piVar2 = (int *)((int)piVar2 + iVar1 * 2);
      }
      if (iVar1 != 0) {
        piVar2 = (int *)((int)piVar2 + iVar1);
      }
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  iVar6 = *piVar2;
  puVar4 = (uint *)(piVar2 + 1);
  if (0 < iVar6) {
    do {
      puVar3 = puVar4 + 3;
      uVar5 = puVar4[2] * puVar4[1];
      if (*puVar4 != 0) {
        if ((*puVar4 & 0x80) == 0) {
          uVar5 = uVar5 * 2;
        }
        else {
          uVar5 = *puVar3;
          puVar3 = puVar4 + 4;
        }
      }
      puVar4 = puVar3;
      if (uVar5 != 0) {
        puVar4 = (uint *)((int)puVar4 + uVar5);
      }
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  DAT_00581158 = *puVar4;
  if ((0 < (int)DAT_00581158) && (DAT_00581154 == 0)) {
    DAT_00581154 = sub_41EF00(DAT_00581158 * 0x14);
    if (DAT_00581154 == 0) {
      return 0;
    }
  }
  return 1;
}

