/* sub_5508F0 @ 005508f0   24 bytes */

void sub_5508F0(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + iVar1;
  return;
}

