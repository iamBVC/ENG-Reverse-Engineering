/* sub_565B71 @ 00565b71   60 bytes */

undefined4 sub_565B71(int param_1)

{
  int iVar1;
  
  DAT_006db91c = HeapCreate((uint)(param_1 == 0),0x1000,0);
  if (DAT_006db91c != (HANDLE)0x0) {
    iVar1 = sub_565BAD();
    if (iVar1 != 0) {
      return 1;
    }
    HeapDestroy(DAT_006db91c);
  }
  return 0;
}

