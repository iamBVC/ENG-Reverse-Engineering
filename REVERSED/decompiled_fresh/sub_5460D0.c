/* sub_5460D0 @ 005460d0   101 bytes */

void sub_5460D0(short param_1,short param_2)

{
  int iVar1;
  
  if ((DAT_006d9490 != 0) && (DAT_005834f4 != 0)) {
    *(uint *)(DAT_006d9490 + 0x68) = *(uint *)(DAT_006d9490 + 0x68) | 0x200;
    if (param_1 < 0) {
      iVar1 = 0;
    }
    else if (param_1 < 7) {
      iVar1 = (int)param_1;
    }
    else {
      iVar1 = 6;
    }
    *(undefined4 *)(DAT_006d9490 + 0x6c) = (&DAT_00578360)[iVar1];
    *(int *)(DAT_006d9490 + 0x3c) = (int)param_2;
    *(undefined4 *)(DAT_006d9490 + 0x38) = 0xffffffff;
  }
  return;
}

