/* sub_553170 @ 00553170   89 bytes */

void sub_553170(int *param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  
  *param_2 = param_1;
  param_2[1] = *(undefined4 *)*param_1;
  iVar1 = *param_1;
  *param_1 = iVar1 + 4;
  *param_3 = *(undefined4 *)(iVar1 + 4);
  iVar1 = *param_1;
  *param_1 = iVar1 + 4;
  param_2[2] = *(undefined4 *)(iVar1 + 4);
  iVar1 = *param_1;
  *param_1 = iVar1 + 4;
  param_2[3] = *(undefined4 *)(iVar1 + 4);
  iVar1 = *param_1;
  *param_1 = iVar1 + 4;
  param_2[4] = *(undefined4 *)(iVar1 + 4);
  *param_1 = *param_1 + 4;
  param_2[6] = 0;
  return;
}

