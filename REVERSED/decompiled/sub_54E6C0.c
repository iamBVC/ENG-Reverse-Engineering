/* sub_54E6C0 @ 0054e6c0   92 bytes */

void sub_54E6C0(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  
  pbVar4 = *(byte **)(param_1 + 200);
  uVar1 = sub_54BC00(param_1);
  iVar2 = sub_54BC00(param_1);
  iVar3 = 0;
  if (*(ushort *)(param_1 + 0xc6) != 0) {
    do {
      if ((uint)*pbVar4 == iVar2 >> 0xc) {
        *(undefined2 *)(pbVar4 + 2) = uVar1;
        return;
      }
      iVar3 = iVar3 + 1;
      pbVar4 = pbVar4 + 4;
    } while (iVar3 < (int)(uint)*(ushort *)(param_1 + 0xc6));
  }
  *pbVar4 = (byte)(iVar2 >> 0xc);
  *(undefined2 *)(pbVar4 + 2) = uVar1;
  *(short *)(param_1 + 0xc6) = *(short *)(param_1 + 0xc6) + 1;
  return;
}

