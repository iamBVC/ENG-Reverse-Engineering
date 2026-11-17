/* sub_21105500 @ 21105500   102 bytes */

void __fastcall sub_21105500(int param_1)

{
  int iVar1;
  
  if ((*(byte *)(param_1 + 0xcc) & 0x10) != 0) {
    while (DAT_211155cc != 0) {
      Sleep(1);
    }
    _AAL_Lock_0();
    while (iVar1 = (**(code **)(**(int **)(param_1 + 0x88) + 0x48))(*(int **)(param_1 + 0x88)),
          iVar1 == -0x7787ff6a) {
      (**(code **)(**(int **)(param_1 + 0x88) + 0x50))(*(int **)(param_1 + 0x88));
      Sleep(10);
    }
    Sleep(10);
    *(uint *)(param_1 + 0xcc) = *(uint *)(param_1 + 0xcc) & 0xffffffef;
    _AAL_Unlock_0();
  }
  return;
}

