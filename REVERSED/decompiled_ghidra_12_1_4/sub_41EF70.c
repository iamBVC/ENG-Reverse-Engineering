/* sub_41EF70 @ 0041ef70   322 bytes */

HRESULT sub_41EF70(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  HRESULT HVar1;
  LPCSTR pCStack_10;
  
  *param_3 = 0;
  HVar1 = CoCreateInstance((IID *)&DAT_0056e5ec,(LPUNKNOWN)0x0,1,(IID *)&DAT_0056e5fc,&DAT_005865e0)
  ;
  if (HVar1 < 0) {
    sub_414600();
  }
  else {
    HVar1 = (**(code **)(*DAT_005865e0 + 0x30))(DAT_005865e0);
    if (HVar1 < 0) {
      sub_414600();
    }
    else {
      HVar1 = (**(code **)(*DAT_005865e0 + 0x3c))(DAT_005865e0,param_2);
      if (HVar1 < 0) {
        sub_414600();
      }
      else {
        (**(code **)(*DAT_005865e0 + 0x3c))(DAT_005865e0,0);
        MultiByteToWideChar(0,0,pCStack_10,-1,(LPWSTR)&stack0xfffffde4,0x104);
        HVar1 = (**(code **)(*DAT_005865e0 + 0x40))(DAT_005865e0,&stack0xfffffde4,0);
        if (HVar1 < 0) {
          sub_414600();
        }
        else {
          *param_3 = DAT_005865e0;
          (**(code **)(*DAT_005865e0 + 4))();
        }
      }
    }
  }
  if ((DAT_005865e0 == (int *)0x0) && (sub_414600(), DAT_005865e0 == (int *)0x0)) {
    return HVar1;
  }
  (**(code **)(*DAT_005865e0 + 8))();
  return HVar1;
}

