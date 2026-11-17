/* sub_21104710 @ 21104710   156 bytes */

void __fastcall sub_21104710(undefined4 *param_1)

{
  int *piVar1;
  
  *param_1 = &PTR_sub_211046F0_21112338;
  if ((LPVOID)param_1[0x18] != (LPVOID)0x0) {
    sub_2110D4F4((LPVOID)param_1[0x18]);
    param_1[0x18] = 0;
  }
  if ((LPVOID)param_1[0x1a] != (LPVOID)0x0) {
    sub_2110D4F4((LPVOID)param_1[0x1a]);
    param_1[0x1a] = 0;
  }
  if ((LPVOID)param_1[0x1d] != (LPVOID)0x0) {
    sub_2110D4F4((LPVOID)param_1[0x1d]);
    param_1[0x1d] = 0;
  }
  piVar1 = (int *)param_1[5];
  while (piVar1 != param_1 + 6) {
    if (*piVar1 != 0) {
      *(int *)(*piVar1 + 4) = piVar1[1];
      *(int *)piVar1[1] = *piVar1;
      *piVar1 = 0;
      piVar1[1] = 0;
    }
    piVar1 = (int *)param_1[5];
  }
  piVar1 = (int *)param_1[2];
  while (piVar1 != param_1 + 3) {
    if (*piVar1 != 0) {
      *(int *)(*piVar1 + 4) = piVar1[1];
      *(int *)piVar1[1] = *piVar1;
      *piVar1 = 0;
      piVar1[1] = 0;
    }
    piVar1 = (int *)param_1[2];
  }
  return;
}

