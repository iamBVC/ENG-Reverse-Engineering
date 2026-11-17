/* sub_565BEB @ 00565beb   43 bytes */

uint sub_565BEB(int param_1)

{
  uint uVar1;
  
  uVar1 = DAT_006db918;
  while( true ) {
    if (DAT_006db918 + DAT_006db914 * 0x14 <= uVar1) {
      return 0;
    }
    if ((uint)(param_1 - *(int *)(uVar1 + 0xc)) < 0x100000) break;
    uVar1 = uVar1 + 0x14;
  }
  return uVar1;
}

