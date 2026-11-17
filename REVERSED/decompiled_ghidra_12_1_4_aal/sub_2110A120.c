/* sub_2110A120 @ 2110a120   39 bytes */

void __thiscall sub_2110A120(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  if ((*(int *)((int)this + 0x5c) != 0) &&
     (iVar1 = *(int *)(*(int *)((int)this + 0x5c) + 0xb0), iVar1 != -0x74)) {
    (**(code **)(iVar1 + 0x7c))(param_1,param_2,param_3);
  }
  return;
}

