/* sub_554530 @ 00554530   143 bytes */

void sub_554530(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = sub_54BC00(param_1);
  iVar2 = sub_54BC00(param_1);
  piVar3 = &DAT_005fd594;
  iVar5 = 0;
  do {
    if (*piVar3 == 0) {
      iVar4 = iVar5 * 0x42c;
      (&DAT_005fd594)[iVar5 * 0x10b] = param_1;
      (&DAT_005fd590)[iVar5 * 0x10b] = 0;
      (&DAT_005fd598)[iVar5 * 0x10b] = 0x40;
      *(int *)(iVar4 + 0x5fd59c) = iVar1 >> 0xc;
      *(int *)(iVar4 + 0x5fd5a0) = iVar2 >> 0xc;
      sub_54BBD0(param_1,&DAT_005fd180 + iVar4);
      return;
    }
    piVar3 = piVar3 + 0x10b;
    iVar5 = iVar5 + 1;
  } while ((int)piVar3 < 0x5fe644);
  sub_54BBD0(param_1,0);
  return;
}

