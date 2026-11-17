/* sub_40FBE0 @ 0040fbe0   104 bytes */

void sub_40FBE0(char param_1,char *param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  if (DAT_005834d4 != 0) {
    if (param_1 != -1) {
      sub_562B75(&param_1,1,1,DAT_005834d4);
    }
    if (param_2 != (char *)0x0) {
      uVar2 = 0xffffffff;
      pcVar3 = param_2;
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      sub_562B75(param_2,1,~uVar2,DAT_005834d4);
    }
    if (param_3 != 0) {
      sub_562B75(param_3,param_4,1,DAT_005834d4);
    }
  }
  return;
}

