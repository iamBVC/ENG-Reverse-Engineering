/* sub_426740 @ 00426740   156 bytes */

void sub_426740(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  ulonglong uVar1;
  char *pcVar2;
  uint uVar3;
  
  uVar3 = param_3;
  pcVar2 = (char *)&param_3;
  if (param_3 < 100) {
    if (9 < param_3) {
      param_3 = CONCAT31(param_3._1_3_,(char)(param_3 / 10) + '0');
      uVar3 = uVar3 % 10;
      pcVar2 = (char *)((int)&param_3 + 1);
    }
  }
  else {
    uVar3 = param_3 / 100;
    uVar1 = (ulonglong)param_3;
    param_3._0_2_ = CONCAT11((char)((uVar1 % 100) / 10) + '0',(char)uVar3 + '0');
    pcVar2 = (char *)((int)&param_3 + 2);
    uVar3 = (uint)((uVar1 % 100) % 10);
  }
  *pcVar2 = (char)uVar3 + '0';
  pcVar2[1] = '\0';
  sub_4266F0(&param_3,param_1,param_2,param_4);
  return;
}

