/* sub_54B970 @ 0054b970   117 bytes */

undefined4 * __thiscall sub_54B970(undefined4 *param_1,undefined4 param_2)

{
  BOOL BVar1;
  LARGE_INTEGER local_10;
  LARGE_INTEGER local_8;
  
  *param_1 = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  param_1[3] = 0;
  param_1[6] = param_2;
  BVar1 = QueryPerformanceFrequency(&local_10);
  if (BVar1 == 0) {
    local_10.s.HighPart = -1;
    param_1[4] = 0xffffffff;
  }
  else {
    param_1[4] = local_10.s.LowPart;
  }
  param_1[5] = local_10.s.HighPart;
  if (param_1[6] == 1) {
    param_1[6] = 0;
    QueryPerformanceCounter(&local_8);
    param_1[2] = local_8.s.LowPart;
    param_1[3] = local_8.s.HighPart;
    param_1[6] = 1;
  }
  return param_1;
}

