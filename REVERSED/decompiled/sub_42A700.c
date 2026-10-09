/* sub_42A700 @ 0042a700   289 bytes */

void sub_42A700(int param_1,uint param_2,int param_3,undefined4 *param_4,uint param_5)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  
  iVar5 = (int)*(char *)(param_1 + 0x150 + param_5);
  iVar2 = sub_428700(param_4);
  if (((iVar2 == 0) && (iVar5 != -1)) && (param_2 != 0)) {
    param_1 = 0;
    param_5 = 0;
    do {
      puVar1 = DAT_006d9bd8;
      if (DAT_006d9bd8 == (undefined4 *)0x0) {
        return;
      }
      uVar3 = sub_563C89();
      uVar4 = sub_563C89();
      DAT_006d9bd8 = (undefined4 *)*DAT_006d9bd8;
      piVar6 = (int *)(&DAT_005fe230 + iVar5 * 0x34);
      piVar7 = puVar1 + 6;
      for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar7 = *piVar6;
        piVar6 = piVar6 + 1;
        piVar7 = piVar7 + 1;
      }
      *puVar1 = DAT_006d9bdc;
      if (DAT_006d9bdc != (undefined4 *)0x0) {
        DAT_006d9bdc[1] = puVar1;
      }
      DAT_006d9bdc = puVar1;
      puVar1[2] = *param_4;
      puVar1[3] = param_4[1];
      puVar1[4] = param_4[2];
      puVar1[5] = param_4[3];
      puVar1[3] = puVar1[3] + param_1;
      puVar1[7] = -(uVar4 & 0x1f);
      puVar1[8] = (uVar4 & 0x3f) - (uVar3 & 0x3f);
      param_5 = param_5 + 1;
      param_1 = param_1 + param_3;
      puVar1[6] = (uVar3 & 0x3f) - (uVar4 & 0x3f);
    } while (param_5 < param_2);
  }
  return;
}

