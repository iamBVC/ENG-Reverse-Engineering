/* sub_413700 @ 00413700   68 bytes */

undefined4 * __thiscall sub_413700(undefined4 *param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  *param_1 = 0;
  param_1[1] = 0;
  uVar1 = sub_56D4ED(param_2);
  param_1[2] = uVar1;
  param_1[3] = param_3[3];
  param_1[4] = param_3[2];
  puVar3 = param_1 + 5;
  for (iVar2 = 0x1f; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_3;
    param_3 = param_3 + 1;
    puVar3 = puVar3 + 1;
  }
  return param_1;
}

