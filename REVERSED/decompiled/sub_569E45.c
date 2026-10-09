/* sub_569E45 @ 00569e45   200 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint sub_569E45(LPWSTR param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  
  if ((param_2 != (byte *)0x0) && (param_3 != 0)) {
    bVar1 = *param_2;
    if (bVar1 != 0) {
      if (DAT_006da3f4 == 0) {
        if (param_1 != (LPWSTR)0x0) {
          *param_1 = (ushort)bVar1;
        }
        return 1;
      }
      if ((PTR_DAT_0057c804[(uint)bVar1 * 2 + 1] & 0x80) == 0) {
        iVar2 = MultiByteToWideChar(DAT_006da404,9,(LPCSTR)param_2,1,param_1,
                                    (uint)(param_1 != (LPWSTR)0x0));
        if (iVar2 != 0) {
          return 1;
        }
      }
      else {
        if (1 < (int)DAT_0057ca10) {
          if ((int)param_3 < (int)DAT_0057ca10) {
            _DAT_006da364 = 0x2a;
            return 0xffffffff;
          }
          iVar2 = MultiByteToWideChar(DAT_006da404,9,(LPCSTR)param_2,DAT_0057ca10,param_1,
                                      (uint)(param_1 != (LPWSTR)0x0));
          if (iVar2 != 0) {
            return DAT_0057ca10;
          }
        }
        if ((DAT_0057ca10 <= param_3) && (param_2[1] != 0)) {
          return DAT_0057ca10;
        }
      }
      _DAT_006da364 = 0x2a;
      return 0xffffffff;
    }
    if (param_1 != (LPWSTR)0x0) {
      *param_1 = L'\0';
    }
  }
  return 0;
}

