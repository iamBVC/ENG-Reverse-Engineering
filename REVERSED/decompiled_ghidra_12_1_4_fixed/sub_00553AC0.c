/* sub_553AC0 @ 00553ac0   29 bytes */

void sub_553AC0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = sub_54BC00(param_1);
  *(undefined4 *)(*(int *)(param_1 + 0xf4) + param_2 * 4) = uVar1;
  return;
}

