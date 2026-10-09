/* sub_553E80 @ 00553e80   37 bytes */

void sub_553E80(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  if (iVar1 != 0) {
    *param_1 = *param_1 + param_2 * 4;
  }
  return;
}

