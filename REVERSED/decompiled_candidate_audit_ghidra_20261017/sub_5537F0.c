/* Selected Ghidra export at 005537f0. */

void sub_5537F0(int *param_1)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  if (iVar3 == 0) {
    DAT_006d9db8 = DAT_006d9db8 + 0xc;
    return;
  }
  do {
    puVar1 = (uint *)*param_1;
    uVar2 = *puVar1 & 0xffff;
    *param_1 = (int)(puVar1 + 1);
    if ((uVar2 != 0x44) && ((uVar2 == 0x45 || (uVar2 == 0xea)))) {
      *param_1 = (int)(puVar1 + 2);
    }
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  DAT_006d9db8 = DAT_006d9db8 + 0xc;
  return;
}

