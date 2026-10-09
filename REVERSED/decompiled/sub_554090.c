/* sub_554090 @ 00554090   274 bytes */

void sub_554090(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  piVar2 = (int *)sub_553F10(param_1);
  if ((piVar2 != (int *)0x0) && ((int *)piVar2[5] != (int *)0x0)) {
    if (((DAT_006da330 & 0x10000000) != 0) && (*(int *)piVar2[5] == piVar2[4])) {
      piVar4 = *(int **)(DAT_00584648[0x10] + (DAT_00584648[5] * piVar2[2] + *piVar2) * 4);
      while (((iVar3 = *piVar4 * 0x20 + DAT_00584648[0xf],
              ((*(uint *)(iVar3 + 0x10) ^ *(uint *)(param_1 + 0x30)) & 0xfffff000) != 0 ||
              (((*(uint *)(iVar3 + 0x14) ^ *(uint *)(param_1 + 0x34)) & 0xfffff000) != 0)) ||
             (((*(uint *)(iVar3 + 0x18) ^ *(uint *)(param_1 + 0x38)) & 0xfffff000) != 0))) {
        piVar4 = (int *)piVar4[1];
      }
      iVar3 = DAT_00584648[0x15];
      if (iVar3 != 0) {
        uVar1 = *(undefined4 *)(iVar3 + *piVar4 * 4);
        *(undefined4 *)(iVar3 + *piVar4 * 4) =
             *(undefined4 *)(iVar3 + (*DAT_00584648 + DAT_006da2bc) * 4);
        *(undefined4 *)(DAT_00584648[0x15] + (*DAT_00584648 + DAT_006da2bc) * 4) = uVar1;
      }
      iVar3 = DAT_00584648[0x16];
      uVar1 = *(undefined4 *)(iVar3 + *piVar4 * 4);
      *(undefined4 *)(iVar3 + *piVar4 * 4) =
           *(undefined4 *)(iVar3 + (*DAT_00584648 + DAT_006da2bc) * 4);
      *(undefined4 *)(DAT_00584648[0x16] + (*DAT_00584648 + DAT_006da2bc) * 4) = uVar1;
    }
    *(int *)piVar2[5] = piVar2[3];
  }
  return;
}

