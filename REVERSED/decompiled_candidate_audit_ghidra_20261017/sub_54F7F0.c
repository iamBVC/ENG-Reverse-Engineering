/* Selected Ghidra export at 0054f7f0. */

void sub_54F7F0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = sub_54BC00(param_1);
  iVar2 = sub_54BC00(param_1);
  fpatan((float10)iVar2,(float10)iVar1);
  uVar3 = __ftol();
  sub_54BBD0(param_1,(uVar3 & 0xfff) << 0xc);
  return;
}

