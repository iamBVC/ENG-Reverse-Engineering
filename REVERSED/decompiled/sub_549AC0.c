/* sub_549AC0 @ 00549ac0   70 bytes */

void sub_549AC0(int param_1,short param_2)

{
  undefined2 local_10 [6];
  undefined4 local_4;
  
  if (param_2 < (short)(ushort)*(byte *)(DAT_006d949c + 0x72)) {
    local_10[0] = 2;
    local_4 = *(undefined4 *)(*(int *)(DAT_006d949c + 0x68) + param_2 * 4);
    sub_547D70(param_1 + 0x14,local_10,0);
  }
  return;
}

