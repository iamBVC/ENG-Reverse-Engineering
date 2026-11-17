/* sub_549A00 @ 00549a00   102 bytes */

void sub_549A00(int param_1,short param_2,short param_3)

{
  undefined2 local_10 [2];
  int local_c;
  undefined4 local_4;
  
  if (param_2 < (short)(ushort)*(byte *)(DAT_006d949c + 0x72)) {
    if (param_3 < 0) {
      param_3 = 0;
    }
    else if (0x80 < param_3) {
      param_3 = 0x80;
    }
    local_10[0] = 3;
    local_c = (int)param_3;
    local_4 = *(undefined4 *)(*(int *)(DAT_006d949c + 0x68) + param_2 * 4);
    sub_547D70(param_1 + 0x14,local_10,0);
  }
  return;
}

