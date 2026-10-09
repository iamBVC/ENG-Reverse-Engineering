/* sub_41ED90 @ 0041ed90   47 bytes */

int sub_41ED90(int param_1)

{
  int iVar1;
  
  if (DAT_00586570 < param_1) {
    return 0;
  }
  iVar1 = DAT_0058656c;
  DAT_0058656c = DAT_0058656c + param_1;
  DAT_00586570 = DAT_00586570 - param_1;
  return iVar1;
}

