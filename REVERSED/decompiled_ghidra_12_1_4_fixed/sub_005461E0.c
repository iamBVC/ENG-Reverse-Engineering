/* sub_5461E0 @ 005461e0   95 bytes */

uint sub_5461E0(int param_1,char param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar2 = sub_548760(DAT_006d9498,(int)param_2);
  uVar3 = 0;
  if (uVar2 != 0) {
    uVar3 = uVar2 & 0xffffff00;
    if (0 < *(int *)(DAT_006d9498 + 0x48)) {
      iVar4 = 0;
      do {
        if ((*(uint *)(*(int *)(DAT_006d9498 + 0x44) + 4 + iVar4 * 0x9c) == uVar2) &&
           (*(int *)(*(int *)(DAT_006d9498 + 0x44) + iVar4 * 0x9c + 0x20) == param_1)) {
          return uVar3;
        }
        cVar1 = (char)uVar3 + '\x01';
        uVar3 = CONCAT31((int3)(uVar3 >> 8),cVar1);
        iVar4 = (int)cVar1;
      } while (iVar4 < *(int *)(DAT_006d9498 + 0x48));
    }
  }
  return CONCAT31((int3)(uVar3 >> 8),0xff);
}

