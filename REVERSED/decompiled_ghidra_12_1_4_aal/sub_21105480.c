/* sub_21105480 @ 21105480   123 bytes */

void __fastcall sub_21105480(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = *(uint *)(param_1 + 0xcc);
  *(uint *)(param_1 + 0xcc) = uVar1 & 0xfffffff7;
  if ((uVar1 & 0x10) == 0) {
    _AAL_Lock_0();
    sub_21105590(*(int **)(param_1 + 0x88));
    while( true ) {
      iVar2 = (**(code **)(**(int **)(param_1 + 0x88) + 0x30))(*(int **)(param_1 + 0x88),0,0,1);
      if (iVar2 != -0x7787ff6a) break;
      (**(code **)(**(int **)(param_1 + 0x88) + 0x50))(*(int **)(param_1 + 0x88));
      Sleep(10);
    }
    if (iVar2 == 0) {
      Sleep(10);
      *(uint *)(param_1 + 0xcc) = *(uint *)(param_1 + 0xcc) | 0x10;
    }
    _AAL_Unlock_0();
  }
  return;
}

