/* Hand reconstruction of sub_41DDA0, 0x0041DDA0, from Game/groove.exe.asm.
 * The original callback is stdcall (ret 0x10); Ghidra did not export this entry.
 */
LRESULT __stdcall sub_41DDA0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    unsigned char handled = 0;
    undefined4 result = (undefined4)wparam;
    char filename[0x50];
    void *stream;

    if (!(sub_4065D0(&handled, &result, window, message, wparam, (LPRECT)lparam) & 0xff)) {
        sub_41DF60();
        return 0;
    }
    if (handled)
        return (LRESULT)result;

    switch (message) {
    case 0x100: /* WM_KEYDOWN: VK_F6 captures the current display. */
        if (wparam == 0x75) {
            sub_562717(filename, "capture%d.tga", DAT_00586418);
            while ((stream = (void *)sub_562AEE(filename, "r")) != 0) {
                sub_5628EB(stream);
                ++DAT_00586418;
                sub_562717(filename, "capture%d.tga", DAT_00586418);
            }
            if (!(sub_40CAB0(filename, DAT_00582ccc, DAT_00582ce4) & 0xff))
                sub_414600("WinMain: capture failed (ncap = %d)", DAT_00586418);
            ++DAT_00586418;
        }
        break;
    case 2: /* WM_DESTROY */
        sub_41DF60();
        break;
    case 0x104: /* WM_SYSKEYDOWN */
    case 0x105: /* WM_SYSKEYUP */
        if (wparam != 9 && wparam != 0x73)
            return 0;
        break;
    case 0x400: /* Game's activation notification. */
        sub_40F170(wparam == 0);
        break;
    case 0x111: /* WM_COMMAND: IDCANCEL */
        if ((wparam & 0xffff) == 2) {
            DAT_005846e4 = 0x11;
            *((unsigned char *)PTR_DAT_00571f54 + 0x54) = 1;
            sub_41DF60();
        }
        return 0;
    }
    return DefWindowProcA(window, message, wparam, lparam);
}
