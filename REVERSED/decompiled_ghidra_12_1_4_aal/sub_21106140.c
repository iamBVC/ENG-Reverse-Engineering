/* sub_21106140 @ 21106140   65 bytes */

void __thiscall sub_21106140(void *this,undefined4 *param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)((int)this + 4); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x3c)) {
    if (*(void **)(iVar1 + 0x30) == this) {
      (**(code **)(iVar1 + 0x18))(*(undefined4 *)(iVar1 + 0x38));
    }
  }
  (**(code **)(*(int *)((int)this + 0xb0) + 0x7c))
            (param_1,*(undefined4 *)((int)this + 0x60),*(undefined4 *)((int)this + 0x5c));
  *(undefined4 *)((int)this + 0xac) = *param_1;
  return;
}

