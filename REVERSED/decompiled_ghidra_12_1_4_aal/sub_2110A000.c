/* sub_2110A000 @ 2110a000   55 bytes */

void __thiscall sub_2110A000(void *this,short *param_1)

{
  if (param_1 != (short *)0x0) {
    *(uint *)((int)this + 0x88) =
         (uint)((int)*param_1 * *(int *)(*(int *)((int)this + 0x5c) + 0xa8)) >> 10;
    *(uint *)((int)this + 0x8c) =
         (uint)((int)param_1[1] * *(int *)(*(int *)((int)this + 0x5c) + 0xa8)) >> 10;
  }
  return;
}

