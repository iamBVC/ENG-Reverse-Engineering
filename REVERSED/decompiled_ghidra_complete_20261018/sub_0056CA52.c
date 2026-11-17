/* sub_56CA52 @ 0056ca52   69 bytes */

undefined4 * sub_56CA52(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = &DAT_0057cee0;
  if (DAT_0057cee4 != param_1) {
    puVar3 = puVar2;
    do {
      puVar2 = puVar3 + 3;
      if (&DAT_0057cee0 + DAT_0057cf60 * 3 <= puVar2) break;
      piVar1 = puVar3 + 4;
      puVar3 = puVar2;
    } while (*piVar1 != param_1);
  }
  if ((&DAT_0057cee0 + DAT_0057cf60 * 3 <= puVar2) || (puVar2[1] != param_1)) {
    puVar2 = (undefined4 *)0x0;
  }
  return puVar2;
}

