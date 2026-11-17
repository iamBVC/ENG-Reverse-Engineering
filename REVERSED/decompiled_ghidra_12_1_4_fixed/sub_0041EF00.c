/* sub_41EF00 @ 0041ef00   47 bytes */

int sub_41EF00(int param_1)

{
  int iVar1;
  
  if (DAT_00586588 < param_1) {
    return 0;
  }
  iVar1 = DAT_00586584;
  DAT_00586584 = DAT_00586584 + param_1;
  DAT_00586588 = DAT_00586588 - param_1;
  return iVar1;
}

