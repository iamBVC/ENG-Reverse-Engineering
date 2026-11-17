/* sub_427FF0 @ 00427ff0   25 bytes */

uint sub_427FF0(void)

{
  uint uVar1;
  char *pcVar2;
  
  uVar1 = 0;
  pcVar2 = &DAT_005fe260;
  do {
    if (*pcVar2 == '\0') {
      return uVar1;
    }
    uVar1 = uVar1 + 1;
    pcVar2 = pcVar2 + 0x34;
  } while (uVar1 < 0x40);
  return 0xffffffff;
}

