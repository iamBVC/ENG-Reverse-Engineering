/* sub_568D55 @ 00568d55   88 bytes */

byte * sub_568D55(void)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  if (DAT_006db928 == 0) {
    sub_56C06A();
  }
  bVar1 = *DAT_006db920;
  pbVar4 = DAT_006db920;
  if (bVar1 == 0x22) {
    while( true ) {
      pbVar3 = pbVar4;
      bVar1 = pbVar3[1];
      pbVar4 = pbVar3 + 1;
      if ((bVar1 == 0x22) || (bVar1 == 0)) break;
      iVar2 = sub_56BC64(bVar1);
      if (iVar2 != 0) {
        pbVar4 = pbVar3 + 2;
      }
    }
    if (*pbVar4 == 0x22) goto LAB_00568d92;
  }
  else {
    while (0x20 < bVar1) {
      bVar1 = pbVar4[1];
      pbVar4 = pbVar4 + 1;
    }
  }
  for (; (*pbVar4 != 0 && (*pbVar4 < 0x21)); pbVar4 = pbVar4 + 1) {
LAB_00568d92:
  }
  return pbVar4;
}

