/* sub_429B70 @ 00429b70   178 bytes */

void sub_429B70(uint param_1,undefined4 param_2,uint param_3,uint param_4,int param_5,int param_6)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 < 3) {
    cVar1 = *(char *)(param_1 + 0x150 + param_6);
    if (cVar1 != -1) {
      iVar2 = (int)cVar1;
      goto LAB_00429ba7;
    }
  }
  else if (*(char *)(param_6 + 0x153) != -1) {
    iVar2 = (int)*(char *)(param_6 + 0x153);
    goto LAB_00429ba7;
  }
  iVar2 = sub_427FF0(param_6);
LAB_00429ba7:
  if (iVar2 != -1) {
    iVar3 = iVar2 * 0x34;
    (&DAT_005fe254)[iVar2 * 0xd] = param_2;
    *(short *)(&DAT_005fe24a + iVar3) = (short)(param_3 >> 0xc);
    if (param_5 == 0) {
      if (param_4 >> 0xc != 0) {
        (&DAT_005fe25c)[iVar2 * 0xd] = (param_4 >> 0xc) * 0x20 + -0x20;
      }
    }
    else {
      (&DAT_005fe246)[iVar3] = (char)param_5;
      (&DAT_005fe23c)[iVar2 * 0xd] = param_4;
    }
    if (param_1 < 3) {
      *(char *)(param_1 + 0x150 + param_6) = (char)iVar2;
      (&DAT_005fe260)[iVar3] = 1;
      return;
    }
    *(char *)(param_6 + 0x153) = (char)iVar2;
    (&DAT_005fe260)[iVar3] = 1;
  }
  return;
}

