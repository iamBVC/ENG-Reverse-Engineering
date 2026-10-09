/* sub_41DC40 @ 0041dc40   220 bytes */

bool sub_41DC40(HINSTANCE param_1)

{
  char cVar1;
  ATOM AVar2;
  int nHeight;
  int nWidth;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  HWND hWndParent;
  HMENU hMenu;
  LPVOID lpParam;
  WNDCLASSA local_28;
  
  uVar3 = 0xffffffff;
  pcVar5 = "Emperors New Groove";
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  local_28.style = 3;
  local_28.lpfnWndProc = (WNDPROC)&LAB_0041dda0;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = (char *)&DAT_005855d8;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  DAT_00585738 = 1;
  DAT_005855d4 = param_1;
  local_28.cbClsExtra = 0;
  local_28.cbWndExtra = 0;
  local_28.hInstance = param_1;
  local_28.hIcon = LoadIconA(param_1,s_AppIcon_00572600);
  local_28.hCursor = (HCURSOR)0x0;
  local_28.hbrBackground = GetStockObject(4);
  local_28.lpszMenuName = (LPCSTR)0x0;
  local_28.lpszClassName = s_Groove_005722dc;
  AVar2 = RegisterClassA(&local_28);
  if (AVar2 == 0) {
    return false;
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hWndParent = (HWND)0x0;
  nHeight = sub_41DAD0(1);
  nWidth = sub_41DAD0(0);
  DAT_005855d0 = CreateWindowExA(0x40000,s_Groove_005722dc,s_Groove_005722dc,0x80000000,0,0,nWidth,
                                 nHeight,hWndParent,hMenu,param_1,lpParam);
  return DAT_005855d0 != (HWND)0x0;
}

