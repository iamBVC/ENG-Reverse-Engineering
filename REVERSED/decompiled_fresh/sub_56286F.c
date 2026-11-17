/* sub_56286F @ 0056286f   77 bytes */

float10 sub_56286F(byte *param_1)

{
  uint uVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  while( true ) {
    if (DAT_0057ca10 < 2) {
      uVar1 = (byte)PTR_DAT_0057c804[(uint)*param_1 * 2] & 8;
    }
    else {
      uVar1 = sub_565AFC(*param_1,8);
    }
    if (uVar1 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar5 = 0;
  uVar4 = 0;
  sVar2 = _strlen((char *)param_1);
  iVar3 = sub_565A6B(param_1,sVar2,uVar4,uVar5);
  return (float10)*(double *)(iVar3 + 0x10);
}

