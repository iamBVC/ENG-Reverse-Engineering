/* sub_54FD60 @ 0054fd60   89 bytes */

void sub_54FD60(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar1 = sub_54BC00(param_1);
  uVar2 = *(uint *)(param_1 + 0xec) & 0xfffffbd3;
  *(uint *)(param_1 + 0xec) = uVar2;
  switch(uVar1) {
  case 1:
    *(uint *)(param_1 + 0xec) = uVar2 | 8;
    return;
  case 2:
    *(uint *)(param_1 + 0xec) = uVar2 | 0x400;
    return;
  case 3:
    *(uint *)(param_1 + 0xec) = uVar2 | 0x20;
    return;
  case 4:
    break;
  default:
    *(uint *)(param_1 + 0xec) = uVar2 | 4;
  }
  return;
}

