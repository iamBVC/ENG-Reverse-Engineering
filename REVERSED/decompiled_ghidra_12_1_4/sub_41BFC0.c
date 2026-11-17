/* sub_41BFC0 @ 0041bfc0   62 bytes */

int * sub_41BFC0(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (*param_1 == param_2) {
    piVar1 = (int *)param_1[1];
    param_1[1] = 0;
    sub_562941(param_1);
    return piVar1;
  }
  if (param_1[1] != 0) {
    iVar2 = sub_41BFC0(param_1[1],param_2);
    param_1[1] = iVar2;
  }
  return param_1;
}

