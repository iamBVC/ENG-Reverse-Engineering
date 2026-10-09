/* sub_566B8C @ 00566b8c   502 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sub_566B8C(uint param_1,char *param_2,char *param_3)

{
  int *piVar1;
  byte *pbVar2;
  char cVar3;
  byte bVar4;
  BOOL BVar5;
  DWORD DVar6;
  int iVar7;
  char *pcVar8;
  DWORD local_10;
  char *local_c;
  char local_5;
  
  if (param_1 < DAT_006da8e0) {
    iVar7 = (param_1 & 0x1f) * 8;
    piVar1 = &DAT_006da7e0 + ((int)param_1 >> 5);
    bVar4 = *(byte *)((&DAT_006da7e0)[(int)param_1 >> 5] + iVar7 + 4);
    if ((bVar4 & 1) != 0) {
      local_c = (char *)0x0;
      if ((param_3 == (char *)0x0) || ((bVar4 & 2) != 0)) {
        return 0;
      }
      pcVar8 = param_2;
      if (((bVar4 & 0x48) != 0) &&
         (cVar3 = *(char *)((&DAT_006da7e0)[(int)param_1 >> 5] + iVar7 + 5), cVar3 != '\n')) {
        param_3 = (char *)((int)param_3 - 1);
        *param_2 = cVar3;
        pcVar8 = param_2 + 1;
        local_c = (char *)0x1;
        *(undefined1 *)(*piVar1 + 5 + iVar7) = 10;
      }
      BVar5 = ReadFile(*(HANDLE *)(*piVar1 + iVar7),pcVar8,(DWORD)param_3,&local_10,
                       (LPOVERLAPPED)0x0);
      if (BVar5 == 0) {
        DVar6 = GetLastError();
        if (DVar6 == 5) {
          _DAT_006da364 = 9;
          DAT_006da368 = 5;
          return -1;
        }
        if (DVar6 != 0x6d) {
          sub_568953(DVar6);
          return -1;
        }
        return 0;
      }
      bVar4 = *(byte *)(*piVar1 + 4 + iVar7);
      if ((bVar4 & 0x80) == 0) {
        return (int)local_c + local_10;
      }
      if ((local_10 == 0) || (*param_2 != '\n')) {
        bVar4 = bVar4 & 0xfb;
      }
      else {
        bVar4 = bVar4 | 4;
      }
      *(byte *)(*piVar1 + 4 + iVar7) = bVar4;
      param_3 = param_2;
      local_c = param_2 + (int)local_c + local_10;
      pcVar8 = param_2;
      if (param_2 < local_c) {
        do {
          cVar3 = *param_3;
          if (cVar3 == '\x1a') {
            pbVar2 = (byte *)(*piVar1 + 4 + iVar7);
            bVar4 = *pbVar2;
            if ((bVar4 & 0x40) == 0) {
              *pbVar2 = bVar4 | 2;
            }
            break;
          }
          if (cVar3 == '\r') {
            if (param_3 < local_c + -1) {
              if (param_3[1] == '\n') {
                param_3 = param_3 + 2;
                goto LAB_00566d22;
              }
              *pcVar8 = '\r';
              pcVar8 = pcVar8 + 1;
              param_3 = param_3 + 1;
            }
            else {
              param_3 = param_3 + 1;
              BVar5 = ReadFile(*(HANDLE *)(*piVar1 + iVar7),&local_5,1,&local_10,(LPOVERLAPPED)0x0);
              if (((BVar5 == 0) && (DVar6 = GetLastError(), DVar6 != 0)) || (local_10 == 0)) {
LAB_00566d3c:
                *pcVar8 = '\r';
LAB_00566d3f:
                pcVar8 = pcVar8 + 1;
              }
              else if ((*(byte *)(*piVar1 + 4 + iVar7) & 0x48) == 0) {
                if ((pcVar8 == param_2) && (local_5 == '\n')) {
LAB_00566d22:
                  *pcVar8 = '\n';
                  goto LAB_00566d3f;
                }
                sub_5667CA(param_1,0xffffffff,1);
                if (local_5 != '\n') goto LAB_00566d3c;
              }
              else {
                if (local_5 == '\n') goto LAB_00566d22;
                *pcVar8 = '\r';
                pcVar8 = pcVar8 + 1;
                *(char *)(*piVar1 + 5 + iVar7) = local_5;
              }
            }
          }
          else {
            *pcVar8 = cVar3;
            pcVar8 = pcVar8 + 1;
            param_3 = param_3 + 1;
          }
        } while (param_3 < local_c);
      }
      return (int)pcVar8 - (int)param_2;
    }
  }
  DAT_006da368 = 0;
  _DAT_006da364 = 9;
  return -1;
}

