/* sub_437C90 @ 00437c90   99 bytes */

bool sub_437C90(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  *param_4 = 0;
  param_4[3] = param_2;
  *param_4 = 0x7c;
  param_4[1] = 0x1007;
  param_4[2] = param_3;
  puVar2 = (undefined4 *)(DAT_0058342c + 0x5c);
  puVar3 = param_4 + 0x12;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  param_4[0x1a] = 0x40;
  param_4[0x1b] = 0;
  param_4[0x1c] = 0;
  param_4[0x1d] = 0;
  iVar1 = (**(code **)(*DAT_00582ccc + 0x18))(DAT_00582ccc,param_4,param_1,0);
  return iVar1 == 0;
}

