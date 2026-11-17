/* entry @ 00563ee0   235 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  DWORD DVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  HMODULE pHVar5;
  undefined4 uVar6;
  _STARTUPINFOA local_60;
  undefined1 *local_1c;
  undefined4 *local_18;
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0056e788;
  puStack_10 = &LAB_00563e08;
  pvStack_14 = ExceptionList;
  local_1c = &stack0xffffff88;
  ExceptionList = &pvStack_14;
  DVar1 = GetVersion();
  _DAT_006da37c = DVar1 >> 8 & 0xff;
  _DAT_006da378 = DVar1 & 0xff;
  _DAT_006da374 = _DAT_006da378 * 0x100 + _DAT_006da37c;
  _DAT_006da370 = DVar1 >> 0x10;
  iVar2 = sub_565B71(0);
  if (iVar2 == 0) {
    sub_563FFB(0x1c);
  }
  local_8 = 0;
  sub_5687A8();
  DAT_006db920 = GetCommandLineA();
  DAT_006da3b0 = sub_5690B3();
  sub_568E66();
  sub_568DAD();
  sub_563B87();
  local_60.dwFlags = 0;
  GetStartupInfoA(&local_60);
  uVar3 = sub_568D55();
  if ((local_60.dwFlags & 1) == 0) {
    uVar4 = 10;
  }
  else {
    uVar4 = (uint)local_60.wShowWindow;
  }
  uVar6 = 0;
  pHVar5 = GetModuleHandleA((LPCSTR)0x0);
  uVar3 = sub_41D350(pHVar5,uVar6,uVar3,uVar4);
  sub_563BB4(uVar3);
  sub_568BD1(*(undefined4 *)*local_18,local_18);
  return;
}

