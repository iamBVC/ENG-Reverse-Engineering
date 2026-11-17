/* sub_2110A040 @ 2110a040   216 bytes */

void __thiscall sub_2110A040(void *this,int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 != 0) {
    *(undefined4 *)((int)this + 0x58) = 0;
    *(int *)((int)this + 0x118) = param_1;
    *(undefined4 *)((int)this + 0x38) = *(undefined4 *)(param_1 + 0x34);
    *(undefined4 *)((int)this + *(int *)((int)this + 0x58) * 4 + 0x48) =
         *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)((int)this + 0x18) = *(undefined4 *)(param_1 + 0x18);
    if (*(int *)(param_1 + 0x1c) == 0) {
      uVar1 = 1;
    }
    else {
      uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x14);
    }
    *(undefined4 *)((int)this + 0x70) = uVar1;
    iVar2 = *(int *)(param_1 + 0x1c);
    if (*(int *)(param_1 + 0x30) == 1) {
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
      *(uint *)((int)this + 0x68) = (uint)*(ushort *)(*(int *)((int)this + 0x18) + 0xc) * iVar2;
      if (*(int *)(param_1 + 0x1c) != 0) {
        *(uint *)((int)this + 0x6c) =
             (uint)*(ushort *)(*(int *)((int)this + 0x18) + 0xc) *
             *(int *)(*(int *)(param_1 + 0x1c) + 0xc);
        return;
      }
      *(undefined4 *)((int)this + 0x6c) = 0;
    }
    else {
      if (iVar2 == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = *(undefined4 *)(iVar2 + 8);
      }
      *(undefined4 *)((int)this + 0x68) = uVar1;
      if (*(int *)(param_1 + 0x1c) == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xc);
      }
      *(undefined4 *)((int)this + 0x6c) = uVar1;
      sub_2110A200(this,0,*(uint *)(param_1 + 0x38),param_1);
      if (*(int *)(param_1 + 0x38) == 0) {
        *(undefined4 *)((int)this + 0xc) = 0;
        return;
      }
    }
  }
  return;
}

