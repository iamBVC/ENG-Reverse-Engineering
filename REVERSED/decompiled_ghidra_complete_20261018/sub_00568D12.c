/* sub_568D12 @ 00568d12   67 bytes */

int * sub_568D12(int param_1)

{
  int *piVar1;
  
  piVar1 = &DAT_0057cee0;
  if (DAT_0057cee0 != param_1) {
    do {
      piVar1 = piVar1 + 3;
      if (&DAT_0057cee0 + DAT_0057cf60 * 3 <= piVar1) break;
    } while (*piVar1 != param_1);
  }
  if ((&DAT_0057cee0 + DAT_0057cf60 * 3 <= piVar1) || (*piVar1 != param_1)) {
    piVar1 = (int *)0x0;
  }
  return piVar1;
}

