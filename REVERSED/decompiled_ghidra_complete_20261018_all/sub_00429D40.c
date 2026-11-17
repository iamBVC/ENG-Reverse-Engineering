/* sub_429D40 @ 00429d40   106 bytes */

void sub_429D40(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (int)*(char *)(param_1 + 0x150 + param_2);
  if (iVar1 != -1) {
    iVar2 = iVar1 * 0x34;
    (&DAT_005fe240)[iVar2] = 0;
    (&DAT_005fe241)[iVar2] = 0;
    (&DAT_005fe242)[iVar2] = 0;
    (&DAT_005fe243)[iVar2] = 0;
    (&DAT_005fe25c)[iVar1 * 0xd] = 0xffffffff;
    (&DAT_005fe250)[iVar1 * 0xd] = 0;
    (&DAT_005fe23c)[iVar1 * 0xd] = 0xffff0000;
    *(undefined2 *)(&DAT_005fe24a + iVar2) = 0;
    *(undefined1 *)(param_1 + 0x150 + param_2) = 0xff;
    (&DAT_005fe260)[iVar2] = 0;
  }
  return;
}

