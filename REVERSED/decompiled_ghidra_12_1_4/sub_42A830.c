/* sub_42A830 @ 0042a830   174 bytes */

void sub_42A830(int param_1,uint param_2,int param_3,undefined4 *param_4,int param_5)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  iVar4 = (int)*(char *)(param_1 + 0x150 + param_5);
  iVar2 = sub_428700(param_4);
  if (((iVar2 == 0) && (iVar4 != -1)) && (uVar3 = 0, param_2 != 0)) {
    param_5 = 0;
    do {
      puVar1 = DAT_006d9bd8;
      if (DAT_006d9bd8 == (undefined4 *)0x0) {
        return;
      }
      puVar5 = (undefined4 *)(&DAT_005fe230 + iVar4 * 0x34);
      puVar6 = DAT_006d9bd8 + 6;
      DAT_006d9bd8 = (undefined4 *)*DAT_006d9bd8;
      for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      *puVar1 = DAT_006d9bdc;
      if (DAT_006d9bdc != (undefined4 *)0x0) {
        DAT_006d9bdc[1] = puVar1;
      }
      DAT_006d9bdc = puVar1;
      puVar1[2] = *param_4;
      uVar3 = uVar3 + 1;
      puVar1[3] = param_4[1] + param_5;
      puVar1[4] = param_4[2];
      param_5 = param_5 + param_3;
    } while (uVar3 < param_2);
  }
  return;
}

