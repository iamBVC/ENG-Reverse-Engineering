/* sub_43AC00 @ 0043ac00   217 bytes */

int sub_43AC00(int param_1,undefined4 *param_2,int param_3,uint param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  if ((DAT_006d8498 & 1) == 0) {
    DAT_006d8498 = DAT_006d8498 | 1;
    sub_5626AD(&DAT_0043ace0);
  }
  param_4 = param_4 & 0xf;
  iVar4 = 0;
  iVar3 = 0;
  puVar1 = &DAT_006d7c80;
  do {
    if (param_4 == 0) {
      param_3 = param_3 + -2;
      if (0 < param_3) {
        puVar1 = (undefined4 *)(param_1 + 0x40);
        puVar2 = param_2 + 0x10;
        iVar4 = param_3;
        do {
          puVar5 = param_2;
          puVar6 = puVar1 + -0x10;
          for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar6 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar6 = puVar6 + 1;
          }
          puVar5 = puVar2 + -8;
          puVar6 = puVar1 + -8;
          for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar6 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar6 = puVar6 + 1;
          }
          iVar4 = iVar4 + -1;
          puVar5 = puVar2;
          puVar6 = puVar1;
          for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar6 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar6 = puVar6 + 1;
          }
          puVar1 = puVar1 + 0x18;
          puVar2 = puVar2 + 8;
        } while (iVar4 != 0);
      }
      return param_3 * 3;
    }
    puVar2 = puVar1;
    if ((param_4 & 1) != 0) {
      param_3 = sub_43A810(iVar3,param_2,param_3,puVar1,0);
      if (param_3 < 3) {
        return 0;
      }
      iVar4 = 1 - iVar4;
      puVar2 = &DAT_006d7c80 + iVar4 * 0x50;
      param_2 = puVar1;
    }
    iVar3 = iVar3 + 1;
    param_4 = (int)param_4 >> 1;
    puVar1 = puVar2;
  } while( true );
}

