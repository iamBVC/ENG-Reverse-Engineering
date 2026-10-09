/* sub_546E10 @ 00546e10   27 bytes */

void sub_546E10(int *param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  param_1[1] = (int)param_2;
  *param_1 = iVar1;
  if (*param_2 != 0) {
    *(int **)(*param_2 + 4) = param_1;
  }
  *param_2 = (int)param_1;
  return;
}

