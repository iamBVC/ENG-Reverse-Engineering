/* sub_4146B0 @ 004146b0   199 bytes */

void sub_4146B0(int param_1)

{
  float fVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (DAT_005833f3 != '\0') {
    puVar2 = (undefined4 *)sub_41ED90(0x80);
    if (puVar2 != (undefined4 *)0x0) {
      puVar2[0x1d] = 0;
      puVar2[0x15] = 0;
      param_1 = param_1 << 0x18;
      puVar2[0x1c] = param_1;
      puVar2[0x14] = param_1;
      puVar2[0xc] = param_1;
      puVar2[4] = param_1;
      puVar2[0xd] = 0;
      puVar2[5] = 0;
      puVar2[0x1a] = 0;
      puVar2[0x12] = 0;
      puVar2[10] = 0;
      puVar2[2] = 0;
      puVar2[0x1b] = 0x3f800000;
      puVar2[0x13] = 0x3f800000;
      puVar2[0xb] = 0x3f800000;
      puVar2[3] = 0x3f800000;
      puVar2[0x18] = 0;
      *puVar2 = 0;
      fVar1 = (float)DAT_00583374;
      puVar2[9] = 0;
      puVar2[1] = 0;
      puVar2[0x10] = fVar1;
      puVar2[8] = fVar1;
      fVar1 = (float)DAT_00583378;
      puVar2[0x19] = fVar1;
      puVar2[0x11] = fVar1;
      puVar3 = (undefined4 *)sub_41ED90(0x20);
      if (puVar3 != (undefined4 *)0x0) {
        puVar3[1] = puVar2;
        *puVar3 = DAT_005f6ef8;
        puVar3[2] = 4;
        puVar3[3] = 0;
        puVar3[4] = 0;
        puVar3[5] = 0;
        puVar3[6] = 0;
        puVar3[7] = 0x506d;
        DAT_005f6ef8 = puVar3;
      }
    }
  }
  return;
}

