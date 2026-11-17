/* sub_546000 @ 00546000   56 bytes */

void sub_546000(short param_1,short param_2)

{
  int iVar1;
  
  if (DAT_006d9490 != 0) {
    iVar1 = ((int)param_1 << 7) / (int)param_2;
    if (iVar1 < 0) {
      *(undefined2 *)(DAT_006d9490 + 0x5e) = 0;
      return;
    }
    if (0x80 < iVar1) {
      iVar1 = 0x80;
    }
    *(short *)(DAT_006d9490 + 0x5e) = (short)iVar1;
  }
  return;
}

