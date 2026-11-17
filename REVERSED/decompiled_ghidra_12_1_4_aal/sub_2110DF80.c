/* sub_2110DF80 @ 2110df80   60 bytes */

undefined4 __cdecl sub_2110DF80(int param_1)

{
  int iVar1;
  
  DAT_21115b44 = HeapCreate((uint)(param_1 == 0),0x1000,0);
  if (DAT_21115b44 != (HANDLE)0x0) {
    iVar1 = sub_2110E7DE();
    if (iVar1 != 0) {
      return 1;
    }
    HeapDestroy(DAT_21115b44);
  }
  return 0;
}

