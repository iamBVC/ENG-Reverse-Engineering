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

/* Read back uploaded texture surfaces once during startup. This distinguishes
 * bad WAD conversion/upload from a later D3D state or rasterization failure. */
void groove_probe_texture_surface(void *object, void *texture, unsigned int index)
{
    LPDIRECTDRAWSURFACE4 surface = (LPDIRECTDRAWSURFACE4)object;
    DDSURFACEDESC2 desc = {0};
    HRESULT result;
    unsigned long long hash = 1469598103934665603ULL;
    unsigned int x, y, samples = 0;
    const unsigned char *row;
    desc.dwSize = sizeof desc;
    if (!surface) {
        fprintf(stderr, "[texture-probe] index=%u surface=null texture=%p\n", index, texture);
        return;
    }
    result = surface->lpVtbl->Lock(surface, NULL, &desc, DDLOCK_WAIT | DDLOCK_READONLY, NULL);
    if (FAILED(result)) {
        fprintf(stderr, "[texture-probe] index=%u surface=%p texture=%p lock=%08lx\n",
                index, object, texture, result);
        return;
    }
    if (desc.lpSurface && desc.lPitch > 0 && desc.dwHeight <= 8192 && desc.dwWidth <= 8192) {
        /* Hash a bounded grid, so even large mip levels have cheap diagnostics. */
        for (y = 0; y < desc.dwHeight; y += (desc.dwHeight > 64 ? desc.dwHeight / 64 : 1)) {
            row = (const unsigned char *)desc.lpSurface + (size_t)y * desc.lPitch;
            for (x = 0; x < desc.dwWidth; x += (desc.dwWidth > 64 ? desc.dwWidth / 64 : 1)) {
                unsigned int b;
                size_t pixel_bytes = (desc.ddpfPixelFormat.dwRGBBitCount + 7) / 8;
                if (pixel_bytes == 0 || pixel_bytes > 4) break;
                for (b = 0; b < pixel_bytes; ++b) {
                    hash ^= row[(size_t)x * pixel_bytes + b];
                    hash *= 1099511628211ULL;
                }
                ++samples;
            }
        }
        fprintf(stderr, "[texture-probe] index=%u surface=%p texture=%p size=%lu/%lu pitch=%ld bpp=%lu samples=%u hash=%016llx first=%02x%02x%02x%02x\n",
                index, object, texture, desc.dwWidth, desc.dwHeight, desc.lPitch,
                desc.ddpfPixelFormat.dwRGBBitCount, samples, hash,
                ((const unsigned char *)desc.lpSurface)[0],
                ((const unsigned char *)desc.lpSurface)[1],
                ((const unsigned char *)desc.lpSurface)[2],
                ((const unsigned char *)desc.lpSurface)[3]);
    } else {
        fprintf(stderr, "[texture-probe] index=%u surface=%p texture=%p invalid-surface\n",
                index, object, texture);
    }
    surface->lpVtbl->Unlock(surface, NULL);
}

/* Hash decoded WAD pixels before DirectDraw surface creation/upload. */
void groove_probe_texture_source(const void *pixels, unsigned int width, unsigned int height,
                                 unsigned int texture_type, unsigned int index)
{
    const unsigned char *bytes = (const unsigned char *)pixels;
    size_t length = (size_t)width * height * 2;
    size_t stride = length > 4096 ? length / 4096 : 1;
    size_t i;
    unsigned int samples = 0;
    unsigned long long hash = 1469598103934665603ULL;
    if (!bytes) {
        fprintf(stderr, "[texture-source] index=%u type=%u size=%u/%u pixels=null\n",
                index, texture_type, width, height);
        return;
    }
    for (i = 0; i < length; i += stride) {
        hash ^= bytes[i];
        hash *= 1099511628211ULL;
        ++samples;
    }
    fprintf(stderr, "[texture-source] index=%u type=%u size=%u/%u bytes=%llu samples=%u hash=%016llx first=%02x%02x%02x%02x\n",
            index, texture_type, width, height, (unsigned long long)length, samples, hash,
            bytes[0], bytes[1], bytes[2], bytes[3]);
}


HRESULT groove_DirectDrawCreate(GUID *guid, void **object, void *outer)
{
    static unsigned int trace_count;
    HRESULT result = DirectDrawCreate(guid, (LPDIRECTDRAW *)object, (IUnknown *)outer);
    if (trace_count < 8) {
        if (guid != NULL) {
            fprintf(stderr,
                    "[ddraw-create] call=%u guid=%08lx-%04x-%04x-%02x%02x%02x%02x%02x%02x result=%08lx object=%p\n",
                    trace_count + 1, (unsigned long)guid->Data1, guid->Data2, guid->Data3,
                    guid->Data4[0], guid->Data4[1], guid->Data4[2], guid->Data4[3],
                    guid->Data4[4], guid->Data4[5], (unsigned long)result,
                    object != NULL ? *object : NULL);
        } else {
            fprintf(stderr, "[ddraw-create] call=%u guid=(null) result=%08lx object=%p\n",
                    trace_count + 1, (unsigned long)result,
                    object != NULL ? *object : NULL);
        }
        fflush(stderr);
        ++trace_count;
    }
    return result;
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
