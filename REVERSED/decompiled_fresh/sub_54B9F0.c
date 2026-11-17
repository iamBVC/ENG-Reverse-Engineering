/* sub_54B9F0 @ 0054b9f0   104 bytes */

void __thiscall sub_54B9F0(undefined8 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  LARGE_INTEGER local_8;
  
  if (*(int *)(param_1 + 3) == 1) {
    QueryPerformanceCounter(&local_8);
    *(undefined4 *)(param_1 + 3) = 0;
    uVar1 = __ftol();
    *param_1 = uVar1;
    QueryPerformanceCounter((LARGE_INTEGER *)&param_2);
    *(undefined4 *)(param_1 + 1) = param_2;
    *(undefined4 *)((int)param_1 + 0xc) = param_3;
    *(undefined4 *)(param_1 + 3) = 1;
    return;
  }
  uVar1 = __ftol();
  *param_1 = uVar1;
  return;
}

