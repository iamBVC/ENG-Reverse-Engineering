/* sub_211063C0 @ 211063c0   93 bytes */

undefined4 __thiscall sub_211063C0(void *this,LPCSTR param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  LPSTR lpString1;
  undefined4 uVar3;
  
  puVar1 = (uint *)sub_211062E0(this,param_1);
  if (puVar1 == (uint *)0x0) {
    return 1;
  }
  iVar2 = lstrlenA(param_1);
  lpString1 = operator_new(iVar2 + 1);
  *(LPSTR *)this = lpString1;
  lstrcpyA(lpString1,param_1);
  uVar3 = sub_211066A0(this,puVar1);
  if (param_2 != 0) {
    sub_211064A0(this,(byte)param_2);
  }
  return uVar3;
}

