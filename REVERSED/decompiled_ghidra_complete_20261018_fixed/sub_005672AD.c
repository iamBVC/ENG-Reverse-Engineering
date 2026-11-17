/* sub_5672AD @ 005672ad   27 bytes */

undefined4 sub_5672AD(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_006da410 != (code *)0x0) {
    iVar1 = (*DAT_006da410)(param_1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}

