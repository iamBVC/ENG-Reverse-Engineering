/* AAL_SetError @ 21102a80   110 bytes */

void __cdecl AAL_SetError(LPCSTR param_1)

{
  int iVar1;
  CHAR local_100 [256];
  
                    /* 0x2a80  63  AAL_SetError */
  if (DAT_211155b8 != (LPSTR)0x0) {
    sub_2110D4F4(DAT_211155b8);
    DAT_211155b8 = (LPSTR)0x0;
  }
  if (param_1 != (LPCSTR)0x0) {
    wvsprintfA(local_100,param_1,&stack0x00000008);
    iVar1 = lstrlenA(local_100);
    DAT_211155b8 = operator_new(iVar1 + 1);
    lstrcpyA(DAT_211155b8,local_100);
  }
  return;
}

