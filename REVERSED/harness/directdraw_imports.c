/* Keep the generated C calling convention at the boundary and let the Windows
 * SDK supply the actual stdcall imports. A zero-returning stub cannot create
 * interfaces or invoke the enumeration callbacks.
 */
#define DIRECTDRAW_VERSION 0x0700
#include <windows.h>
#include <ddraw.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
#include <stdio.h>

/* Capture the game's completed render surface, independently of presentation.
 * The caller uses this once, after EndScene, during a bounded diagnostic run. */
void groove_dump_render_surface(void *object, void *viewport)
{
    LPDIRECTDRAWSURFACE4 surface = (LPDIRECTDRAWSURFACE4)object;
    DDSURFACEDESC2 desc = {0};
    DWORD view[11] = {44}, header[8];
    HRESULT result;
    FILE *output;
    typedef HRESULT (WINAPI *get_viewport)(void *, DWORD *);
    if (viewport) {
        result = ((get_viewport)(*(void ***)viewport)[16])(viewport, view);
        fprintf(stderr, "[surface] viewport hr=%08lx xy=%lu/%lu size=%lu/%lu z=%08lx/%08lx\n",
                result, view[1], view[2], view[3], view[4], view[9], view[10]);
    }
    desc.dwSize = sizeof desc;
    result = surface->lpVtbl->Lock(surface, NULL, &desc, DDLOCK_WAIT | DDLOCK_READONLY, NULL);
    fprintf(stderr, "[surface] render lock hr=%08lx size=%lu/%lu pitch=%ld bits=%lu\n",
            result, desc.dwWidth, desc.dwHeight, desc.lPitch, desc.ddpfPixelFormat.dwRGBBitCount);
    if (FAILED(result)) return;
    if (desc.lpSurface && desc.lPitch > 0 && desc.lPitch <= 65536 && desc.dwHeight <= 8192) {
        header[0] = desc.dwWidth; header[1] = desc.dwHeight; header[2] = desc.lPitch;
        header[3] = desc.ddpfPixelFormat.dwRGBBitCount;
        header[4] = desc.ddpfPixelFormat.dwRBitMask;
        header[5] = desc.ddpfPixelFormat.dwGBitMask;
        header[6] = desc.ddpfPixelFormat.dwBBitMask;
        header[7] = desc.ddpfPixelFormat.dwRGBAlphaBitMask;
        output = fopen("groove_render.raw", "wb");
        if (output) {
            fwrite(header, sizeof header, 1, output);
            fwrite(desc.lpSurface, desc.lPitch, desc.dwHeight, output);
            fclose(output);
            fprintf(stderr, "[surface] saved groove_render.raw\n");
        }
    }
    result = surface->lpVtbl->Unlock(surface, NULL);
    fprintf(stderr, "[surface] render unlock hr=%08lx\n", result);
}

HRESULT groove_DirectDrawCreate(GUID *guid, void **object, void *outer)
{
    return DirectDrawCreate(guid, (LPDIRECTDRAW *)object, (IUnknown *)outer);
}

HRESULT groove_DirectDrawEnumerateA(LPDDENUMCALLBACKA callback, void *context)
{
    return DirectDrawEnumerateA(callback, context);
}

HRESULT groove_DirectDrawEnumerateExA(LPDDENUMCALLBACKEXA callback, void *context, DWORD flags)
{
    return DirectDrawEnumerateExA(callback, context, flags);
}

HRESULT groove_DirectInputCreateA(HINSTANCE instance, DWORD version, void **object, void *outer)
{
    typedef HRESULT (WINAPI *CreateInput)(HINSTANCE, DWORD, LPDIRECTINPUTA *, LPUNKNOWN);
    static HMODULE module;
    CreateInput create;
    /* Retain the import module for the process: returned interfaces execute its code.
     * The game's input setup calls this from its single startup thread.
     */
    if (module == NULL)
        module = LoadLibraryA("dinput.dll");
    if (module == NULL)
        return HRESULT_FROM_WIN32(GetLastError());
    create = (CreateInput)GetProcAddress(module, "DirectInputCreateA");
    if (create == NULL)
        return HRESULT_FROM_WIN32(GetLastError());
    return create(instance, version, (LPDIRECTINPUTA *)object, (LPUNKNOWN)outer);
}

const void *groove_KeyboardDataFormat(void) { return &c_dfDIKeyboard; }
