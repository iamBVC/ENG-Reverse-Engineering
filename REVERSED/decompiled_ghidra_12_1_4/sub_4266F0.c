/* sub_4266F0 @ 004266f0   67 bytes */

void sub_4266F0(byte *param_1,int param_2,undefined4 param_3,char param_4)

{
  byte bVar1;
  
  bVar1 = *param_1;
  if (bVar1 != 0) {
    do {
      sub_425CB0(param_2,param_3,bVar1 + 0x1e,(int)param_4,1,1);
      bVar1 = param_1[1];
      param_2 = param_2 + 0xc;
      param_1 = param_1 + 1;
    } while (bVar1 != 0);
  }
  return;
}

