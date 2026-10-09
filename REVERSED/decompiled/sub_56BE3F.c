/* sub_56BE3F @ 0056be3f   74 bytes */

int sub_56BE3F(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_006da580 = 1;
                    /* WARNING: Could not recover jumptable at 0x0056be59. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_006da580 = 1;
                    /* WARNING: Could not recover jumptable at 0x0056be6e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_006da404;
  }
  DAT_006da580 = (uint)bVar2;
  return param_1;
}

