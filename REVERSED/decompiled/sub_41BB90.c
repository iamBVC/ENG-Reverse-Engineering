/* sub_41BB90 @ 0041bb90   184 bytes */

void sub_41BB90(int param_1,float *param_2)

{
  if (*(int *)(param_1 + 0x68) == 1) {
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + 0x2c) * *param_2 +
         param_2[8] * *(float *)(param_1 + 0x34) + param_2[4] * *(float *)(param_1 + 0x30);
    *(float *)(param_1 + 0x48) =
         param_2[9] * *(float *)(param_1 + 0x34) +
         param_2[5] * *(float *)(param_1 + 0x30) + param_2[1] * *(float *)(param_1 + 0x2c);
    *(float *)(param_1 + 0x4c) =
         param_2[10] * *(float *)(param_1 + 0x34) +
         param_2[6] * *(float *)(param_1 + 0x30) + param_2[2] * *(float *)(param_1 + 0x2c);
  }
  else if (*(int *)(param_1 + 0x68) == 2) {
    *(float *)(param_1 + 0x38) =
         *(float *)(param_1 + 0x20) * *param_2 +
         param_2[4] * *(float *)(param_1 + 0x24) + param_2[8] * *(float *)(param_1 + 0x28) +
         param_2[0xc];
    *(float *)(param_1 + 0x3c) =
         param_2[1] * *(float *)(param_1 + 0x20) +
         param_2[5] * *(float *)(param_1 + 0x24) + param_2[9] * *(float *)(param_1 + 0x28) +
         param_2[0xd];
    *(float *)(param_1 + 0x40) =
         param_2[2] * *(float *)(param_1 + 0x20) +
         param_2[6] * *(float *)(param_1 + 0x24) + param_2[10] * *(float *)(param_1 + 0x28) +
         param_2[0xe];
    return;
  }
  return;
}

