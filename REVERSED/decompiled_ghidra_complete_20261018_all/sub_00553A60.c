/* sub_553A60 @ 00553a60   37 bytes */

void sub_553A60(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = sub_54BC00(param_1);
  puVar2 = (undefined4 *)sub_5509F0(param_1,*(undefined4 *)(param_1 + 0xc),param_2);
  *puVar2 = uVar1;
  return;
}

