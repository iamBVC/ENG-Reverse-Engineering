/* sub_401000 @ 00401000   115 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

byte sub_401000(float *param_1)

{
  byte bVar1;
  
  bVar1 = param_1[2] < -*param_1;
  if (param_1[2] < *param_1) {
    bVar1 = bVar1 | 2;
  }
  if (param_1[2] < -param_1[1]) {
    bVar1 = bVar1 | 4;
  }
  if (param_1[2] < param_1[1]) {
    bVar1 = bVar1 | 8;
  }
  if (param_1[2] <= _DAT_0057d70c) {
    bVar1 = bVar1 | 0x10;
  }
  if (_DAT_0057d7fc <= param_1[2]) {
    bVar1 = bVar1 | 0x20;
  }
  return bVar1;
}

