/* sub_40D020 @ 0040d020   265 bytes */

int sub_40D020(HDC param_1,HANDLE param_2,undefined4 param_3,int param_4,int param_5)

{
  HDC hdc;
  int iVar1;
  undefined1 auStack_98 [4];
  int iStack_94;
  int iStack_90;
  int iStack_88;
  int iStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  int iStack_8;
  int iStack_4;
  
  if ((param_2 != (HANDLE)0x0) && (param_1 != (HDC)0x0)) {
    (**(code **)(param_1->unused + 0x6c))();
    hdc = CreateCompatibleDC((HDC)0x0);
    if (hdc == (HDC)0x0) {
      OutputDebugStringA(s_createcompatible_dc_failed_005713b4);
    }
    SelectObject(hdc,param_2);
    GetObjectA(param_2,0x18,auStack_98);
    if (param_4 == 0) {
      param_4 = iStack_94;
    }
    if (param_5 == 0) {
      param_5 = iStack_90;
    }
    uStack_80 = 0x7c;
    uStack_7c = 6;
    (**(code **)(param_1->unused + 0x58))(param_1,&uStack_80);
    iVar1 = (**(code **)(param_1->unused + 0x44))(param_1,&stack0xffffff58);
    if (iVar1 == 0) {
      StretchBlt(param_1,0,0,iStack_84,iStack_88,hdc,iStack_8,iStack_4,param_4,param_5,0xcc0020);
      (**(code **)(param_1->unused + 0x68))(param_1,param_1);
    }
    DeleteDC(hdc);
    return iVar1;
  }
  return -0x7fffbffb;
}

