/* sub_2110FF0D @ 2110ff0d   74 bytes */

int __cdecl sub_2110FF0D(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_211157b0 = 1;
                    /* WARNING: Could not recover jumptable at 0x2110ff27. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_211157b0 = 1;
                    /* WARNING: Could not recover jumptable at 0x2110ff3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_211157e4;
  }
  DAT_211157b0 = (uint)bVar2;
  return param_1;
}

