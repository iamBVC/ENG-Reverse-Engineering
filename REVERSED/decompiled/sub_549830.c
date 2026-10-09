/* sub_549830 @ 00549830   66 bytes */

int sub_549830(int param_1,byte param_2,undefined4 param_3,uint param_4)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  
  pbVar1 = *(byte **)(param_1 + 0x4c + (param_4 & 0xff) * 0xc);
  if (pbVar1 != (byte *)0x0) {
    iVar3 = 0;
    if (*pbVar1 != 0) {
      iVar2 = *(int *)(pbVar1 + 8);
      do {
        if ((*(byte *)(iVar2 + 6) <= param_2) && (param_2 <= *(byte *)(iVar2 + 7))) {
          return iVar2;
        }
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + 0x20;
      } while (iVar3 < (int)(uint)*pbVar1);
    }
  }
  return 0;
}

