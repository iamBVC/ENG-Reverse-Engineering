/* sub_547800 @ 00547800   56 bytes */

void sub_547800(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 8);
  if (iVar1 != 0) {
    _AAL_FreeVoice_4(*(undefined4 *)(iVar1 + 0x14));
    sub_546E30(iVar1);
    sub_546E10(iVar1,param_1 + 0x1c);
    *(undefined4 *)(param_2 + 8) = 0;
  }
  return;
}

