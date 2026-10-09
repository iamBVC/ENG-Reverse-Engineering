/* sub_547890 @ 00547890   47 bytes */

undefined4 sub_547890(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 != 0) {
    uVar1 = 1 << (*(byte *)(param_2 + 0xc) & 0x1f);
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | uVar1;
    if ((uVar1 & *(uint *)(param_1 + 0x24)) != 0) {
      *(uint *)(param_1 + 0x24) = ~uVar1 & *(uint *)(param_1 + 0x24);
    }
  }
  return 0;
}

