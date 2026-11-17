/* sub_5645F3 @ 005645f3   41 bytes */

SIZE_T sub_5645F3(LPCVOID param_1)

{
  int iVar1;
  SIZE_T SVar2;
  
  iVar1 = sub_565BEB(param_1);
  if (iVar1 != 0) {
    return *(int *)((int)param_1 + -4) - 9;
  }
  SVar2 = HeapSize(DAT_006db91c,0,param_1);
  return SVar2;
}

