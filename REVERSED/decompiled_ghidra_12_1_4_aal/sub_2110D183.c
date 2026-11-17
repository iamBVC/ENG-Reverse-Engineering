/* sub_2110D183 @ 2110d183   84 bytes */

void sub_2110D183(uint *param_1,uint param_2,int *param_3,int param_4)

{
  uint uVar1;
  
  if (param_4 == 0) {
    for (uVar1 = param_2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined1 *)param_1 = 0;
      param_1 = (uint *)((int)param_1 + 1);
    }
    for (uVar1 = param_2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *param_1 = 0;
      param_1 = param_1 + 1;
    }
    return;
  }
  uVar1 = param_2 >> 2;
  do {
    *param_1 = (uint)((longlong)*param_3 * (longlong)param_4) >> 7 |
               (int)((ulonglong)((longlong)*param_3 * (longlong)param_4) >> 0x20) << 0x19;
    param_3 = param_3 + 1;
    param_1 = param_1 + 1;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  return;
}

