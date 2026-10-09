/* sub_405960 @ 00405960   401 bytes */

undefined4 sub_405960(undefined4 param_1)

{
  char cVar1;
  HKEY hKey;
  LPCSTR lpSubKey;
  LSTATUS LVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  HKEY in_stack_00001014;
  char *in_stack_00001018;
  REGSAM in_stack_0000101c;
  
  sub_562840();
  uVar3 = 0xffffffff;
  do {
    pcVar7 = in_stack_00001018;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = in_stack_00001018 + 1;
    cVar1 = *in_stack_00001018;
    in_stack_00001018 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar7 = pcVar7 + -uVar3;
  pcVar8 = &stack0x00000810;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  lpSubKey = (LPCSTR)sub_56279D();
  uVar3 = 0;
  do {
    if (lpSubKey == (LPCSTR)0x0) {
      return (&param_1)[uVar3];
    }
    uVar4 = (uint)(uVar3 == 0);
    LVar2 = RegOpenKeyExA((HKEY)(&param_1)[uVar3],lpSubKey,0,in_stack_0000101c,
                          (PHKEY)(&param_1 + uVar4));
    if (LVar2 != 0) {
      if (in_stack_00001014 == (HKEY)0x80000002) {
        uVar5 = 0xffffffff;
        pcVar7 = s_HKEY_LOCAL_MACHINE_00570320;
        do {
          pcVar8 = pcVar7;
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        uVar5 = ~uVar5;
        pcVar7 = pcVar8 + -uVar5;
        pcVar8 = &stack0x00000010;
        for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar8 = pcVar8 + 4;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *pcVar8 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        }
      }
      else if (in_stack_00001014 == (HKEY)0x80000001) {
        uVar5 = 0xffffffff;
        pcVar7 = s_HKEY_CURRENT_USER_0057030c;
        do {
          pcVar8 = pcVar7;
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        uVar5 = ~uVar5;
        pcVar7 = pcVar8 + -uVar5;
        pcVar8 = &stack0x00000010;
        for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar8 = pcVar8 + 4;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *pcVar8 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        }
      }
      else {
        sub_562717();
      }
      LVar2 = RegCreateKeyExA((HKEY)(&param_1)[uVar3],lpSubKey,0,&DAT_0057f834,0,in_stack_0000101c,
                              (LPSECURITY_ATTRIBUTES)0x0,(PHKEY)(&param_1 + uVar4),
                              (LPDWORD)&stack0x0000000c);
      if (LVar2 != 0) {
        return 0;
      }
    }
    hKey = (HKEY)(&param_1)[uVar3];
    if (hKey != in_stack_00001014) {
      RegCloseKey(hKey);
    }
    lpSubKey = (LPCSTR)sub_56279D();
    uVar3 = uVar4;
  } while( true );
}

