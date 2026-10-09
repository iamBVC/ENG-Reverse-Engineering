/* sub_437A60 @ 00437a60   91 bytes */

void sub_437A60(int *param_1,undefined1 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[4];
  if (iVar3 < param_1[5]) {
    iVar2 = iVar3 << 5;
    do {
      iVar4 = param_1[2];
      if (iVar4 < param_1[3]) {
        do {
          iVar1 = *param_1;
          if (iVar1 < param_1[1]) {
            do {
              *(undefined1 *)((int)&DAT_0061ff34 + iVar1 + (iVar2 + iVar4) * 0x20) = param_2;
              iVar1 = iVar1 + 1;
            } while (iVar1 < param_1[1]);
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < param_1[3]);
      }
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 0x20;
    } while (iVar3 < param_1[5]);
  }
  return;
}

