/* sub_565BAD @ 00565bad   62 bytes */

undefined4 sub_565BAD(void)

{
  DAT_006db918 = HeapAlloc(DAT_006db91c,0,0x140);
  if (DAT_006db918 == (LPVOID)0x0) {
    return 0;
  }
  DAT_006db910 = 0;
  DAT_006db914 = 0;
  DAT_006db90c = DAT_006db918;
  DAT_006db904 = 0x10;
  return 1;
}

