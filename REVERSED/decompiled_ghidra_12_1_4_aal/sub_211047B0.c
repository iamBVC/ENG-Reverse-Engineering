/* sub_211047B0 @ 211047b0   54 bytes */

undefined4 * __fastcall sub_211047B0(int param_1)

{
  undefined4 *puVar1;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)0x0;
  local_4 = 0;
  if (*(int *)(param_1 + 0xb8) != 0) {
    _AAL_Lock_0();
    puVar1 = &local_4;
    (**(code **)(**(int **)(param_1 + 0xb8) + 0x20))(*(int **)(param_1 + 0xb8));
    _AAL_Unlock_0();
  }
  return puVar1;
}

