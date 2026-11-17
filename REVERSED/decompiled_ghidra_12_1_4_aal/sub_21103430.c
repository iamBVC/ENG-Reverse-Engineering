/* sub_21103430 @ 21103430   285 bytes */

undefined4 __thiscall sub_21103430(void *this,int *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  
  pbVar4 = (byte *)(param_1 + 1);
  if (*pbVar4 == 0) {
    if ((param_1[0x41] == *(int *)((int)this + 0x11c)) && (*param_1 == *(int *)((int)this + 0x18)))
    {
      pbVar4 = (byte *)((int)this + 0x9c);
      pbVar2 = (byte *)(param_1 + 0x21);
      do {
        bVar1 = *pbVar2;
        bVar5 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_21103494:
          iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
          goto LAB_21103499;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar5 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_21103494;
        pbVar2 = pbVar2 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_21103499:
      if (iVar3 == 0) {
        return 1;
      }
    }
  }
  else if ((param_1[0x41] == *(int *)((int)this + 0x11c)) &&
          (*param_1 == *(int *)((int)this + 0x18))) {
    pbVar2 = (byte *)((int)this + 0x1c);
    do {
      bVar1 = *pbVar4;
      bVar5 = bVar1 < *pbVar2;
      if (bVar1 != *pbVar2) {
LAB_211034f2:
        iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
        goto LAB_211034f7;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar4[1];
      bVar5 = bVar1 < pbVar2[1];
      if (bVar1 != pbVar2[1]) goto LAB_211034f2;
      pbVar4 = pbVar4 + 2;
      pbVar2 = pbVar2 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_211034f7:
    if (iVar3 == 0) {
      pbVar4 = (byte *)((int)this + 0x9c);
      pbVar2 = (byte *)(param_1 + 0x21);
      do {
        bVar1 = *pbVar2;
        bVar5 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_2110352f:
          iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
          goto LAB_21103534;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar5 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_2110352f;
        pbVar2 = pbVar2 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_21103534:
      if (iVar3 == 0) {
        return 1;
      }
    }
  }
  return 0;
}

