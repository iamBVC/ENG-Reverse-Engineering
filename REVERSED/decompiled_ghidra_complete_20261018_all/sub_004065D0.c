/* sub_4065D0 @ 004065d0   355 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sub_4065D0(undefined1 *param_1,undefined4 *param_2,HWND param_3,uint param_4,WPARAM param_5,
          LPRECT param_6)

{
  int iVar1;
  
  *param_1 = 0;
  if (DAT_0057f93c != '\0') {
    if (param_4 < 0x21) {
      if (param_4 == 0x20) {
        iVar1 = ShowCursor(0);
        while (0 < iVar1) {
          iVar1 = ShowCursor(0);
        }
        SetCursor((HCURSOR)0x0);
        *param_2 = 1;
        *param_1 = 1;
        return 1;
      }
      if (param_4 == 3) {
        _DAT_00581124 = 0;
        _DAT_00581120 = 0;
        ClientToScreen(param_3,(LPPOINT)&DAT_00581120);
        return 1;
      }
      if (param_4 == 6) {
        iVar1 = ShowCursor(0);
        while (0 < iVar1) {
          iVar1 = ShowCursor(0);
        }
        PostMessageA(param_3,0x400,(uint)(param_5 != 0),0);
        return 1;
      }
      if (param_4 == 0x1c) {
        iVar1 = ShowCursor(0);
        while (0 < iVar1) {
          iVar1 = ShowCursor(0);
        }
        DAT_00581129 = param_5 != 0;
        if (!(bool)DAT_00581129) {
          _DAT_00570344 = 2;
          sub_41D330();
        }
        PostMessageA(param_3,0x400,param_5,0);
        return 1;
      }
    }
    else if (param_4 == 0x85) {
      *param_2 = 0;
      *param_1 = 1;
    }
    else if (param_4 == 0x216) {
      GetWindowRect(param_3,param_6);
      *param_2 = 1;
      *param_1 = 1;
      return 1;
    }
  }
  return 1;
}

