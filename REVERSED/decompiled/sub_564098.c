/* sub_564098 @ 00564098   90 bytes */

void sub_564098(char *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = sub_5694D7((int)*param_1);
  if (iVar3 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (DAT_0057ca10 < 2) {
        uVar4 = (byte)PTR_DAT_0057c804[*param_1 * 2] & 4;
      }
      else {
        uVar4 = sub_565AFC((int)*param_1,4);
      }
    } while (uVar4 != 0);
  }
  cVar2 = *param_1;
  *param_1 = DAT_0057ca14;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}

