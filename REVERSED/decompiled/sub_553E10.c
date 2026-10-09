/* sub_553E10 @ 00553e10   51 bytes */

void sub_553E10(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  if (iVar1 == 0) {
    *param_1 = *param_1 + param_2 * 4;
  }
  param_1[0x3a] = param_1[0x3a] | 2;
  return;
}

