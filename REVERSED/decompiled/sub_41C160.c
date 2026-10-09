/* sub_41C160 @ 0041c160   25 bytes */

int sub_41C160(void)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  
  iVar1 = 0;
  pbVar2 = &DAT_00585274;
  iVar3 = 0x300;
  do {
    iVar1 = iVar1 + (uint)*pbVar2;
    pbVar2 = pbVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return iVar1;
}

