/* sub_21109BF0 @ 21109bf0   82 bytes */

void __fastcall sub_21109BF0(int *param_1)

{
  if (param_1[5] != 0) {
    SetEvent((HANDLE)param_1[2]);
    WaitForSingleObject((HANDLE)param_1[5],0xffffffff);
    CloseHandle((HANDLE)param_1[5]);
    CloseHandle((HANDLE)param_1[2]);
  }
  if (*param_1 != 0) {
    sub_2110D4F4((LPVOID)(*param_1 + -4));
    *param_1 = 0;
  }
  return;
}

