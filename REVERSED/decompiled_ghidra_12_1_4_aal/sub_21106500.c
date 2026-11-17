/* sub_21106500 @ 21106500   88 bytes */

void __thiscall sub_21106500(void *this,undefined2 *param_1)

{
  if ((*(undefined2 **)((int)this + 0x18) != (undefined2 *)0x0) && (param_1 != (undefined2 *)0x0)) {
    **(undefined2 **)((int)this + 0x18) = *param_1;
    *(undefined2 *)(*(int *)((int)this + 0x18) + 2) = param_1[1];
    *(undefined4 *)(*(int *)((int)this + 0x18) + 4) = *(undefined4 *)(param_1 + 2);
    *(undefined2 *)(*(int *)((int)this + 0x18) + 0xe) = param_1[7];
    *(undefined2 *)(*(int *)((int)this + 0x18) + 0xc) = param_1[6];
    *(undefined4 *)(*(int *)((int)this + 0x18) + 8) = *(undefined4 *)(param_1 + 4);
    *(undefined2 *)(*(int *)((int)this + 0x18) + 0x10) = param_1[8];
  }
  return;
}

