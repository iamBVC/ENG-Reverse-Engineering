/* Selected Ghidra export at 00417fa0. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint sub_417FA0(void)

{
  DWORD DVar1;
  uint uVar2;
  
  DVar1 = timeGetTime();
  sub_562717(0x583988,&DAT_00570300,0xf - (DVar1 - _DAT_005839d0) / 1000);
  uRam00571de8 = 0x583988;
  DVar1 = timeGetTime();
  uVar2 = DVar1 - _DAT_005839d0;
  if (15000 < uVar2) {
    if (_DAT_00571e3c == 1) {
      sub_418020();
      return 0;
    }
    func_0x00418050(0);
    uVar2 = 0;
  }
  return uVar2;
}

