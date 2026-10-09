/* sub_54E050 @ 0054e050   49 bytes */

void sub_54E050(int param_1)

{
  undefined2 uVar1;
  
  uVar1 = sub_54BC00(param_1);
  *(undefined2 *)(param_1 + 0xd0) = uVar1;
  uVar1 = sub_54BC00(param_1);
  *(undefined2 *)(param_1 + 0xce) = uVar1;
  uVar1 = sub_54BC00(param_1);
  *(undefined2 *)(param_1 + 0xcc) = uVar1;
  return;
}

