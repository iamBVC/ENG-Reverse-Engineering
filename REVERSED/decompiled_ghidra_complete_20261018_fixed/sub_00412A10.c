/* sub_412A10 @ 00412a10   487 bytes */

uint sub_412A10(int param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  char cVar3;
  uint uVar4;
  
  if ((*(uint *)(param_2 + 4) & 0x1c2) != 0x1c2) {
    return *(uint *)(param_2 + 4) & 0x100;
  }
  if ((*(byte *)(param_2 + 8) & 2) == 0) {
    return 0x100;
  }
  if (((byte)*(undefined4 *)(param_2 + 0xf4) & 3) != 3) {
    return 0x100;
  }
  if (*(short *)(param_2 + 0xf8) == 0) {
    return 0x100;
  }
  if ((*(byte *)(param_2 + 0x68) & 0x10) == 0) {
    return 0x100;
  }
  if ((*(byte *)(param_2 + 0x70) & 8) == 0) {
    return 0x100;
  }
  *(byte *)(param_1 + 2) = *(byte *)(param_2 + 0x6c) & 1;
  *(byte *)(param_1 + 7) = (byte)(*(uint *)(param_2 + 0x6c) >> 0xe) & 1;
  uVar4 = *(uint *)(param_2 + 0x6c);
  *(undefined1 *)(param_1 + 6) = 1;
  *(byte *)(param_1 + 5) = ~(byte)(uVar4 >> 0xf) & 1;
  if (((*(byte *)(param_2 + 0x74) & 0x10) == 0) || ((*(byte *)(param_2 + 0x78) & 0x20) == 0)) {
    cVar1 = '\0';
  }
  else {
    cVar1 = '\x01';
  }
  *(char *)(param_1 + 0x16) = cVar1;
  if (((cVar1 == '\0') || ((*(uint *)(param_2 + 0x74) & 2) == 0)) ||
     ((*(uint *)(param_2 + 0x74) == 0x12 && (*(int *)(param_2 + 0x78) == 0x21)))) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  *(undefined1 *)(param_1 + 0x19) = uVar2;
  if (((*(byte *)(param_2 + 0x74) & 2) == 0) || ((*(byte *)(param_2 + 0x78) & 2) == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  *(undefined1 *)(param_1 + 0x17) = uVar2;
  *(byte *)(param_1 + 3) = (byte)(*(uint *)(param_2 + 0x7c) >> 4) & 1;
  if ((cVar1 == '\0') || ((*(uint *)(param_2 + 0x80) & 0xf000) == 0)) {
    cVar3 = '\0';
  }
  else {
    cVar3 = '\x01';
  }
  *(char *)(param_1 + 0x13) = cVar3;
  if ((cVar1 == '\0') || ((*(uint *)(param_2 + 0x80) & 0xc000) == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  *(undefined1 *)(param_1 + 0x14) = uVar2;
  if ((cVar3 == '\0') || ((*(uint *)(param_2 + 0x80) & 0x5000) != 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  *(undefined1 *)(param_1 + 0x1a) = uVar2;
  *(bool *)(param_1 + 0x12) = (*(byte *)(param_2 + 0x80) & 0xc) != 0;
  *(bool *)(param_1 + 0x15) = (*(uint *)(param_2 + 0x80) >> 8 & 3) != 0;
  if ((cVar1 == '\0') || ((*(byte *)(param_2 + 0x84) & 4) == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  *(undefined1 *)(param_1 + 0x18) = uVar2;
  if ((cVar1 == '\0') || ((*(byte *)(param_2 + 0x84) & 0x80) == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  *(undefined1 *)(param_1 + 0xf) = uVar2;
  *(byte *)(param_1 + 0xb) = (byte)(*(uint *)(param_2 + 0x84) >> 3) & 1;
  *(byte *)(param_1 + 8) = *(byte *)(param_2 + 0x84) & 1;
  uVar4 = *(uint *)(param_2 + 0x88);
  *(undefined1 *)(param_1 + 0xe) = 0;
  *(bool *)(param_1 + 0xd) = (uVar4 & 0x2000200) == 0x2000200;
  uVar4 = *(uint *)(param_2 + 0xf4) >> 3;
  *(byte *)(param_1 + 0x10) = (byte)uVar4 & 1;
  if (((uVar4 & 1) != 0) && ((*(byte *)(param_2 + 0x8c) & 8) != 0)) {
    *(undefined1 *)(param_1 + 0x11) = 1;
    return 1;
  }
  *(undefined1 *)(param_1 + 0x11) = 0;
  return 1;
}

