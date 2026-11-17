/* sub_40F4F0 @ 0040f4f0   1687 bytes */

bool sub_40F4F0(void)

{
  int *piVar1;
  undefined1 *puVar2;
  char cVar3;
  BOOL BVar4;
  int iVar5;
  FARPROC pFVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  int *piVar10;
  char *pcVar11;
  char *pcVar12;
  int *piVar13;
  char local_15c [276];
  char local_48 [16];
  undefined *local_38 [2];
  int local_30;
  undefined **local_2c;
  char *local_28;
  int *local_24;
  int *local_20;
  int *local_1c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0056d6c8;
  local_10 = ExceptionList;
  local_14 = &stack0xfffffe98;
  ExceptionList = &local_10;
  puVar2 = &stack0xfffffe98;
  if ((DAT_005834d0 != '\0') &&
     (ExceptionList = &local_10, puVar2 = &stack0xfffffe98, DAT_005834d4 == 0)) {
    local_1c = (int *)0x10;
    ExceptionList = &local_10;
    BVar4 = GetComputerNameA(local_48,(LPDWORD)&local_1c);
    if (BVar4 == 0) {
      uVar7 = 0xffffffff;
      pcVar11 = s_unnamed_00571720;
      do {
        pcVar9 = pcVar11;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar9 = pcVar11 + 1;
        cVar3 = *pcVar11;
        pcVar11 = pcVar9;
      } while (cVar3 != '\0');
      uVar7 = ~uVar7;
      pcVar11 = pcVar9 + -uVar7;
      pcVar9 = local_48;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
        pcVar11 = pcVar11 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar9 = *pcVar11;
        pcVar11 = pcVar11 + 1;
        pcVar9 = pcVar9 + 1;
      }
    }
    pcVar11 = local_48;
    pcVar9 = local_15c;
    while (local_48[0] != '\0') {
      iVar5 = sub_562EA3((int)*pcVar11);
      if (iVar5 != 0) {
        *pcVar9 = *pcVar11;
        pcVar9 = pcVar9 + 1;
      }
      pcVar12 = pcVar11 + 1;
      pcVar11 = pcVar11 + 1;
      local_48[0] = *pcVar12;
    }
    uVar7 = 0xffffffff;
    pcVar11 = s__dispdiag_00571714;
    do {
      pcVar12 = pcVar11;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar12 = pcVar11 + 1;
      cVar3 = *pcVar11;
      pcVar11 = pcVar12;
    } while (cVar3 != '\0');
    uVar7 = ~uVar7;
    pcVar11 = pcVar12 + -uVar7;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar9 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar9 = pcVar9 + 1;
    }
    DAT_005834d4 = sub_562AEE(local_15c,&DAT_00571710);
    sub_40FBE0(0xffffffff,local_48,0,0);
    puVar2 = local_14;
  }
  local_14 = puVar2;
  local_8 = 0;
  if (DAT_00583410 != (int *)&DAT_00583414) {
    sub_40FD00();
  }
  DAT_00583408 = LoadLibraryA(s_ddraw_dll_00571704);
  if (DAT_00583408 == (HMODULE)0x0) {
    local_28 = s_Couldn_t_load_DirectDraw_library_005716e0;
    local_2c = &PTR_sub_413B20_0056e1c4;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_2c,&DAT_0056f000);
  }
  local_15 = 2;
  if (DAT_005834d4 != 0) {
    sub_562B75(&local_15,1,1,DAT_005834d4);
    uVar7 = 0xffffffff;
    pcVar11 = s_Enumeration_005716d4;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar3 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar3 != '\0');
    sub_562B75(s_Enumeration_005716d4,1,~uVar7,DAT_005834d4);
  }
  local_15 = 4;
  if (DAT_005834d4 != 0) {
    sub_562B75(&local_15,1,1,DAT_005834d4);
    uVar7 = 0xffffffff;
    pcVar11 = s_DDraw_Devices_005716c4;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar3 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar3 != '\0');
    sub_562B75(s_DDraw_Devices_005716c4,1,~uVar7,DAT_005834d4);
  }
  pFVar6 = GetProcAddress(DAT_00583408,s_DirectDrawEnumerateExA_005716ac);
  if (pFVar6 == (FARPROC)0x0) {
    iVar5 = DirectDrawEnumerateA(&LAB_004116b0,0);
  }
  else {
    iVar5 = DirectDrawEnumerateExA(sub_4116D0,0,7);
  }
  local_15 = 5;
  if (DAT_005834d4 != 0) {
    sub_562B75(&local_15,1,1,DAT_005834d4);
  }
  local_15 = 3;
  if (DAT_005834d4 != 0) {
    sub_562B75(&local_15,1,1,DAT_005834d4);
  }
  if (iVar5 != 0) {
    sub_413D80(s_Couldn_t_enumerate_DirectDraw_de_00571684);
    local_38[0] = &DAT_0056e1c0;
    local_30 = iVar5;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_38,&DAT_0056eff0);
  }
  if (DAT_005834d0 != '\0') {
    local_15 = 4;
    if (DAT_005834d4 != 0) {
      sub_562B75(&local_15,1,1,DAT_005834d4);
      uVar7 = 0xffffffff;
      pcVar11 = s_Initialisation_00571674;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar3 = *pcVar11;
        pcVar11 = pcVar11 + 1;
      } while (cVar3 != '\0');
      sub_562B75(s_Initialisation_00571674,1,~uVar7,DAT_005834d4);
    }
    for (local_20 = DAT_00583410; (*local_20 != 0 || (local_20[1] == 0));
        local_20 = (int *)*local_20) {
      pcVar11 = (char *)local_20[2];
      local_15 = 4;
      if ((DAT_005834d4 != 0) && (sub_562B75(&local_15,1,1,DAT_005834d4), pcVar11 != (char *)0x0)) {
        uVar7 = 0xffffffff;
        pcVar9 = pcVar11;
        do {
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          cVar3 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar3 != '\0');
        sub_562B75(pcVar11,1,~uVar7,DAT_005834d4);
      }
      for (piVar10 = (int *)local_20[7]; (*piVar10 != 0 || (piVar10[1] == 0));
          piVar10 = (int *)*piVar10) {
        pcVar11 = (char *)piVar10[2];
        local_15 = 4;
        if ((DAT_005834d4 != 0) && (sub_562B75(&local_15,1,1,DAT_005834d4), pcVar11 != (char *)0x0))
        {
          uVar7 = 0xffffffff;
          pcVar9 = pcVar11;
          do {
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            cVar3 = *pcVar9;
            pcVar9 = pcVar9 + 1;
          } while (cVar3 != '\0');
          sub_562B75(pcVar11,1,~uVar7,DAT_005834d4);
        }
        for (local_1c = (int *)piVar10[0xb]; (*local_1c != 0 || (local_1c[1] == 0));
            local_1c = (int *)*local_1c) {
          pcVar11 = (char *)local_1c[2];
          local_15 = 4;
          if ((DAT_005834d4 != 0) &&
             (sub_562B75(&local_15,1,1,DAT_005834d4), pcVar11 != (char *)0x0)) {
            uVar7 = 0xffffffff;
            pcVar9 = pcVar11;
            do {
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              cVar3 = *pcVar9;
              pcVar9 = pcVar9 + 1;
            } while (cVar3 != '\0');
            sub_562B75(pcVar11,1,~uVar7,DAT_005834d4);
          }
          for (piVar13 = (int *)local_1c[0xc];
              (local_24 = piVar13, *piVar13 != 0 || (piVar13[1] == 0)); piVar13 = (int *)*piVar13) {
            pcVar11 = (char *)piVar13[2];
            local_15 = 2;
            if ((DAT_005834d4 != 0) &&
               (sub_562B75(&local_15,1,1,DAT_005834d4), pcVar11 != (char *)0x0)) {
              uVar7 = 0xffffffff;
              pcVar9 = pcVar11;
              do {
                if (uVar7 == 0) break;
                uVar7 = uVar7 - 1;
                cVar3 = *pcVar9;
                pcVar9 = pcVar9 + 1;
              } while (cVar3 != '\0');
              sub_562B75(pcVar11,1,~uVar7,DAT_005834d4);
              piVar13 = local_24;
            }
            piVar1 = local_20;
            cVar3 = sub_410550(local_20);
            if ((((cVar3 == '\0') ||
                 (cVar3 = sub_410700(local_1c,piVar13,piVar1,piVar10), cVar3 == '\0')) ||
                (cVar3 = sub_411000(piVar10), cVar3 == '\0')) && (local_15 = 1, DAT_005834d4 != 0))
            {
              sub_562B75(&local_15,1,1,DAT_005834d4);
              uVar7 = 0xffffffff;
              pcVar11 = s_Couldn_t_open_mode_00571660;
              do {
                if (uVar7 == 0) break;
                uVar7 = uVar7 - 1;
                cVar3 = *pcVar11;
                pcVar11 = pcVar11 + 1;
              } while (cVar3 != '\0');
              sub_562B75(s_Couldn_t_open_mode_00571660,1,~uVar7,DAT_005834d4);
              piVar13 = local_24;
            }
            local_15 = 0x10;
            piVar1 = local_20 + 5;
            if (DAT_005834d4 != 0) {
              sub_562B75(&local_15,1,1,DAT_005834d4);
              uVar7 = 0xffffffff;
              pcVar11 = s_DirectDraw_Capabilities_00571648;
              do {
                if (uVar7 == 0) break;
                uVar7 = uVar7 - 1;
                cVar3 = *pcVar11;
                pcVar11 = pcVar11 + 1;
              } while (cVar3 != '\0');
              sub_562B75(s_DirectDraw_Capabilities_00571648,1,~uVar7,DAT_005834d4);
              piVar13 = local_24;
              if (piVar1 != (int *)0x0) {
                sub_562B75(piVar1,8,1,DAT_005834d4);
              }
            }
            local_15 = 0x11;
            if (DAT_005834d4 != 0) {
              sub_562B75(&local_15,1,1,DAT_005834d4);
              uVar7 = 0xffffffff;
              pcVar11 = s_Direct3D_Capabilities_00571630;
              do {
                if (uVar7 == 0) break;
                uVar7 = uVar7 - 1;
                cVar3 = *pcVar11;
                pcVar11 = pcVar11 + 1;
              } while (cVar3 != '\0');
              sub_562B75(s_Direct3D_Capabilities_00571630,1,~uVar7,DAT_005834d4);
              piVar13 = local_24;
              if (piVar10 + 4 != (int *)0x0) {
                sub_562B75(piVar10 + 4,0x1c,1,DAT_005834d4);
              }
            }
            sub_40FBE0(0xb,s_Indexed_texture_format_00571618,piVar10 + 0x16,0x20);
            sub_40FBE0(0xb,s_Normal_texture_format_00571600,piVar10 + 0x1e,0x20);
            sub_40FBE0(0xb,s_Alpha_texture_format_005715e8,piVar10 + 0x26,0x20);
            sub_40FBE0(0xb,s_Colourkey_texture_format_005715cc,piVar10 + 0x2e,0x20);
            sub_40FE10();
            sub_40FBE0(3,0,0,0);
          }
          sub_40FBE0(5,0,0,0);
        }
        sub_40FBE0(5,0,0,0);
      }
      sub_40FBE0(5,0,0,0);
    }
    sub_40FBE0(5,0,0,0);
    sub_40FBE0(0x12,s_Preferences_005715c0,&DAT_00573d28,0x1c);
  }
  sub_40FC50();
  ExceptionList = local_10;
  return DAT_00583410 != (int *)&DAT_00583414;
}

