/* sub_402840 @ 00402840   208 bytes */

undefined4 sub_402840(int param_1,float *param_2,uint *param_3)

{
  uint uVar1;
  float *pfVar2;
  float *pfVar3;
  uint local_4;
  
  local_4 = 0xffffffff;
  *param_3 = 0;
  pfVar2 = (float *)&DAT_0057dc78;
  pfVar3 = (float *)(param_1 + 0x10);
  do {
    pfVar2[-2] = pfVar3[1] * param_2[8] + *pfVar3 * param_2[4] + *param_2 * pfVar3[-1] +
                 param_2[0xc];
    pfVar2[-1] = param_2[1] * pfVar3[-1] + *pfVar3 * param_2[5] + pfVar3[1] * param_2[9] +
                 param_2[0xd];
    *pfVar2 = param_2[2] * pfVar3[-1] + param_2[10] * pfVar3[1] + *pfVar3 * param_2[6] +
              param_2[0xe];
    pfVar2[1] = param_2[0xb] * pfVar3[1] + *pfVar3 * param_2[7] + param_2[3] * pfVar3[-1] +
                param_2[0xf];
    uVar1 = sub_401080(pfVar2 + -2);
    pfVar2 = pfVar2 + 9;
    local_4 = local_4 & uVar1;
    pfVar3 = pfVar3 + 3;
    *param_3 = *param_3 | uVar1;
  } while ((int)pfVar2 < 0x57dd98);
  return CONCAT31((int3)(local_4 >> 8),local_4 == 0);
}

