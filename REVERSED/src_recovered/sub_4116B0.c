/* Hand reconstruction of 0x004116B0: four-argument DirectDraw callback adapter. */
BOOL __stdcall sub_4116B0(GUID *guid, LPSTR description, LPSTR name, LPVOID context)
{
    return sub_4116D0(guid, description, name, context, 0);
}
