/* sub_211053E0 @ 211053e0   156 bytes */

undefined4 __fastcall sub_211053E0(int param_1)

{
  int *piVar1;
  
  if ((*(byte *)(param_1 + 0xcc) & 0x20) == 0) {
    _AAL_Lock_0();
    LOCK();
    DAT_211155e0 = DAT_211155e0 + 1;
    UNLOCK();
    while (DAT_211155e4 != 0) {
      Sleep(1);
    }
    piVar1 = *(int **)(param_1 + 0x84);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
      *(undefined4 *)(param_1 + 0x84) = 0;
    }
    piVar1 = *(int **)(param_1 + 0xb4);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
      *(undefined4 *)(param_1 + 0xb4) = 0;
    }
    piVar1 = *(int **)(param_1 + 0xb8);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
      *(undefined4 *)(param_1 + 0xb8) = 0;
    }
    *(undefined4 *)(param_1 + 0x88) = 0;
    Sleep(10);
    LOCK();
    DAT_211155e0 = DAT_211155e0 + -1;
    UNLOCK();
    _AAL_Unlock_0();
    return 1;
  }
  return 0;
}

