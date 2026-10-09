/* sub_43B030 @ 0043b030   43 bytes */

byte sub_43B030(uint param_1)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  
  iVar1 = param_1;
  bVar2 = 0;
  bVar4 = 0;
  bVar3 = 0x80;
  if (0 < (int)param_1) {
    do {
      bVar2 = bVar2 | bVar3;
      bVar3 = bVar3 >> 1;
      bVar4 = bVar4 + 1;
      param_1 = (uint)bVar4;
    } while ((int)param_1 < iVar1);
  }
  return bVar2;
}

