/* sub_549150 @ 00549150   164 bytes */

void sub_549150(int param_1,int *param_2)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  undefined2 local_10 [6];
  int *local_4;
  
  pbVar2 = (byte *)param_2[0xd];
  if (pbVar2 < (byte *)(param_2[0xf] + *param_2)) {
    pbVar4 = pbVar2 + 1;
    bVar1 = *pbVar2;
    uVar3 = (uint)bVar1;
    param_2[0xd] = (int)pbVar4;
    if ((bVar1 & 0x80) != 0) {
      uVar3 = bVar1 & 0x7f;
      do {
        bVar1 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        param_2[0xd] = (int)pbVar4;
        uVar3 = uVar3 * 0x80 + (bVar1 & 0x7f);
      } while ((bVar1 & 0x80) != 0);
    }
    param_2[0xd] = (int)pbVar2;
    if (param_2[0xb] <= (int)(param_2[0x11] + uVar3)) {
      if (param_2[10] == 0x7fffffff) {
        param_2[0xb] = 0x7fffffff;
      }
      param_2[0xd] = param_2[5];
      *(short *)(param_2 + 0x12) = (short)param_2[8];
      param_2[0x11] = param_2[6];
    }
    local_10[0] = 0xe;
    local_4 = param_2;
    sub_547D70(param_1 + 0x14,local_10,*(int *)(param_1 + 0x4c) * uVar3);
  }
  return;
}

