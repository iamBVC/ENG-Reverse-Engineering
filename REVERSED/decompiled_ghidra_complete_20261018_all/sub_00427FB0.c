/* sub_427FB0 @ 00427fb0   49 bytes */

void sub_427FB0(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_005fe250;
  iVar2 = 0x40;
  do {
    *(undefined1 *)(puVar1 + 4) = 0;
    *puVar1 = 0;
    puVar1[3] = 0xffffffff;
    puVar1[-5] = 0xffff0000;
    puVar1[1] = 0x1000;
    puVar1 = puVar1 + 0xd;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

