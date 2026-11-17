/* sub_546170 @ 00546170   109 bytes */

uint sub_546170(undefined4 param_1,char param_2,undefined4 param_3)

{
  int iVar1;
  uint local_4;
  
  local_4 = 0xffffffff;
  if (DAT_005834dc == 0) {
    return 0xff;
  }
  if (param_2 == -1) {
    return 0xff;
  }
  iVar1 = sub_548760(DAT_006d9498,(int)param_2);
  if (iVar1 != 0) {
    iVar1 = sub_5487A0(iVar1,param_1,param_3,&local_4);
    if (iVar1 != 0) {
      sub_5489C0(DAT_006d9498 + 0x10,iVar1);
    }
  }
  return local_4 & 0xff;
}

