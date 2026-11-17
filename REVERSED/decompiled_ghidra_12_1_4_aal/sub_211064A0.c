/* sub_211064A0 @ 211064a0   95 bytes */

void __thiscall sub_211064A0(void *this,byte param_1)

{
  void *pvVar1;
  
  if ((param_1 & 0x40) != 0) {
    if (*(int *)((int)this + 0x1c) == 0) {
      pvVar1 = operator_new(0x18);
      *(void **)((int)this + 0x1c) = pvVar1;
      *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 2;
    }
    *(undefined4 *)(*(int *)((int)this + 0x1c) + 8) = 0;
    *(undefined4 *)(*(int *)((int)this + 0x1c) + 0xc) = *(undefined4 *)((int)this + 0x2c);
    *(undefined4 *)(*(int *)((int)this + 0x1c) + 0x14) = 0;
  }
  if (((param_1 & 0x80) != 0) && (*(int *)((int)this + 0x1c) != 0)) {
    *(undefined4 *)(*(int *)((int)this + 0x1c) + 0x14) = 1;
  }
  return;
}

