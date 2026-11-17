/* sub_41F770 @ 0041f770   317 bytes */

undefined4 sub_41F770(int *param_1,int param_2,int *param_3)

{
  ushort *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (param_2 * 0x8c == 0) {
    iVar5 = 0;
    iVar3 = 0;
  }
  else {
    iVar5 = *param_1;
    iVar3 = param_2 * 0x8c + iVar5;
    *param_1 = iVar3;
  }
  *param_3 = iVar5;
  if (param_2 < 1) {
    return CONCAT31((int3)((uint)iVar3 >> 8),1);
  }
  iVar5 = 0;
  do {
    uVar2 = (uint)*(ushort *)(iVar5 + 0x86 + *param_3);
    if (uVar2 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *param_1;
      *param_1 = uVar2 * 2 + iVar3;
    }
    *(int *)(iVar5 + 0x88 + *param_3) = iVar3;
    iVar3 = (uint)*(ushort *)(iVar5 + 0x6c + *param_3) * 0x18;
    if (iVar3 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = *param_1;
      *param_1 = iVar3 + iVar4;
    }
    *(int *)(iVar5 + 0x70 + *param_3) = iVar4;
    iVar3 = (uint)*(ushort *)(iVar5 + 0x6e + *param_3) * 0x1c;
    if (iVar3 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = *param_1;
      *param_1 = iVar3 + iVar4;
    }
    *(int *)(iVar5 + 0x74 + *param_3) = iVar4;
    iVar3 = iVar5 + *param_3;
    iVar3 = (uint)*(ushort *)(iVar3 + 0x7c) + (uint)*(ushort *)(iVar5 + 0x7a + *param_3) +
            (uint)*(ushort *)(iVar3 + 0x78);
    if (iVar3 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = *param_1;
      *param_1 = iVar3 * 0x20 + iVar4;
    }
    iVar6 = 0;
    *(int *)(iVar5 + 0x80 + *param_3) = iVar4;
    iVar3 = iVar5 + *param_3;
    if (*(short *)(iVar5 + 0x6e + *param_3) != 0) {
      iVar4 = 0;
      do {
        puVar1 = (ushort *)(*(int *)(iVar3 + 0x74) + 8 + iVar4);
        iVar6 = iVar6 + 1;
        iVar4 = iVar4 + 0x1c;
        *(uint *)puVar1 = DAT_00581154 + (uint)*puVar1 * 0x14;
        iVar3 = iVar5 + *param_3;
      } while (iVar6 < (int)(uint)*(ushort *)(iVar3 + 0x6e));
    }
    iVar5 = iVar5 + 0x8c;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return 1;
}

