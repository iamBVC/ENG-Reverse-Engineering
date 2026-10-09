/* sub_41D350 @ 0041d350   1491 bytes */

undefined4 sub_41D350(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  char *_Str1;
  void *pvVar5;
  BOOL BVar6;
  bool bVar7;
  LPCSTR lpText;
  undefined4 uVar8;
  tagMSG local_50;
  LARGE_INTEGER local_34 [2];
  tagPOINT local_24;
  LARGE_INTEGER local_1c;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0056d8fe;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffa4;
  ExceptionList = &local_10;
  cVar3 = sub_41DC10();
  if (cVar3 == '\0') {
    iVar4 = sub_415690(0,s_111_cor_00572564);
    if (iVar4 == 0) {
      lpText = (&PTR_s_Inserire_il_CD_del_gioco_per_com_0057ba3c)[DAT_00584f04];
    }
    else {
      _Str1 = (char *)sub_56279D(param_3,&DAT_00572560);
      while (_Str1 != (char *)0x0) {
        iVar4 = __strcmpi(_Str1,s__display_diagnostics_00572548);
        if (iVar4 == 0) {
          DAT_005834d0 = 1;
        }
        _Str1 = (char *)sub_56279D(0,&DAT_00572560);
      }
      sub_41C050();
      cVar3 = sub_556340();
      if (cVar3 == '\0') {
        lpText = (&PTR_DAT_0057ba40)[DAT_00584f04];
      }
      else {
        sub_41D9C0();
        sub_415690(&DAT_00570348,s_DEFANIM_WAD_0057253c);
        cVar3 = sub_41DC40(param_1);
        if (cVar3 == '\0') {
          lpText = (&PTR_s_Impossibile_avviare_il_gioco_0057ba44)[DAT_00584f04];
        }
        else {
          local_8 = 0;
          cVar3 = sub_40F4F0();
          if (cVar3 == '\0') {
            lpText = (&PTR_s_Impossibile_avviare_Direct_Draw_0057ba48)[DAT_00584f04];
          }
          else {
            cVar3 = sub_40FF40();
            if (cVar3 == '\0') {
              lpText = (&PTR_s__Le_follie_dell_Imperatore__di_D_0057ba30)[DAT_00584f04];
            }
            else {
              local_8 = 0xffffffff;
              cVar3 = sub_40E6F0(DAT_005855d0,DAT_005855d4);
              if (cVar3 == '\0') {
                lpText = (&PTR_s_Impossibile_avviare_DirectInput_0057ba50)[DAT_00584f04];
              }
              else {
                sub_41ED50();
                DAT_0057f910 = 0x3d4ccccd;
                sub_424590();
                sub_410430();
                sub_410480(DAT_00573d38,DAT_00573d3c,DAT_00573d40);
                DAT_0057f93c = 1;
                DAT_00581129 = '\x01';
                iVar4 = ShowCursor(0);
                while (0 < iVar4) {
                  iVar4 = ShowCursor(0);
                }
                CoInitialize((LPVOID)0x0);
                sub_545030();
                sub_41ABC0();
                sub_43CB40(1);
                sub_545270();
                cVar3 = sub_40FE30();
                if (cVar3 != '\0') {
                  sub_41F630(s_disneylogompeg_dat_00572528);
                  if (DAT_005865e4 == 0) {
                    sub_41F630(s_argologompeg_dat_005724f0,0);
                  }
                  else {
                    sub_41D2C0(s_disney_cor_0057251c,3000);
                    sub_41D2C0(s_arglogo_cor_00572510,3000);
                    sub_41D2C0(s_movinfo_cor_00572504,8000);
                  }
                  sub_41D2C0(s__englogo_cor_005724e3 + 1,3000);
                  sub_545030();
                  sub_425540();
                  DAT_00581168 = operator_new(0x2c);
                  uVar2 = DAT_0057f920;
                  uVar1 = DAT_0057f91c;
                  uVar8 = DAT_0057f918;
                  if (DAT_00581168 == (undefined4 *)0x0) {
                    DAT_00581168 = (undefined4 *)0x0;
                  }
                  else {
                    DAT_00581168[6] = 0x3c23d70a;
                    DAT_00581168[7] = 0x40a00000;
                    DAT_00581168[3] = uVar8;
                    DAT_00581168[8] = 0x42700000;
                    DAT_00581168[4] = uVar1;
                    DAT_00581168[5] = uVar2;
                    DAT_00581168[2] = 0;
                    DAT_00581168[1] = 0;
                    *DAT_00581168 = 0;
                    DAT_00581168[9] = 0;
                    DAT_00581168[10] = 0;
                  }
                  pvVar5 = operator_new(0x28);
                  local_8 = 3;
                  if (pvVar5 == (void *)0x0) {
                    DAT_0058115c = 0;
                  }
                  else {
                    DAT_0058115c = sub_41BCB0();
                  }
                  local_8 = 0xffffffff;
                  pvVar5 = operator_new(0x28);
                  local_8 = 4;
                  if (pvVar5 == (void *)0x0) {
                    DAT_00581160 = 0;
                  }
                  else {
                    DAT_00581160 = sub_41BCB0();
                  }
                  local_8 = 0xffffffff;
                  sub_41BCF0(0,0,0,0xff);
                  DAT_00581164 = 0;
                  sub_41D340();
                  sub_419460();
                  sub_558E90();
                  sub_424590();
                  sub_410480(DAT_00573d38,DAT_00573d3c,DAT_00573d40);
                  do {
                    if (((DAT_00585739 != '\0') || (DAT_005846e4 == 0x11)) ||
                       (cVar3 = sub_419650(), cVar3 == '\0')) {
                      sub_545030();
                      sub_43CB40(0);
                      sub_545270();
                      DestroyWindow(DAT_005855d0);
                      CoUninitialize();
                      ExceptionList = local_10;
                      return local_50.wParam;
                    }
                    DAT_006d9e10 = 0;
                    sub_4255B0(DAT_005846e4 == 4);
                    cVar3 = PTR_DAT_00571f54[0x54];
                    while (cVar3 == '\0') {
                      BVar6 = PeekMessageA(&local_50,(HWND)0x0,0,0,1);
                      if (BVar6 == 0) {
                        sub_54B9F0(0,0);
                        if (DAT_00585a88 == 0) {
                          QueryPerformanceCounter(&local_1c);
                          DAT_00585a78 = local_1c.s.LowPart;
                          DAT_00585a7c = local_1c.s.HighPart;
                          DAT_00585a88 = 1;
                        }
                        if (((DAT_00582cc8 == '\0') || (DAT_00581128 != '\0')) ||
                           ((DAT_00585739 != '\0' || (DAT_00581129 == '\0')))) {
                          WaitMessage();
                        }
                        else {
                          if (DAT_005846e4 == 0xc) {
                            uVar8 = 0x3c;
                          }
                          else {
                            uVar8 = 0x1e;
                          }
                          sub_41CEE0(uVar8);
                          sub_41EDC0();
                          sub_4254F0();
                          if (((DAT_005846e4 != 3) || (DAT_00584638 == 9)) || (DAT_00584638 == 8)) {
                            sub_414780();
                          }
                          iVar4 = sub_4196D0();
                          if (iVar4 != 0) break;
                          if (PTR_DAT_00571f54[0x54] != '\0') {
                            sub_439280();
                            sub_439490();
                            sub_4254F0();
                            goto LAB_0041d8a9;
                          }
                          if (DAT_005846e4 == 3) {
                            sub_414780();
                          }
                          GetCursorPos(&local_24);
                          SetCursorPos(local_24.x,local_24.y);
                          cVar3 = sub_41DD20();
                          if (cVar3 == '\0') {
                            sub_41DF60();
                            break;
                          }
                        }
                        if (DAT_00585a88 == 1) {
                          QueryPerformanceCounter(local_34);
                          DAT_00585a88 = 0;
                          bVar7 = CARRY4(DAT_00585a70,local_34[0].s.LowPart - DAT_00585a78);
                          DAT_00585a70 = DAT_00585a70 + (local_34[0].s.LowPart - DAT_00585a78);
                          DAT_00585a74 = DAT_00585a74 +
                                         ((local_34[0].s.HighPart - DAT_00585a7c) -
                                         (uint)((uint)local_34[0]._0_4_ < DAT_00585a78)) +
                                         (uint)bVar7;
                        }
                      }
                      else {
                        if (local_50.message == 0x12) {
                          DAT_005846e4 = 0x11;
                          PTR_DAT_00571f54[0x54] = 1;
                          break;
                        }
                        TranslateMessage(&local_50);
                        DispatchMessageA(&local_50);
                      }
LAB_0041d8a9:
                      cVar3 = PTR_DAT_00571f54[0x54];
                    }
                    DAT_0058372c = 0;
                  } while( true );
                }
                lpText = (&PTR_DAT_0057ba4c)[DAT_00584f04];
              }
            }
          }
        }
      }
    }
    MessageBoxA((HWND)0x0,lpText,s_Groove_005722dc,0);
  }
  ExceptionList = local_10;
  return 0;
}

