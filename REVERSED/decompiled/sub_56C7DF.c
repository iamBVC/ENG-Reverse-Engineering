/* sub_56C7DF @ 0056c7df   326 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sub_56C7DF(uint param_1,int param_2)

{
  int iVar1;
  HANDLE hFile;
  BOOL BVar2;
  int iVar3;
  undefined1 local_1004 [4060];
  undefined4 uStackY_28;
  uint uStackY_24;
  uint uStackY_20;
  
  sub_562840();
  iVar3 = 0;
  if ((param_1 < DAT_006da8e0) &&
     ((*(byte *)((&DAT_006da7e0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    iVar1 = sub_5667CA();
    if ((iVar1 != -1) && (iVar1 = sub_5667CA(), iVar1 != -1)) {
      param_2 = param_2 - iVar1;
      if (param_2 < 1) {
        if (param_2 < 0) {
          uStackY_20 = 0x56c8ce;
          sub_5667CA();
          uStackY_20 = param_1;
          uStackY_24 = 0x56c8d4;
          hFile = (HANDLE)sub_56A73D();
          BVar2 = SetEndOfFile(hFile);
          iVar3 = (BVar2 != 0) - 1;
          if (iVar3 == -1) {
            _DAT_006da364 = 0xd;
            DAT_006da368 = GetLastError();
          }
        }
      }
      else {
        uStackY_20 = 0x56c864;
        _memset(local_1004,0,0x1000);
        uStackY_20 = 0x8000;
        uStackY_24 = param_1;
        uStackY_28 = 0x56c86f;
        sub_56D020();
        do {
          uStackY_20 = 0x56c88e;
          iVar1 = sub_5672C8();
          if (iVar1 == -1) {
            if (DAT_006da368 == 5) {
              _DAT_006da364 = 0xd;
            }
            iVar3 = -1;
            break;
          }
          param_2 = param_2 - iVar1;
        } while (0 < param_2);
        sub_56D020();
      }
      uStackY_20 = 0x56c90c;
      sub_5667CA();
      return iVar3;
    }
  }
  else {
    _DAT_006da364 = 9;
  }
  return -1;
}

