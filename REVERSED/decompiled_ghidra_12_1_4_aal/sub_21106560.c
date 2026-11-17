/* sub_21106560 @ 21106560   27 bytes */

void __thiscall sub_21106560(void *this,undefined4 param_1,undefined4 param_2)

{
  if (*(int *)((int)this + 0x1c) != 0) {
    *(undefined4 *)(*(int *)((int)this + 0x1c) + 8) = param_1;
    *(undefined4 *)(*(int *)((int)this + 0x1c) + 0xc) = param_2;
  }
  return;
}

