/* _AAL_RegisterTimer@12 @ 21102b00   36 bytes */

int _AAL_RegisterTimer_12(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  
                    /* 0x2b00  56  _AAL_RegisterTimer@12 */
  iVar1 = -1;
  if (DAT_211155b0 != (void *)0x0) {
    iVar1 = sub_21109C50(DAT_211155b0,param_1,param_2,param_3);
  }
  return iVar1;
}

