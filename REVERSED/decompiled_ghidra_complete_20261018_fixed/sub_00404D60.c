/* sub_404D60 @ 00404d60   68 bytes */

int sub_404D60(int *param_1,int *param_2)

{
  uint uVar1;
  
  fpatan((float10)(*param_1 - *param_2),(float10)(param_1[2] - param_2[2]));
  uVar1 = __ftol();
  return (uVar1 & 0xfff) << 0xc;
}

