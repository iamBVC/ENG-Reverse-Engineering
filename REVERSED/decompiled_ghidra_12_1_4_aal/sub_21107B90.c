/* sub_21107B90 @ 21107b90   125 bytes */

bool sub_21107B90(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int *param_5
                 ,undefined4 param_6,int *param_7)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    return false;
  }
  _AAL_Lock_0();
  while( true ) {
    iVar1 = (**(code **)(*param_1 + 0x2c))(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    if (iVar1 != -0x7787ff6a) break;
    (**(code **)(*param_1 + 0x50))(param_1);
  }
  _AAL_Unlock_0();
  if (iVar1 != 0) {
    return false;
  }
  return (bool)('\x01' - (*param_5 + *param_7 != 0));
}

