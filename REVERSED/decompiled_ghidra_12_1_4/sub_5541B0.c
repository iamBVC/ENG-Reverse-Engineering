/* sub_5541B0 @ 005541b0   196 bytes */

void sub_5541B0(byte *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar6 = param_1;
  pbVar5 = param_1 + param_2 * 4;
  pbVar4 = param_1 + param_2 * 8;
  if (param_2 != 0) {
    param_1 = (byte *)param_2;
    do {
      iVar1 = ((int)(((uint)*pbVar6 - (uint)*pbVar5) * param_3) >> 0xc) + (uint)*pbVar5;
      iVar3 = ((int)(((uint)pbVar6[1] - (uint)pbVar5[1]) * param_3) >> 0xc) + (uint)pbVar5[1];
      iVar2 = ((int)(((uint)pbVar6[2] - (uint)pbVar5[2]) * param_3) >> 0xc) + (uint)pbVar5[2];
      if (iVar1 < 0x100) {
        if (iVar1 < 0) {
          iVar1 = 0;
        }
      }
      else {
        iVar1 = 0xff;
      }
      if (iVar3 < 0x100) {
        if (iVar3 < 0) {
          iVar3 = 0;
        }
      }
      else {
        iVar3 = 0xff;
      }
      if (iVar2 < 0x100) {
        if (iVar2 < 0) {
          iVar2 = 0;
        }
      }
      else {
        iVar2 = 0xff;
      }
      *pbVar4 = (byte)iVar1;
      pbVar4[1] = (byte)iVar3;
      pbVar4[2] = (byte)iVar2;
      pbVar6 = pbVar6 + 4;
      pbVar5 = pbVar5 + 4;
      pbVar4 = pbVar4 + 4;
      param_1 = (byte *)((int)param_1 + -1);
    } while (param_1 != (byte *)0x0);
  }
  return;
}

