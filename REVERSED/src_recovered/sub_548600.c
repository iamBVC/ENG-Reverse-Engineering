/* Selected Ghidra export at 00548600. */

void sub_548600(int param_1)

{
  short *psVar1;
  int iVar2;
  
  psVar1 = (short *)(param_1 + 0x2c);
  do {
    if (*psVar1 == 8) {
      sub_547D70(param_1 + 0x10,psVar1,*(undefined4 *)(param_1 + 0x4c));
    }
    else {
      sub_547EC0(param_1,psVar1);
    }
    iVar2 = sub_547D20(param_1 + 0x10,psVar1);
    *(int *)(param_1 + 0x50) = iVar2;
  } while (iVar2 == 0);
  *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + iVar2;
  return;
}

