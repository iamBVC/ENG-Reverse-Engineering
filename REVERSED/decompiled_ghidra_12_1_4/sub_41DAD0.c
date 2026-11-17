/* sub_41DAD0 @ 0041dad0   82 bytes */

int sub_41DAD0(int param_1)

{
  int iVar1;
  
  iVar1 = sub_41D9C0();
  if (iVar1 == 0) {
    switch(param_1) {
    case 0x4c:
    case 0x4d:
      return 0;
    case 0x4e:
      iVar1 = GetSystemMetrics(0);
      return iVar1;
    case 0x4f:
      param_1 = 1;
      break;
    case 0x50:
    case 0x51:
      return 1;
    }
    iVar1 = GetSystemMetrics(param_1);
    return iVar1;
  }
  iVar1 = (*DAT_005863cc)(param_1);
  return iVar1;
}

