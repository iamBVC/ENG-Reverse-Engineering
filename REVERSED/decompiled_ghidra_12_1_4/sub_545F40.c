/* sub_545F40 @ 00545f40   72 bytes */

void sub_545F40(short param_1,short param_2)

{
  int iVar1;
  
  if (DAT_006d9490 != 0) {
    iVar1 = ((int)param_1 << 7) / (int)param_2;
    if (iVar1 < 0) {
      iVar1 = 0;
    }
    else if (0x80 < iVar1) {
      iVar1 = 0x80;
    }
    *(short *)(DAT_006d9490 + 0x60) = (short)iVar1;
    *(undefined2 *)(DAT_006d949c + 0x6e) = *(undefined2 *)(DAT_006d9490 + 0x60);
  }
  return;
}

