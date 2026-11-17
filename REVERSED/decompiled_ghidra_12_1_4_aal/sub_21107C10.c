/* sub_21107C10 @ 21107c10   86 bytes */

bool sub_21107C10(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    return false;
  }
  _AAL_Lock_0();
  while( true ) {
    iVar1 = (**(code **)(*param_1 + 0x4c))(param_1,param_2,param_3,param_4,param_5);
    if (iVar1 != -0x7787ff6a) break;
    (**(code **)(*param_1 + 0x50))(param_1);
  }
  _AAL_Unlock_0();
  return iVar1 == 0;
}

