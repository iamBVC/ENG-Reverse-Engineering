/* Bridge reconstructed calls to the original shipped AAL audio library. */
#include "ghidra_shim.h"

static FARPROC groove_audio_export(const char *name)
{
    static HMODULE module;
    FARPROC procedure;
    if (!module) {
        module = LoadLibraryA("aal.dll");
        if (module) fprintf(stderr, "[audio] loaded aal.dll\n");
    }
    procedure = module ? GetProcAddress(module, name) : NULL;
    if (!procedure) {
        fprintf(stderr, "[audio] missing export %s, error=%lu\n", name, GetLastError());
        ExitProcess(ERROR_PROC_NOT_FOUND);
    }
    return procedure;
}

int _AAL_Close3DProvider_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_Close3DProvider@4"))(arg0);
}

int _AAL_Enumerate3DProviders_12(UINT_PTR arg0, UINT_PTR arg1, UINT_PTR arg2)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR, UINT_PTR, UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_Enumerate3DProviders@12"))(arg0, arg1, arg2);
}

int _AAL_FreeVoice_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_FreeVoice@4"))(arg0);
}

int _AAL_Get3DAttributes_8(UINT_PTR arg0, UINT_PTR arg1)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR, UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_Get3DAttributes@8"))(arg0, arg1);
}

int _AAL_GetADSFlags_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_GetADSFlags@4"))(arg0);
}

int _AAL_GetADSVolume_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_GetADSVolume@4"))(arg0);
}

int _AAL_GetDataSize_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_GetDataSize@4"))(arg0);
}

int _AAL_GetDeviceId_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_GetDeviceId@4"))(arg0);
}

int _AAL_GetLoopType_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_GetLoopType@4"))(arg0);
}

int _AAL_GetPlayStatus_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_GetPlayStatus@4"))(arg0);
}

int _AAL_GetSampleRate_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_GetSampleRate@4"))(arg0);
}

int _AAL_InitDriver_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_InitDriver@4"))(arg0);
}

int _AAL_Init_0(void)
{
    typedef int (__stdcall *AudioCall)(void);
    return ((AudioCall)groove_audio_export("_AAL_Init@0"))();
}

int _AAL_LoadFile_8(UINT_PTR arg0, UINT_PTR arg1)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR, UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_LoadFile@8"))(arg0, arg1);
}

int _AAL_LoadResourceType_16(UINT_PTR arg0, UINT_PTR arg1, UINT_PTR arg2, UINT_PTR arg3)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR, UINT_PTR, UINT_PTR, UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_LoadResourceType@16"))(arg0, arg1, arg2, arg3);
}

int _AAL_LoadResource_8(UINT_PTR arg0, UINT_PTR arg1)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR, UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_LoadResource@8"))(arg0, arg1);
}

int _AAL_Open3DProvider_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_Open3DProvider@4"))(arg0);
}

int _AAL_PauseVoice_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_PauseVoice@4"))(arg0);
}

int _AAL_QuitDriver_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_QuitDriver@4"))(arg0);
}

int _AAL_Quit_0(void)
{
    typedef int (__stdcall *AudioCall)(void);
    return ((AudioCall)groove_audio_export("_AAL_Quit@0"))();
}

int _AAL_ResumeVoice_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_ResumeVoice@4"))(arg0);
}

int _AAL_Set3DAttributes_8(UINT_PTR arg0, UINT_PTR arg1)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR, UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_Set3DAttributes@8"))(arg0, arg1);
}

int _AAL_SetResource_8(UINT_PTR arg0, UINT_PTR arg1)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR, UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_SetResource@8"))(arg0, arg1);
}

int _AAL_SetSpeakerMode_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_SetSpeakerMode@4"))(arg0);
}

int _AAL_SetVoiceAttr_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_SetVoiceAttr@4"))(arg0);
}

int _AAL_StartVoice_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_StartVoice@4"))(arg0);
}

int _AAL_StopVoice_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_StopVoice@4"))(arg0);
}

int _AAL_UnloadFile_4(UINT_PTR arg0)
{
    typedef int (__stdcall *AudioCall)(UINT_PTR);
    return ((AudioCall)groove_audio_export("_AAL_UnloadFile@4"))(arg0);
}
