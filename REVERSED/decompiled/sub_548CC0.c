/* sub_548CC0 @ 00548cc0   43 bytes */

void sub_548CC0(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1 + param_2 * 0xc;
  *(undefined1 *)(iVar1 + 0x55) = 0;
  *(undefined1 *)(iVar1 + 0x52) = 0x40;
  *(undefined1 *)(param_1 + (param_2 * 3 + 0x15) * 4) = 0x80;
  *(undefined1 *)(iVar1 + 0x53) = 4;
  *(undefined1 *)(iVar1 + 0x56) = 0;
  *(undefined1 *)(iVar1 + 0x57) = 0;
  return;
}

