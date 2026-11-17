/* sub_211047F0 @ 211047f0   75 bytes */

void __thiscall sub_211047F0(void *this,int param_1)

{
  if (param_1 < 1) {
    param_1 = 1;
  }
  else if (6 < param_1) {
    param_1 = 6;
  }
  if (*(int *)((int)this + 0xb8) != 0) {
    _AAL_Lock_0();
    (**(code **)(**(int **)((int)this + 0xb8) + 0x24))(*(int **)((int)this + 0xb8),param_1);
    _AAL_Unlock_0();
  }
  sub_211047B0((int)this);
  return;
}

