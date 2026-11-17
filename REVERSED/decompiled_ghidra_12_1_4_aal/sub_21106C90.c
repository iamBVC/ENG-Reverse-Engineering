/* sub_21106C90 @ 21106c90   25 bytes */

undefined4 __thiscall sub_21106C90(void *this,int param_1)

{
  *(int *)((int)this + 0x34) = param_1;
  *(undefined4 *)((int)this + 0x30) = 7;
  *(undefined4 *)((int)this + 0x2c) = *(undefined4 *)(param_1 + 0xc);
  return 0;
}

