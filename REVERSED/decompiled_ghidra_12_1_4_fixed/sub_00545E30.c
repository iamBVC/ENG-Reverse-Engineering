/* sub_545E30 @ 00545e30   127 bytes */

void sub_545E30(void)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  
  if (DAT_006d9498 != 0) {
    iVar4 = *(int *)(DAT_006d9498 + 0x48);
    if (iVar4 != 0) {
      pbVar2 = (byte *)(*(int *)(DAT_006d9498 + 0x44) + 0x3c);
      do {
        if (((*(int *)(pbVar2 + -0x2c) != 0) && ((*pbVar2 & 8) == 0)) &&
           (*(int *)(pbVar2 + 0x4c) != 0)) {
          _AAL_PauseVoice_4(*(undefined4 *)(*(int *)(pbVar2 + 0x4c) + 0x14));
        }
        pbVar2 = pbVar2 + 0x9c;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  if (DAT_006d949c != 0) {
    uVar3 = 0;
    bVar1 = *(byte *)(DAT_006d949c + 0x72);
    iVar4 = DAT_006d949c;
    if (bVar1 != 0) {
      do {
        if (*(char *)(*(int *)(*(int *)(iVar4 + 0x68) + uVar3 * 4) + 0x4a) != '\0') {
          sub_549A70(iVar4,uVar3);
          iVar4 = DAT_006d949c;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < bVar1);
    }
  }
  return;
}

