/* sub_54F470 @ 0054f470   63 bytes */

void sub_54F470(int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0xffffffff;
  for (puVar1 = *(undefined4 **)(param_1 + 0x118); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    uVar2 = sub_404C90(puVar1 + 6,DAT_006d9e1c + 0x30);
    if (uVar2 < uVar3) {
      *(undefined4 **)(param_1 + 0x120) = puVar1;
      uVar3 = uVar2;
    }
  }
  return;
}

