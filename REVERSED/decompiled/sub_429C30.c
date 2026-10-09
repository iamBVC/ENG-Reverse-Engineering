/* sub_429C30 @ 00429c30   262 bytes */

void sub_429C30(uint param_1,uint param_2,uint param_3,uint param_4,undefined4 param_5,int param_6)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 < 3) {
    cVar1 = *(char *)(param_6 + 0x150 + param_1);
    if (cVar1 == -1) {
LAB_00429c5f:
      iVar4 = sub_427FF0(param_6);
    }
    else {
      iVar4 = (int)cVar1;
    }
  }
  else {
    if (*(char *)(param_6 + 0x153) == -1) goto LAB_00429c5f;
    iVar4 = (int)*(char *)(param_6 + 0x153);
  }
  if (iVar4 == -1) {
    return;
  }
  iVar3 = iVar4 * 0x34;
  (&DAT_005fe250)[iVar4 * 0xd] = param_5;
  if ((param_2 & 0xfff) == 0) {
    (&DAT_005fe243)[iVar3] = (byte)(param_2 >> 0xc) & 0x7f;
  }
  else {
    (&DAT_005fe240)[iVar3] = (char)(param_2 >> 0xc);
    (&DAT_005fe241)[iVar3] = (char)(param_3 >> 0xc);
    (&DAT_005fe242)[iVar3] = (char)(param_4 >> 0xc);
    (&DAT_005fe243)[iVar3] = 0x80;
  }
  if ((&DAT_005fe243)[iVar3] == 0) {
    if (*(short *)(&DAT_005fe24a + iVar3) == 0) {
      (&DAT_005fe250)[iVar4 * 0xd] = (&DAT_005fe250)[iVar4 * 0xd] | 0x1000000;
      goto LAB_00429d14;
    }
    uVar2 = (uint)(0xff / (longlong)(int)*(short *)(&DAT_005fe24a + iVar3));
  }
  else {
    uVar2 = (uint)(byte)(&DAT_005fe243)[iVar3];
  }
  (&DAT_005fe250)[iVar4 * 0xd] = (&DAT_005fe250)[iVar4 * 0xd] | uVar2 << 0x18;
LAB_00429d14:
  (&DAT_005fe260)[iVar3] = 1;
  if (2 < param_1) {
    *(char *)(param_6 + 0x153) = (char)iVar4;
    return;
  }
  *(char *)(param_6 + 0x150 + param_1) = (char)iVar4;
  return;
}

