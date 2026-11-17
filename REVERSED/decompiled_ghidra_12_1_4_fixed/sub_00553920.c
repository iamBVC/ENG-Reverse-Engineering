/* sub_553920 @ 00553920   46 bytes */

void sub_553920(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = sub_54BC00(param_1);
  if (DAT_006d9e1c != 0) {
    puVar2 = (undefined4 *)sub_5509F0(param_1,DAT_006d9e1c,param_2);
    *puVar2 = uVar1;
  }
  return;
}

