/* sub_43C1B0 @ 0043c1b0   104 bytes */

void sub_43C1B0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = 0;
  puVar3 = &DAT_006d8750;
  do {
    *(undefined1 *)(param_1 + 0x11) = 0;
    iVar1 = sub_43AD90(puVar3,(int)*(short *)(param_1 + 0xc),(int)*(short *)(param_1 + 0xe),
                       param_1 + 4,param_1 + 6,*(undefined4 *)(param_1 + 0x214));
    if (iVar1 == 1) {
      *(char *)(param_1 + 0x11) = (char)iVar2;
      if (DAT_006d8748 < iVar2 + 1) {
        DAT_006d8748 = iVar2 + 1;
      }
      return;
    }
    puVar3 = puVar3 + 0x25;
    iVar2 = iVar2 + 1;
  } while ((int)puVar3 < 0x6d91b8);
  return;
}

