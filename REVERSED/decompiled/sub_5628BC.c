/* sub_5628BC @ 005628bc   47 bytes */

void sub_5628BC(LPVOID param_1)

{
  int iVar1;
  
  if (param_1 != (LPVOID)0x0) {
    iVar1 = sub_565BEB(param_1);
    if (iVar1 != 0) {
      sub_565C16(iVar1);
      return;
    }
    HeapFree(DAT_006db91c,0,param_1);
  }
  return;
}

