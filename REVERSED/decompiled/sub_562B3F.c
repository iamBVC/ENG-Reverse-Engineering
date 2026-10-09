/* sub_562B3F @ 00562b3f   54 bytes */

void sub_562B3F(uint param_1)

{
  int iVar1;
  
  if ((param_1 <= DAT_0057ca20) && (iVar1 = sub_565F41(param_1), iVar1 != 0)) {
    return;
  }
  if (param_1 == 0) {
    param_1 = 1;
  }
  HeapAlloc(DAT_006db91c,0,param_1 + 0xf & 0xfffffff0);
  return;
}

