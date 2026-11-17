/* sub_2110E7C3 @ 2110e7c3   27 bytes */

undefined4 __cdecl sub_2110E7C3(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_2111577c != (code *)0x0) {
    iVar1 = (*DAT_2111577c)(param_1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}

