/* sub_21109D20 @ 21109d20   37 bytes */

void __thiscall sub_21109D20(void *this,int param_1)

{
  if (param_1 != -1) {
    *(undefined4 *)(param_1 * 0x14 + *(int *)this) = 0;
    *(undefined4 *)(param_1 * 0x14 + 8 + *(int *)this) = 0;
  }
  return;
}

