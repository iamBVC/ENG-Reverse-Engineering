/* sub_545EB0 @ 00545eb0   132 bytes */

void sub_545EB0(void)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  if (DAT_006d9498 != 0) {
    iVar3 = *(int *)(DAT_006d9498 + 0x48);
    if (iVar3 != 0) {
      piVar1 = (int *)(*(int *)(DAT_006d9498 + 0x44) + 0x88);
      do {
        if ((piVar1[-0x1e] != 0) && (*piVar1 != 0)) {
          _AAL_ResumeVoice_4(*(undefined4 *)(*piVar1 + 0x14));
        }
        piVar1 = piVar1 + 0x27;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  if (((DAT_006d949c != 0) && (*(int **)(DAT_006d949c + 0xa4) != (int *)0x0)) &&
     (uVar2 = 0, piVar1 = *(int **)(DAT_006d949c + 0xa4), *(int *)(DAT_006d949c + 0xa0) != 0)) {
    do {
      uVar2 = uVar2 + 1;
      *(undefined4 *)(*piVar1 + 0x20) = 0;
      *(undefined4 *)(*piVar1 + 0x24) = 0;
      piVar1 = piVar1 + 1;
    } while (uVar2 < *(uint *)(DAT_006d949c + 0xa0));
  }
  return;
}

