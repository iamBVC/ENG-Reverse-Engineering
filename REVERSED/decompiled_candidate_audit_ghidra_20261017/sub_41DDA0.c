/* Selected Ghidra export at 0041dda0. */

uint sub_41DDA0(HWND param_1,uint param_2,uint param_3,LPARAM param_4)

{
  LPARAM lParam;
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined1 auStack_50 [80];
  
  lParam = param_4;
  uVar3 = param_3;
  cVar1 = sub_4065D0(&param_4,&param_3,param_1,param_2,param_3,param_4);
  if (cVar1 == '\0') {
LAB_0041df47:
    sub_41DF60();
    return 0;
  }
  if ((char)param_4 != '\0') {
    return param_3;
  }
  if (param_2 < 0x106) {
    if (param_2 < 0x104) {
      if (param_2 == 2) {
        sub_41DF60();
        uVar3 = DefWindowProcA(param_1,2,uVar3,lParam);
        return uVar3;
      }
      if ((param_2 == 0x100) && (uVar3 == 0x75)) {
        sub_562717(auStack_50,s_capture_d_tga_0057262c,DAT_00586418);
        while (iVar2 = sub_562AEE(auStack_50,&DAT_00571d80), iVar2 != 0) {
          sub_5628EB(iVar2);
          DAT_00586418 = DAT_00586418 + 1;
          sub_562717(auStack_50,s_capture_d_tga_0057262c,DAT_00586418);
        }
        cVar1 = sub_40CAB0(auStack_50,DAT_00582ccc,DAT_00582ce4);
        if (cVar1 == '\0') {
          sub_414600(s_WinMain__capture_failed__ncap_____00572608,DAT_00586418);
        }
        DAT_00586418 = DAT_00586418 + 1;
        uVar3 = DefWindowProcA(param_1,0x100,0x75,lParam);
        return uVar3;
      }
    }
    else if ((uVar3 != 9) && (uVar3 != 0x73)) {
      return 0;
    }
  }
  else {
    if (param_2 == 0x111) {
      if ((uVar3 & 0xffff) != 2) {
        return 0;
      }
      DAT_005846e4 = 0x11;
      PTR_DAT_00571f54[0x54] = 1;
      goto LAB_0041df47;
    }
    if (param_2 == 0x400) {
      sub_40F170(uVar3 == 0);
    }
  }
  uVar3 = DefWindowProcA(param_1,param_2,uVar3,lParam);
  return uVar3;
}

