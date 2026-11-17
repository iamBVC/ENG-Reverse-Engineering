/* sub_5563F0 @ 005563f0   277 bytes */

undefined4 sub_5563F0(int *param_1,int param_2,int *param_3)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (param_2 * 0x84 == 0) {
    iVar4 = 0;
    iVar2 = 0;
  }
  else {
    iVar4 = *param_1;
    iVar2 = param_2 * 0x84 + iVar4;
    *param_1 = iVar2;
  }
  *param_3 = iVar4;
  if (param_2 < 1) {
    return CONCAT31((int3)((uint)iVar2 >> 8),1);
  }
  iVar4 = 0;
  do {
    iVar2 = (uint)*(ushort *)(iVar4 + 0x6c + *param_3) * 0x18;
    if (iVar2 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *param_1;
      *param_1 = iVar2 + iVar3;
    }
    *(int *)(iVar4 + 0x70 + *param_3) = iVar3;
    iVar2 = (uint)*(ushort *)(iVar4 + 0x6e + *param_3) * 0x1c;
    if (iVar2 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *param_1;
      *param_1 = iVar2 + iVar3;
    }
    *(int *)(iVar4 + 0x74 + *param_3) = iVar3;
    iVar2 = iVar4 + *param_3;
    iVar2 = (uint)*(ushort *)(iVar2 + 0x7c) + (uint)*(ushort *)(iVar4 + 0x7a + *param_3) +
            (uint)*(ushort *)(iVar2 + 0x78);
    if (iVar2 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *param_1;
      *param_1 = iVar2 * 0x20 + iVar3;
    }
    iVar5 = 0;
    *(int *)(iVar4 + 0x80 + *param_3) = iVar3;
    iVar2 = iVar4 + *param_3;
    if (*(short *)(iVar4 + 0x6e + *param_3) != 0) {
      iVar3 = 0;
      do {
        puVar1 = (ushort *)(*(int *)(iVar2 + 0x74) + 8 + iVar3);
        iVar5 = iVar5 + 1;
        iVar3 = iVar3 + 0x1c;
        *(uint *)puVar1 = DAT_00581154 + (uint)*puVar1 * 0x14;
        iVar2 = iVar4 + *param_3;
      } while (iVar5 < (int)(uint)*(ushort *)(iVar2 + 0x6e));
    }
    iVar4 = iVar4 + 0x84;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return 1;
}

