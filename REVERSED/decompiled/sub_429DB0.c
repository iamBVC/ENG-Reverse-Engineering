/* sub_429DB0 @ 00429db0   79 bytes */

void sub_429DB0(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x34;
  (&DAT_005fe240)[iVar1] = 0;
  (&DAT_005fe241)[iVar1] = 0;
  (&DAT_005fe242)[iVar1] = 0;
  (&DAT_005fe243)[iVar1] = 0;
  (&DAT_005fe25c)[param_1 * 0xd] = 0xffffffff;
  (&DAT_005fe250)[param_1 * 0xd] = 0;
  (&DAT_005fe23c)[param_1 * 0xd] = 0xffff0000;
  *(undefined2 *)(&DAT_005fe24a + iVar1) = 0;
  (&DAT_005fe260)[iVar1] = 0;
  return;
}

