/* sub_54D9D0 @ 0054d9d0   43 bytes */

void sub_54D9D0(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = *(undefined4 *)*param_1;
  *param_1 = (int)((undefined4 *)*param_1 + 1);
  iVar2 = sub_426860(uVar1,0,0,0,0);
  sub_54BBD0(param_1,iVar2 << 0xc);
  return;
}

