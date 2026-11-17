/* sub_42A8E0 @ 0042a8e0   234 bytes */

void sub_42A8E0(int param_1,uint param_2,int param_3,undefined4 *param_4,undefined4 *param_5,
               uint param_6)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  iVar4 = (int)*(char *)(param_1 + 0x150 + param_6);
  iVar3 = sub_428700(param_4);
  if (((iVar3 == 0) && (iVar4 != -1)) && (param_2 != 0)) {
    param_1 = 0;
    param_6 = 0;
    do {
      puVar2 = DAT_006d9bd8;
      if (DAT_006d9bd8 == (undefined4 *)0x0) {
        return;
      }
      puVar1 = DAT_006d9bd8 + 6;
      puVar5 = (undefined4 *)(&DAT_005fe230 + iVar4 * 0x34);
      puVar6 = puVar1;
      DAT_006d9bd8 = (undefined4 *)*DAT_006d9bd8;
      for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      *puVar2 = DAT_006d9bdc;
      if (DAT_006d9bdc != (undefined4 *)0x0) {
        DAT_006d9bdc[1] = puVar2;
      }
      DAT_006d9bdc = puVar2;
      puVar2[2] = *param_4;
      puVar2[3] = param_4[1] + param_1;
      puVar2[4] = param_4[2];
      *puVar1 = *param_5;
      puVar2[7] = param_5[1];
      puVar2[8] = param_5[2];
      param_1 = param_1 + param_3;
      param_6 = param_6 + 1;
    } while (param_6 < param_2);
  }
  return;
}

