/* sub_550940 @ 00550940   24 bytes */

void sub_550940(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) - iVar1;
  return;
}

