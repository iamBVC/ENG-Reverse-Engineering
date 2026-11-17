/* sub_2110E81C @ 2110e81c   43 bytes */

uint __cdecl sub_2110E81C(int param_1)

{
  uint uVar1;
  
  uVar1 = DAT_21115a3c;
  while( true ) {
    if (DAT_21115a3c + DAT_21115a38 * 0x14 <= uVar1) {
      return 0;
    }
    if ((uint)(param_1 - *(int *)(uVar1 + 0xc)) < 0x100000) break;
    uVar1 = uVar1 + 0x14;
  }
  return uVar1;
}

