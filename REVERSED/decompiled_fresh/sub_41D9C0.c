/* sub_41D9C0 @ 0041d9c0   259 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool sub_41D9C0(void)

{
  HMODULE hModule;
  
  if (DAT_005863e8 != 0) {
    return DAT_005863dc != (FARPROC)0x0;
  }
  _DAT_005863ec = sub_41D980();
  hModule = GetModuleHandleA(s_USER32_005725f0);
  if (hModule != (HMODULE)0x0) {
    DAT_005863cc = GetProcAddress(hModule,s_GetSystemMetrics_005725dc);
    if (DAT_005863cc != (FARPROC)0x0) {
      _DAT_005863d0 = GetProcAddress(hModule,s_MonitorFromWindow_005725c8);
      if (_DAT_005863d0 != (FARPROC)0x0) {
        _DAT_005863d4 = GetProcAddress(hModule,s_MonitorFromRect_005725b8);
        if (_DAT_005863d4 != (FARPROC)0x0) {
          _DAT_005863d8 = GetProcAddress(hModule,s_MonitorFromPoint_005725a4);
          if (_DAT_005863d8 != (FARPROC)0x0) {
            _DAT_005863e0 = GetProcAddress(hModule,s_EnumDisplayMonitors_00572590);
            if (_DAT_005863e0 != (FARPROC)0x0) {
              DAT_005863dc = GetProcAddress(hModule,s_GetMonitorInfoA_00572580);
              if (DAT_005863dc != (FARPROC)0x0) {
                _DAT_005863e4 = GetProcAddress(hModule,s_EnumDisplayDevicesA_0057256c);
                if (_DAT_005863e4 != (FARPROC)0x0) {
                  DAT_005863e8 = 1;
                  return true;
                }
              }
            }
          }
        }
      }
    }
  }
  DAT_005863cc = (FARPROC)0x0;
  _DAT_005863d0 = (FARPROC)0x0;
  _DAT_005863d4 = (FARPROC)0x0;
  _DAT_005863d8 = (FARPROC)0x0;
  DAT_005863dc = (FARPROC)0x0;
  _DAT_005863e0 = (FARPROC)0x0;
  _DAT_005863e4 = (FARPROC)0x0;
  DAT_005863e8 = 1;
  return false;
}

