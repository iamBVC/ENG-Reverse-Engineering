/* sub_546E50 @ 00546e50   77 bytes */

int sub_546E50(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 local_4;
  
  iVar3 = 0;
  local_4 = 0;
  iVar1 = _AAL_Enumerate3DProviders_12(&local_4,&DAT_006d91e4,&DAT_006d91e0);
  if (iVar1 != 0) {
    puVar2 = &DAT_006d91e0;
    do {
      if (0x6d93df < (int)puVar2) {
        return iVar3;
      }
      iVar3 = iVar3 + 1;
      iVar1 = _AAL_Enumerate3DProviders_12(&stack0xfffffff0,puVar2 + 3,puVar2 + 2);
      puVar2 = puVar2 + 2;
    } while (iVar1 != 0);
  }
  return iVar3;
}

