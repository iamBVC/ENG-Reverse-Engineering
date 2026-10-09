/* sub_5464D0 @ 005464d0   254 bytes */

void sub_5464D0(void)

{
  byte bVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  undefined2 local_10 [6];
  undefined4 local_4;
  
  if (DAT_006d949c != 0) {
    bVar1 = *(byte *)(DAT_006d949c + 0x72);
    sub_547E80(DAT_006d949c + 0x14);
    local_10[0] = 8;
    local_4 = 0;
    sub_547D70(DAT_006d949c + 0x14,local_10,*(undefined4 *)(DAT_006d949c + 0x48));
    uVar2 = sub_547D20(DAT_006d949c + 0x14,DAT_006d949c + 0x30);
    uVar3 = 0;
    *(undefined4 *)(DAT_006d949c + 0x40) = uVar2;
    iVar5 = DAT_006d949c;
    if (bVar1 != 0) {
      do {
        if (*(char *)(*(int *)(*(int *)(iVar5 + 0x68) + uVar3 * 4) + 0x4a) != '\0') {
          sub_549A70(iVar5,uVar3);
          iVar5 = DAT_006d949c;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < bVar1);
    }
    sub_545C00();
    sub_545C00();
    if (*(int *)(*(int *)(DAT_006d9490 + 0x50) + 0x10) != 0) {
      if (*(int *)(DAT_006d949c + 0x94) != 0) {
        piVar4 = (int *)(*(int *)(DAT_006d949c + 0x94) + 0xc);
        iVar5 = 0x80;
        do {
          if (*piVar4 != 0) {
            _AAL_UnloadFile_4(*piVar4);
          }
          piVar4 = piVar4 + 4;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      *(undefined4 *)(*(int *)(DAT_006d9490 + 0x50) + 0x10) = 0;
    }
    *(undefined1 *)(DAT_006d949c + 0x72) = 0;
    *(undefined4 *)(DAT_006d949c + 0xa4) = 0;
  }
  return;
}

