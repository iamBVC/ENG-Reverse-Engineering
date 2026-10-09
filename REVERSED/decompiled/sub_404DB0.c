/* sub_404DB0 @ 00404db0   212 bytes */

void sub_404DB0(int *param_1,int *param_2,int *param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  unkbyte10 extraout_ST0;
  
  fpatan((float10)(*param_1 - *param_2),(float10)(param_1[2] - param_2[2]));
  uVar1 = __ftol();
  *param_3 = (uVar1 & 0xfff) << 0xc;
  iVar2 = __ftol();
  fpatan(extraout_ST0,(float10)iVar2);
  uVar1 = __ftol();
  *param_4 = (uVar1 & 0xfff) << 0xc;
  return;
}

