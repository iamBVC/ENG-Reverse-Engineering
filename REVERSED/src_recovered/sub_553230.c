/* Selected Ghidra export at 00553230. */

void sub_553230(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint context[7] = {0};
  
  iVar1 = param_1;
  uVar2 = sub_54BC00(param_1);
  sub_553170(iVar1,context,&param_1);
  context[3] |= *(uint *)(iVar1 + 0x138);
  context[5] = 1;
  sub_54BFC0(context,iVar1 + 0x20,uVar2,param_1,1);
  return;
}

