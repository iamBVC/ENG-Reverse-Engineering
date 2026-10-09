/* sub_408320 @ 00408320   98 bytes */

uint sub_408320(void)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar3 = DAT_00581148;
  if (0 < DAT_00581148) {
    iVar4 = 0;
    iVar3 = DAT_00581144;
    do {
      if (*(char *)(iVar4 + 0xc + iVar3) != '\0') {
        piVar1 = *(int **)(iVar4 + 0x10 + iVar3);
        uVar2 = (**(code **)(*piVar1 + 0x18))
                          (piVar1,0,0,*(undefined4 *)(iVar4 + 4 + iVar3),
                           *(undefined4 *)(iVar4 + 8 + iVar3));
        if (uVar2 != 0) {
          return uVar2 & 0xffffff00;
        }
        *(undefined1 *)(iVar4 + 0xc + DAT_00581144) = 0;
        iVar3 = DAT_00581144;
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x1c;
    } while (iVar5 < DAT_00581148);
  }
  return CONCAT31((int3)((uint)iVar3 >> 8),1);
}

