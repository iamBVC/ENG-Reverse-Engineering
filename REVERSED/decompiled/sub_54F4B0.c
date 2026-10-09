/* sub_54F4B0 @ 0054f4b0   70 bytes */

void sub_54F4B0(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0xffffffff;
  puVar2 = *(undefined4 **)(param_1 + 0x120);
  for (puVar1 = *(undefined4 **)(param_1 + 0x118); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    if ((puVar1 != puVar2) && (uVar3 = sub_404C90(puVar1 + 6,param_1 + 0x30), uVar3 < uVar4)) {
      *(undefined4 **)(param_1 + 0x120) = puVar1;
      uVar4 = uVar3;
    }
  }
  return;
}

