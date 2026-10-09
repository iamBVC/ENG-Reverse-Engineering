/* sub_553A40 @ 00553a40   32 bytes */

void sub_553A40(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = sub_54BC00(param_1);
  *(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + 0xf4) + param_2 * 4) = uVar1;
  return;
}

