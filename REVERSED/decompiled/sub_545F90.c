/* sub_545F90 @ 00545f90   78 bytes */

void sub_545F90(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  if (DAT_006d9490 != 0) {
    iVar1 = ((int)(short)param_1 << 7) / (int)(short)param_2;
    if (iVar1 < 0) {
      iVar1 = 0;
    }
    else if (0x80 < iVar1) {
      iVar1 = 0x80;
    }
    *(short *)(DAT_006d9490 + 0x5c) = (short)iVar1;
    sub_545F40(param_1,param_2);
    sub_546060(param_1,param_2);
  }
  return;
}

