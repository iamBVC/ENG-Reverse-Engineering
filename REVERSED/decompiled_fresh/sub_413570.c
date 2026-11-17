/* sub_413570 @ 00413570   80 bytes */

undefined4 * __thiscall
sub_413570(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[0xe] = param_1 + 0xc;
  param_1[0xc] = param_1 + 0xd;
  param_1[0xd] = 0;
  uVar1 = sub_56D4ED(param_2);
  param_1[3] = param_3;
  param_1[2] = uVar1;
  puVar3 = param_1 + 4;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_4;
    param_4 = param_4 + 1;
    puVar3 = puVar3 + 1;
  }
  return param_1;
}

