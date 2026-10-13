/* Selected Ghidra export at 00554bc0. */

void sub_554BC0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_006d9e1c;
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 0x800;
  DAT_006d9e1c = param_1;
  sub_4051D0();
  DAT_006d9e1c = uVar1;
  return;
}

