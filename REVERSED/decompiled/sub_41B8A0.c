/* sub_41B8A0 @ 0041b8a0   358 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sub_41B8A0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5,undefined4 param_6,undefined4 param_7,float param_8,float param_9,
              undefined4 param_10)

{
  float fVar1;
  int iVar2;
  float fVar3;
  
  iVar2 = sub_41EF00(0x70);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0x14) = param_3;
    *(int *)(iVar2 + 0x68) = param_1;
    *(undefined1 *)(iVar2 + 0x6c) = 0;
    *(undefined4 *)(iVar2 + 0x10) = param_2;
    *(undefined4 *)(iVar2 + 0x18) = param_4;
    sub_41BEE0();
    if (param_1 == 1) {
      *(undefined4 *)(iVar2 + 0x2c) = param_5;
      *(undefined4 *)(iVar2 + 0x30) = param_6;
      *(undefined4 *)(iVar2 + 0x34) = param_7;
      fVar3 = *(float *)(iVar2 + 0x34) * *(float *)(iVar2 + 0x34) +
              *(float *)(iVar2 + 0x30) * *(float *)(iVar2 + 0x30) +
              *(float *)(iVar2 + 0x2c) * *(float *)(iVar2 + 0x2c);
      fVar1 = fVar3 * _DAT_0056e158;
      fVar3 = (float)(0x5f3759df - ((int)fVar3 >> 1));
      fVar3 = (_DAT_0056e184 - fVar3 * fVar3 * fVar1) * fVar3;
      fVar3 = (_DAT_0056e184 - fVar3 * fVar3 * fVar1) * fVar3;
      *(float *)(iVar2 + 0x2c) = fVar3 * *(float *)(iVar2 + 0x2c);
      *(float *)(iVar2 + 0x30) = fVar3 * *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x34) = fVar3 * *(float *)(iVar2 + 0x34);
      *(undefined4 *)(iVar2 + 0x44) = *(undefined4 *)(iVar2 + 0x2c);
      *(undefined4 *)(iVar2 + 0x48) = *(undefined4 *)(iVar2 + 0x30);
      *(undefined4 *)(iVar2 + 0x4c) = *(undefined4 *)(iVar2 + 0x34);
    }
    else if (param_1 == 2) {
      *(undefined4 *)(iVar2 + 0x38) = param_5;
      *(undefined4 *)(iVar2 + 0x20) = param_5;
      *(float *)(iVar2 + 0x54) = param_8 * param_8;
      *(undefined4 *)(iVar2 + 0x24) = param_6;
      *(undefined4 *)(iVar2 + 0x3c) = param_6;
      *(float *)(iVar2 + 0x5c) = param_8;
      *(undefined4 *)(iVar2 + 0x40) = param_7;
      *(float *)(iVar2 + 0x50) = param_9 * param_9;
      *(undefined4 *)(iVar2 + 0x28) = param_7;
      *(float *)(iVar2 + 0x58) = param_9;
      if (param_9 - param_8 != _DAT_0056e00c) {
        *(float *)(iVar2 + 0x60) = _DAT_0056e008 / (param_9 - param_8);
      }
      *(undefined4 *)(iVar2 + 100) = param_10;
      return iVar2;
    }
  }
  return iVar2;
}

