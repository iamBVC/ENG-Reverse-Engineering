/* sub_437AC0 @ 00437ac0   120 bytes */

void sub_437AC0(char param_1,ushort *param_2,char *param_3,int param_4)

{
  ushort uVar1;
  char cVar2;
  
  if (DAT_006d76c8 == 0) {
    if (0 < param_4) {
      do {
        uVar1 = *param_2;
        param_2 = param_2 + 1;
        *param_3 = *(char *)((int)&DAT_0061ff34 + (uVar1 & 0x7fff)) + param_1;
        param_3 = param_3 + 1;
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
  }
  else if (0 < param_4) {
    do {
      uVar1 = *param_2;
      param_2 = param_2 + 1;
      cVar2 = param_1;
      if (uVar1 != 0) {
        cVar2 = *(char *)((int)&DAT_0061ff34 + (uVar1 & 0x7fff)) + param_1 + '\x01';
      }
      *param_3 = cVar2;
      param_3 = param_3 + 1;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
    return;
  }
  return;
}

