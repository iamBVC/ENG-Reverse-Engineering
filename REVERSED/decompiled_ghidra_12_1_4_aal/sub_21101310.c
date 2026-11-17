/* sub_21101310 @ 21101310   164 bytes */

void sub_21101310(void)

{
  DWORD DVar1;
  HMODULE pHVar2;
  HWND hWnd;
  HMODULE pHVar3;
  uint uVar4;
  DWORD local_4;
  
  DVar1 = GetCurrentProcessId();
  pHVar2 = GetModuleHandleA((LPCSTR)0x0);
  if (DAT_21115594 == (HWND)0x0) {
    for (hWnd = GetTopWindow((HWND)0x0); hWnd != (HWND)0x0; hWnd = GetWindow(hWnd,2)) {
      GetWindowThreadProcessId(hWnd,&local_4);
      if (local_4 == DVar1) {
        pHVar3 = (HMODULE)GetWindowLongA(hWnd,-6);
        if ((pHVar3 == pHVar2) && (uVar4 = GetWindowLongA(hWnd,-0x10), (uVar4 & 0x40000000) == 0)) {
          DAT_21115594 = hWnd;
        }
        if (DAT_21115594 == (HWND)0x0) {
          DAT_21115594 = hWnd;
        }
      }
    }
    if (DAT_21115594 == (HWND)0x0) {
      DAT_21115594 = GetActiveWindow();
    }
  }
  return;
}

