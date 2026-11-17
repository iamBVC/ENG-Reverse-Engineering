/* sub_548C90 @ 00548c90   46 bytes */

void sub_548C90(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = 0;
  puVar3 = (undefined4 *)(param_1 + 0x4c);
  iVar1 = 0x10;
  do {
    *puVar3 = 0;
    sub_548CC0(param_1,iVar2);
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 3;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}

