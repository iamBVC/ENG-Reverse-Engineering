/* sub_401080 @ 00401080   111 bytes */

byte sub_401080(float *param_1)

{
  byte bVar1;
  
  bVar1 = param_1[3] <= -*param_1;
  if (param_1[3] <= *param_1) {
    bVar1 = bVar1 | 2;
  }
  if (param_1[3] <= param_1[1]) {
    bVar1 = bVar1 | 8;
  }
  if (param_1[3] <= -param_1[1]) {
    bVar1 = bVar1 | 4;
  }
  if (param_1[3] <= -param_1[2]) {
    bVar1 = bVar1 | 0x10;
  }
  if (param_1[3] <= param_1[2]) {
    bVar1 = bVar1 | 0x20;
  }
  return bVar1;
}

