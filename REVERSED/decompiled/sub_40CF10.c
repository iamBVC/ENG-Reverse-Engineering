/* sub_40CF10 @ 0040cf10   267 bytes */

undefined4 sub_40CF10(int *param_1,LPCSTR param_2,int param_3,int param_4)

{
  HMODULE hInst;
  HANDLE h;
  int iVar1;
  undefined4 unaff_EDI;
  int *piVar2;
  LPCSTR name;
  UINT type;
  int cy;
  UINT fuLoad;
  undefined1 local_98 [4];
  int local_94 [26];
  undefined4 local_2c;
  undefined1 local_18 [24];
  
  if (param_1 == (int *)0x0) {
    return 0;
  }
  fuLoad = 0x2000;
  type = 0;
  name = param_2;
  iVar1 = param_3;
  cy = param_4;
  hInst = GetModuleHandleA((LPCSTR)0x0);
  h = LoadImageA(hInst,name,type,iVar1,cy,fuLoad);
  if (h == (HANDLE)0x0) {
    h = LoadImageA((HINSTANCE)0x0,param_2,0,param_3,param_4,0x2010);
    if (h == (HANDLE)0x0) {
      return 0;
    }
  }
  GetObjectA(h,0x18,local_18);
  piVar2 = local_94;
  for (iVar1 = 0x1f; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  local_94[0] = 0x7c;
  local_94[1] = 7;
  local_2c = 0x40;
  local_94[3] = param_3;
  local_94[2] = param_4;
  iVar1 = (**(code **)(*param_1 + 0x18))(param_1,local_94,local_98,0);
  if (iVar1 != 0) {
    return 0;
  }
  sub_40D020(unaff_EDI,h,0,0,0,0);
  DeleteObject(h);
  return unaff_EDI;
}

