/* sub_406D30 @ 00406d30   244 bytes */

undefined4 sub_406D30(int *param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  
  if (DAT_00581154 != 0) {
    sub_406E30();
  }
  DAT_00581158 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  if (0 < DAT_00581158) {
    if (DAT_00581154 == 0) {
      DAT_00581154 = sub_41EF00(DAT_00581158 * 0x14);
      if (DAT_00581154 == 0) {
        return 0;
      }
    }
    iVar4 = 0;
    if (0 < DAT_00581158) {
      iVar3 = 0;
      do {
        uVar2 = *(undefined2 *)*param_1;
        *param_1 = (int)((undefined2 *)*param_1 + 1);
        *(undefined2 *)(iVar3 + DAT_00581154) = uVar2;
        uVar1 = *(undefined1 *)*param_1;
        *param_1 = (int)((undefined1 *)*param_1 + 1);
        *(undefined1 *)(iVar3 + 2 + DAT_00581154) = uVar1;
        uVar1 = *(undefined1 *)*param_1;
        *param_1 = (int)((undefined1 *)*param_1 + 1);
        *(undefined1 *)(iVar3 + 3 + DAT_00581154) = uVar1;
        uVar1 = *(undefined1 *)*param_1;
        *param_1 = (int)((undefined1 *)*param_1 + 1);
        *(undefined1 *)(iVar3 + 4 + DAT_00581154) = uVar1;
        uVar1 = *(undefined1 *)*param_1;
        *param_1 = (int)((undefined1 *)*param_1 + 1);
        *(undefined1 *)(iVar3 + 8 + DAT_00581154) = uVar1;
        uVar1 = *(undefined1 *)*param_1;
        *param_1 = (int)((undefined1 *)*param_1 + 1);
        *(undefined1 *)(iVar3 + 0xc + DAT_00581154) = uVar1;
        uVar1 = *(undefined1 *)*param_1;
        *param_1 = (int)((undefined1 *)*param_1 + 1);
        iVar4 = iVar4 + 1;
        *(undefined1 *)(iVar3 + 0x10 + DAT_00581154) = uVar1;
        iVar3 = iVar3 + 0x14;
      } while (iVar4 < DAT_00581158);
    }
  }
  return 1;
}

