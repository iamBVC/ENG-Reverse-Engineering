/* sub_21106CB0 @ 21106cb0   250 bytes */

undefined4 __thiscall sub_21106CB0(void *this,int *param_1)

{
  uint uVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  ushort uVar5;
  
  if (*param_1 == 0x6468544d) {
    *(int **)((int)this + 0x34) = param_1;
    *(undefined4 *)((int)this + 0x30) = 3;
    uVar5 = 0;
    uVar3 = CONCAT11((char)*(undefined2 *)((int)param_1 + 10),
                     (char)((ushort)*(undefined2 *)((int)param_1 + 10) >> 8));
    uVar1 = param_1[1];
    iVar2 = ((uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8 | (uVar1 << 0x10 | uVar1 & 0xff00) << 8) + 8;
    iVar4 = (int)param_1 + iVar2;
    *(int *)((int)this + 0x2c) = iVar2;
    if (0x10 < uVar3) {
      return 1;
    }
    do {
      uVar1 = *(uint *)(iVar4 + 4);
      uVar1 = (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8 | (uVar1 << 0x10 | uVar1 & 0xff00) << 8;
      uVar5 = uVar5 + 1;
      *(uint *)((int)this + 0x2c) = *(int *)((int)this + 0x2c) + uVar1 + 8;
      iVar4 = iVar4 + 8 + uVar1;
    } while (uVar5 < uVar3);
    return 0;
  }
  iVar2 = 0x13;
  if (param_1[1] == 0) {
    iVar2 = 0x14;
  }
  *(int *)((int)this + 0x30) = iVar2;
  if (iVar2 == 0x13) {
    *(int *)((int)this + 0x34) = (int)param_1 + 0x13;
    *(undefined4 *)((int)this + 0x2c) = 0;
    return 0;
  }
  *(int *)((int)this + 0x34) = (int)param_1 + 0xf;
  *(undefined4 *)((int)this + 0x2c) = 0;
  return 0;
}

