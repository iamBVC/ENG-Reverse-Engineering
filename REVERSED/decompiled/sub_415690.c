/* sub_415690 @ 00415690   1024 bytes */

undefined4 * sub_415690(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  UINT UVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  char local_1;
  
  local_1 = 'A';
  GetModuleFileNameA((HMODULE)0x0,(LPSTR)&DAT_00583748,0x104);
  pcVar2 = _strrchr((char *)&DAT_00583748,0x5c);
  pcVar2[1] = '\0';
  if (param_1 != (char *)0x0) {
    uVar4 = 0xffffffff;
    pcVar2 = param_1;
    do {
      pcVar9 = pcVar2;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar5 = -1;
    pcVar2 = (char *)&DAT_00583748;
    do {
      pcVar8 = pcVar2;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar8 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar8;
    } while (cVar1 != '\0');
    pcVar2 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar9 = pcVar9 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar2 = &DAT_00570334;
    do {
      pcVar9 = pcVar2;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar5 = -1;
    pcVar2 = (char *)&DAT_00583748;
    do {
      pcVar8 = pcVar2;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar8 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar8;
    } while (cVar1 != '\0');
    pcVar2 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  uVar4 = 0xffffffff;
  pcVar2 = param_2;
  do {
    pcVar9 = pcVar2;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar5 = -1;
  pcVar2 = (char *)&DAT_00583748;
  do {
    pcVar8 = pcVar2;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar8 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar8;
  } while (cVar1 != '\0');
  pcVar2 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar5 = sub_563B1A(&DAT_00583748,4);
  if (iVar5 == 0) {
    return &DAT_00583748;
  }
  pcVar2 = (char *)sub_405790(s_HDPath_00571d94,0,0);
  if (pcVar2 != (char *)0x0) {
    uVar4 = 0xffffffff;
    do {
      pcVar9 = pcVar2;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar2 = pcVar9 + -uVar4;
    pcVar9 = (char *)&DAT_00583748;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar9 = pcVar9 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar2 = (char *)&DAT_00583748;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    if (*(char *)((int)&DAT_00583744 + ~uVar4 + 2) != '\\') {
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_00570334;
      do {
        pcVar9 = pcVar2;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar2 = (char *)&DAT_00583748;
      do {
        pcVar8 = pcVar2;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar8 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar8;
      } while (cVar1 != '\0');
      pcVar2 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar9 = pcVar9 + 1;
      }
    }
    if (param_1 != (char *)0x0) {
      uVar4 = 0xffffffff;
      pcVar2 = param_1;
      do {
        pcVar9 = pcVar2;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar2 = (char *)&DAT_00583748;
      do {
        pcVar8 = pcVar2;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar8 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar8;
      } while (cVar1 != '\0');
      pcVar2 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar9 = pcVar9 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_00570334;
      do {
        pcVar9 = pcVar2;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar2 = (char *)&DAT_00583748;
      do {
        pcVar8 = pcVar2;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar8 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar8;
      } while (cVar1 != '\0');
      pcVar2 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar9 = pcVar9 + 1;
      }
    }
    uVar4 = 0xffffffff;
    pcVar2 = param_2;
    do {
      pcVar9 = pcVar2;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar5 = -1;
    pcVar2 = (char *)&DAT_00583748;
    do {
      pcVar8 = pcVar2;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar8 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar8;
    } while (cVar1 != '\0');
    pcVar2 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar9 = pcVar9 + 1;
    }
    iVar5 = sub_563B1A(&DAT_00583748,4);
    if (iVar5 == 0) {
      return &DAT_00583748;
    }
  }
  pcVar2 = (char *)sub_405790(s_CDPath_00571d8c,0,0);
  if (pcVar2 != (char *)0x0) {
    uVar4 = 0xffffffff;
    do {
      pcVar9 = pcVar2;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar2 = pcVar9 + -uVar4;
    pcVar9 = (char *)&DAT_00583748;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar9 = pcVar9 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar2 = (char *)&DAT_00583748;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    if (*(char *)((int)&DAT_00583744 + ~uVar4 + 2) != '\\') {
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_00570334;
      do {
        pcVar9 = pcVar2;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar2 = (char *)&DAT_00583748;
      do {
        pcVar8 = pcVar2;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar8 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar8;
      } while (cVar1 != '\0');
      pcVar2 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar9 = pcVar9 + 1;
      }
    }
    if (param_1 != (char *)0x0) {
      uVar4 = 0xffffffff;
      pcVar2 = param_1;
      do {
        pcVar9 = pcVar2;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar2 = (char *)&DAT_00583748;
      do {
        pcVar8 = pcVar2;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar8 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar8;
      } while (cVar1 != '\0');
      pcVar2 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar9 = pcVar9 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_00570334;
      do {
        pcVar9 = pcVar2;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar2 = (char *)&DAT_00583748;
      do {
        pcVar8 = pcVar2;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar8 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar8;
      } while (cVar1 != '\0');
      pcVar2 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar9 = pcVar9 + 1;
      }
    }
    uVar4 = 0xffffffff;
    pcVar2 = param_2;
    do {
      pcVar9 = pcVar2;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar5 = -1;
    pcVar2 = (char *)&DAT_00583748;
    do {
      pcVar8 = pcVar2;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar8 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar8;
    } while (cVar1 != '\0');
    pcVar2 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar9 = pcVar9 + 1;
    }
    iVar5 = sub_563B1A(&DAT_00583748,4);
    if (iVar5 == 0) {
      return &DAT_00583748;
    }
  }
  iVar5 = 0;
  do {
    sub_562717(&DAT_00583748,&DAT_00571d84,(int)local_1);
    UVar3 = GetDriveTypeA((LPCSTR)&DAT_00583748);
    if (UVar3 == 5) {
      if (param_1 != (char *)0x0) {
        uVar4 = 0xffffffff;
        pcVar2 = param_1;
        do {
          pcVar9 = pcVar2;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar9 = pcVar2 + 1;
          cVar1 = *pcVar2;
          pcVar2 = pcVar9;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar7 = -1;
        pcVar2 = (char *)&DAT_00583748;
        do {
          pcVar8 = pcVar2;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar8 = pcVar2 + 1;
          cVar1 = *pcVar2;
          pcVar2 = pcVar8;
        } while (cVar1 != '\0');
        pcVar2 = pcVar9 + -uVar4;
        pcVar9 = pcVar8 + -1;
        for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
          pcVar2 = pcVar2 + 4;
          pcVar9 = pcVar9 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar9 = *pcVar2;
          pcVar2 = pcVar2 + 1;
          pcVar9 = pcVar9 + 1;
        }
        uVar4 = 0xffffffff;
        pcVar2 = &DAT_00570334;
        do {
          pcVar9 = pcVar2;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar9 = pcVar2 + 1;
          cVar1 = *pcVar2;
          pcVar2 = pcVar9;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar7 = -1;
        pcVar2 = (char *)&DAT_00583748;
        do {
          pcVar8 = pcVar2;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar8 = pcVar2 + 1;
          cVar1 = *pcVar2;
          pcVar2 = pcVar8;
        } while (cVar1 != '\0');
        pcVar2 = pcVar9 + -uVar4;
        pcVar9 = pcVar8 + -1;
        for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
          pcVar2 = pcVar2 + 4;
          pcVar9 = pcVar9 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar9 = *pcVar2;
          pcVar2 = pcVar2 + 1;
          pcVar9 = pcVar9 + 1;
        }
      }
      uVar4 = 0xffffffff;
      pcVar2 = param_2;
      do {
        pcVar9 = pcVar2;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar7 = -1;
      pcVar2 = (char *)&DAT_00583748;
      do {
        pcVar8 = pcVar2;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar8 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar8;
      } while (cVar1 != '\0');
      pcVar2 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar9 = pcVar9 + 1;
      }
      iVar7 = sub_563B1A(&DAT_00583748,4);
      if (iVar7 == 0) {
        return &DAT_00583748;
      }
    }
    local_1 = local_1 + '\x01';
    iVar5 = iVar5 + 1;
    if (0x19 < iVar5) {
      return (undefined4 *)0x0;
    }
  } while( true );
}

