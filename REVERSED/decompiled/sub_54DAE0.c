/* sub_54DAE0 @ 0054dae0   28 bytes */

uint sub_54DAE0(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = param_1 - param_2 & 0xffffff;
  if (0x7ff000 < uVar1) {
    uVar1 = uVar1 - 0x1000000;
  }
  return uVar1;
}

