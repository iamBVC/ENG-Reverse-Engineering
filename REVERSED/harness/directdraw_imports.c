/* Keep the generated C calling convention at the boundary and let the Windows
 * SDK supply the actual stdcall imports. A zero-returning stub cannot create
 * interfaces or invoke the enumeration callbacks.
 */
#define DIRECTDRAW_VERSION 0x0700
#include <windows.h>
#include <ddraw.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>

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
