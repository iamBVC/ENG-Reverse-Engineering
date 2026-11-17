/* sub_553AE0 @ 00553ae0   25 bytes */

void sub_553AE0(int *param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = sub_54BC00(param_1);
  *(undefined4 *)(*param_1 + param_2 * 4) = uVar1;
  return;
}

