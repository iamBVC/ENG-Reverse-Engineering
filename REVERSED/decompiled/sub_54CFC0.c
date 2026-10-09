/* sub_54CFC0 @ 0054cfc0   268 bytes */

void sub_54CFC0(int param_1)

{
  int *piVar1;
  uint uVar2;
  undefined1 *local_190;
  int local_18c;
  int local_188;
  int local_184;
  int local_180;
  undefined4 local_17c;
  int *local_178;
  int local_174;
  int local_170;
  int local_16c;
  int local_164;
  int local_160;
  int local_15c;
  int local_158;
  undefined1 local_154 [260];
  int local_50;
  int local_3c;
  int local_38;
  int local_34;
  
  local_190 = local_154;
  piVar1 = *(int **)(param_1 + 0x38);
  DAT_006d9dc8 = 0;
  uVar2 = 0;
  local_18c = 0;
  local_17c = 0;
  if (*(int *)(param_1 + 4) != 0) {
    do {
      if ((*(byte *)(piVar1 + 0x11) & 2) == 0) {
        local_188 = piVar1[0xc];
        local_3c = piVar1[0xf];
        local_38 = piVar1[0x10];
        local_18c = piVar1[9];
        local_50 = piVar1[10] + piVar1[9] * 4;
        local_184 = piVar1[0xd];
        local_180 = piVar1[0xe];
        local_164 = piVar1[4];
        local_160 = piVar1[5];
        local_15c = piVar1[6];
        local_158 = piVar1[7];
        local_174 = *piVar1 << 0xc;
        local_170 = piVar1[1] << 0xc;
        local_16c = piVar1[2] << 0xc;
        local_178 = piVar1;
        local_34 = local_3c;
        sub_54BFC0(&local_190,&local_174,piVar1[8],piVar1[0xb],0);
      }
      uVar2 = uVar2 + 1;
      piVar1 = piVar1 + 0x12;
    } while (uVar2 < *(uint *)(param_1 + 4));
  }
  sub_41E1B0();
  return;
}

