/* sub_21101090 @ 21101090   48 bytes */

undefined4 sub_21101090(HMODULE param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    _AAL_Quit_0();
  }
  else if (param_2 == 1) {
    DisableThreadLibraryCalls(param_1);
    uVar1 = sub_21101000(param_1);
    return uVar1;
  }
  return 1;
}

