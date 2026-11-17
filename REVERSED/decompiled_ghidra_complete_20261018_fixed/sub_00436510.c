/* sub_436510 @ 00436510   52 bytes */

int sub_436510(char *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  cVar1 = *param_1;
  while (cVar1 != '\0') {
    param_1 = param_1 + 1;
    if (cVar1 == 0x20) {
      iVar2 = iVar2 + 10;
    }
    else {
      iVar2 = iVar2 + (uint)*(ushort *)(DAT_006da354 + 4 + cVar1 * 8);
    }
    cVar1 = *param_1;
  }
  return iVar2;
}

