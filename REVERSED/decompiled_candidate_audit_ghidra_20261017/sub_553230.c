/* Selected Ghidra export at 00553230. */

void sub_553230(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_1c [12];
  uint uStack_10;
  undefined4 uStack_8;
  
  iVar1 = param_1;
  uVar2 = sub_54BC00(param_1);
  sub_553170(iVar1,auStack_1c,&param_1);
  uStack_10 = uStack_10 | *(uint *)(iVar1 + 0x138);
  uStack_8 = 1;
  sub_54BFC0(auStack_1c,iVar1 + 0x20,uVar2,param_1,1);
  return;
}

