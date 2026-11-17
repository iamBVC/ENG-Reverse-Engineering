/* sub_412D70 @ 00412d70   30 bytes */

int sub_412D70(undefined4 param_1,int param_2)

{
  uint uVar1;
  uint3 uVar2;
  
  uVar1 = *(uint *)(param_2 + 4);
  uVar2 = (uint3)(uVar1 >> 8);
  if ((uVar1 & 0x20) == 0) {
    return (uint)uVar2 << 8;
  }
  if ((uVar1 & 0x10) != 0) {
    return (uint)uVar2 << 8;
  }
  return CONCAT31(uVar2,(uVar1 & 0x2001) == 0);
}

