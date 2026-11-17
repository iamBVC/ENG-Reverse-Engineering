/* sub_21107C70 @ 21107c70   147 bytes */

void __fastcall sub_21107C70(int param_1)

{
  int *piVar1;
  int iVar2;
  HGLOBAL hMem;
  int iVar3;
  int iVar4;
  
  piVar1 = *(int **)(param_1 + 0x14);
  if (piVar1 != (int *)0x0) {
    iVar2 = piVar1[1];
    iVar4 = piVar1[4];
    iVar3 = 0;
    if (0 < *piVar1) {
      do {
        _AAL_Lock_0();
        piVar1 = *(int **)(iVar4 + 4);
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 8))(piVar1);
          *(undefined4 *)(iVar4 + 4) = 0;
        }
        piVar1 = *(int **)(iVar4 + 8);
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 8))(piVar1);
          *(undefined4 *)(iVar4 + 8) = 0;
        }
        piVar1 = *(int **)(iVar4 + 0xc);
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 8))(piVar1);
          *(undefined4 *)(iVar4 + 0xc) = 0;
        }
        _AAL_Unlock_0();
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + iVar2;
      } while (iVar3 < **(int **)(param_1 + 0x14));
    }
    if (*(LPCVOID *)(param_1 + 0x14) != (LPCVOID)0x0) {
      hMem = GlobalHandle(*(LPCVOID *)(param_1 + 0x14));
      GlobalUnlock(hMem);
      GlobalFree(hMem);
      *(undefined4 *)(param_1 + 0x14) = 0;
    }
  }
  return;
}

