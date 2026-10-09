/* sub_546300 @ 00546300   86 bytes */

void sub_546300(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((DAT_006d9498 != 0) && (iVar4 = *(int *)(DAT_006d9498 + 0x48), iVar4 != 0)) {
    iVar3 = 0;
    iVar2 = DAT_006d9498;
    do {
      iVar1 = *(int *)(iVar2 + 0x44) + iVar3;
      if ((*(int *)(iVar1 + 4) != 0) && ((*(uint *)(iVar1 + 0x3c) & 0x2000) == 0)) {
        *(undefined4 *)(iVar1 + 0x20) = 0;
        sub_5489F0(DAT_006d9498 + 0x10,iVar1);
        iVar2 = DAT_006d9498;
      }
      iVar3 = iVar3 + 0x9c;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  return;
}

