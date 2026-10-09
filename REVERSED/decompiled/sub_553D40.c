/* sub_553D40 @ 00553d40   50 bytes */

void sub_553D40(int *param_1,int param_2)

{
  sub_54BBD0(param_1,*param_1);
  param_1[0x3a] = param_1[0x3a] | 2;
  *param_1 = *param_1 + param_2 * 4;
  return;
}

