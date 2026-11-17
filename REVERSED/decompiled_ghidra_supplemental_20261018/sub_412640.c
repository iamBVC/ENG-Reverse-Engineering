/* Selected Ghidra export at 00412640. */

undefined4 sub_412640(undefined4 *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined4 *puVar4;
  char acStack_100 [256];
  
  sub_562717();
  if (DAT_005834d4 != 0) {
    sub_562B75();
    if (&stack0x00000000 != (undefined1 *)0x100) {
      iVar2 = -1;
      pcVar3 = acStack_100;
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      sub_562B75();
    }
    if (param_1 != (undefined4 *)0x0) {
      sub_562B75();
    }
  }
  cVar1 = sub_412CB0();
  if (cVar1 != '\0') {
    puVar4 = (undefined4 *)(*(int *)(param_2 + 8) + 0x38);
    for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *param_1;
      param_1 = param_1 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  return 1;
}

