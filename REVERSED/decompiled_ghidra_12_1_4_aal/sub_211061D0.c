/* sub_211061D0 @ 211061d0   161 bytes */

void __fastcall sub_211061D0(undefined4 *param_1)

{
  sub_21107C70((int)param_1);
  if ((LPVOID)param_1[3] != (LPVOID)0x0) {
    sub_2110D4F4((LPVOID)param_1[3]);
    param_1[3] = 0;
  }
  if ((LPCVOID)param_1[4] != (LPCVOID)0x0) {
    UnmapViewOfFile((LPCVOID)param_1[4]);
    param_1[4] = 0;
  }
  if (((*(byte *)(param_1 + 1) & 1) != 0) && ((LPVOID)param_1[6] != (LPVOID)0x0)) {
    sub_2110D4F4((LPVOID)param_1[6]);
    param_1[6] = 0;
  }
  if (((*(byte *)(param_1 + 1) & 2) != 0) && ((LPVOID)param_1[7] != (LPVOID)0x0)) {
    sub_2110D4F4((LPVOID)param_1[7]);
    param_1[7] = 0;
  }
  if (((*(byte *)(param_1 + 1) & 4) != 0) && ((LPVOID)param_1[9] != (LPVOID)0x0)) {
    sub_2110D4F4((LPVOID)param_1[9]);
    param_1[9] = 0;
  }
  if ((LPVOID)param_1[8] != (LPVOID)0x0) {
    sub_2110D4F4((LPVOID)param_1[8]);
    param_1[8] = 0;
  }
  if ((LPVOID)*param_1 != (LPVOID)0x0) {
    sub_2110D4F4((LPVOID)*param_1);
    *param_1 = 0;
  }
  return;
}

