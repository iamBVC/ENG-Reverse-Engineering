/* sub_548B60 @ 00548b60   300 bytes */

void sub_548B60(int *param_1,uint *param_2)

{
  undefined1 uVar1;
  byte *pbVar2;
  byte bVar3;
  uint uVar4;
  byte *pbVar5;
  
  pbVar2 = (byte *)param_1[0xd];
  if (pbVar2 < (byte *)(param_1[0xf] + *param_1)) {
    pbVar5 = pbVar2 + 1;
    bVar3 = *pbVar2;
    uVar4 = (uint)bVar3;
    param_1[0xd] = (int)pbVar5;
    if ((bVar3 & 0x80) != 0) {
      uVar4 = bVar3 & 0x7f;
      do {
        bVar3 = *pbVar5;
        pbVar5 = pbVar5 + 1;
        param_1[0xd] = (int)pbVar5;
        uVar4 = uVar4 * 0x80 + (bVar3 & 0x7f);
      } while ((bVar3 & 0x80) != 0);
    }
    param_1[0x11] = param_1[0x11] + uVar4;
    bVar3 = *pbVar5;
    param_1[0xd] = (int)(pbVar5 + 1);
    if (bVar3 != 0xff) {
      *(undefined1 *)(param_2 + 2) = 0xf;
      *param_2 = uVar4;
      if ((bVar3 & 0x80) == 0) {
        *(byte *)((int)param_2 + 0xb) = bVar3;
        *(char *)((int)param_2 + 10) = (char)param_1[0x12];
      }
      else {
        uVar1 = *(undefined1 *)param_1[0xd];
        param_1[0xd] = (int)((undefined1 *)param_1[0xd] + 1);
        *(undefined1 *)((int)param_2 + 0xb) = uVar1;
        *(byte *)((int)param_2 + 10) = bVar3;
        *(ushort *)(param_1 + 0x12) = (ushort)bVar3;
      }
      bVar3 = *(byte *)((int)param_2 + 10) & 0xf0;
      if ((bVar3 != 0xc0) && (bVar3 != 0xd0)) {
        uVar1 = *(undefined1 *)param_1[0xd];
        param_1[0xd] = (int)((undefined1 *)param_1[0xd] + 1);
        *(undefined1 *)(param_2 + 3) = uVar1;
        return;
      }
      *(undefined1 *)(param_2 + 3) = 0;
      return;
    }
    bVar3 = pbVar5[1];
    param_1[0xd] = (int)(pbVar5 + 2);
    if (bVar3 == 0x2f) {
      *(undefined1 *)(param_2 + 2) = 0x10;
      uVar1 = *(undefined1 *)param_1[0xd];
      param_1[0xd] = (int)((undefined1 *)param_1[0xd] + 1);
      *(undefined1 *)((int)param_2 + 9) = uVar1;
      *param_2 = uVar4;
      *(undefined1 *)((int)param_2 + 10) = 0x2f;
    }
    else if (bVar3 == 0x51) {
      *(undefined1 *)(param_2 + 2) = 0x10;
      uVar1 = *(undefined1 *)param_1[0xd];
      param_1[0xd] = (int)((undefined1 *)param_1[0xd] + 1);
      *(undefined1 *)((int)param_2 + 9) = uVar1;
      uVar1 = *(undefined1 *)param_1[0xd];
      param_1[0xd] = (int)((undefined1 *)param_1[0xd] + 1);
      *(undefined1 *)((int)param_2 + 0xb) = uVar1;
      uVar1 = *(undefined1 *)param_1[0xd];
      param_1[0xd] = (int)((undefined1 *)param_1[0xd] + 1);
      *(undefined1 *)(param_2 + 3) = uVar1;
      uVar1 = *(undefined1 *)param_1[0xd];
      param_1[0xd] = (int)((undefined1 *)param_1[0xd] + 1);
      *(undefined1 *)(param_2 + 3) = uVar1;
      *param_2 = uVar4;
      *(undefined1 *)((int)param_2 + 10) = 0x51;
      *(undefined2 *)(param_1 + 0x12) = 0;
      return;
    }
    *(undefined2 *)(param_1 + 0x12) = 0;
  }
  return;
}

