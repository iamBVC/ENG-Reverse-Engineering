@echo off
rem =====================================================================
rem  build.bat - compile the reversed sources and relink an executable.
rem
rem  build.bat        compile + link
rem  build.bat run    compile + link + run the self-test
rem  build.bat check  compile + link + byte-compare against groove.exe
rem =====================================================================
setlocal enabledelayedexpansion
set "ROOT=%~dp0"
if "%ROOT:~-1%"=="\" set "ROOT=%ROOT:~0,-1%"

rem ---- locate a 32-bit MSVC toolchain --------------------------------
set "VSDIR="
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
    for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSDIR=%%i"
)
if not defined VSDIR if exist "F:\Programmi\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" set "VSDIR=F:\Programmi\Microsoft Visual Studio\2022\Community"
if not defined VSDIR (
    echo [!] No Visual C++ toolchain found.
    echo     Install the "Desktop development with C++" workload, or set VSDIR in this script.
    exit /b 1
)
call "%VSDIR%\VC\Auxiliary\Build\vcvars32.bat" >nul
if errorlevel 1 ( echo [!] vcvars32.bat failed & exit /b 1 )

rem ---- compile --------------------------------------------------------
rem  /O2        optimise for speed      /MT static CRT
rem  /GS-       no stack cookies        (MSVC 6 had none; keeps codegen comparable)
rem  /arch:IA32 x87 floating point      (the original is x87: `fld`/`fdiv`/`fstp`,
rem            not SSE `movss`/`divss`, which is what /arch:SSE2 emits)
rem  x86 is required: the original is PE32
set "OBJ=%ROOT%\build\objects"
if not exist "%OBJ%" mkdir "%OBJ%"

echo Compiling...
pushd "%OBJ%"
rem  /TP compiles every translation unit as C++.  The game itself is C++
rem  (the CRT calls in the listing are `??2@YAPAXI@Z` etc.), and C++ mode is what
rem  makes `__thiscall` legal for the member-style functions.
cl /nologo /c /O2 /MT /GS- /arch:IA32 /W3 /TP /D_CRT_SECURE_NO_WARNINGS /I"%ROOT%\include" ^
   "%ROOT%\src\gr_alloc.c" "%ROOT%\src\gr_data.c" "%ROOT%\src\gr_io.c" ^
   "%ROOT%\src\gr_map.c" "%ROOT%\src\gr_pending.c" "%ROOT%\src\gr_small.c" ^
   "%ROOT%\src\host_main.c"
if errorlevel 1 ( popd & echo [!] compile failed & exit /b 1 )
popd

rem ---- link -----------------------------------------------------------
echo Linking...
rem  NOTE: this list must stay closure-complete.  gr_pending.c is compiled above
rem  (so the byte check still sees it) but is NOT linked: it references callees
rem  that are not reversed yet.
link /nologo /subsystem:console /opt:ref /out:"%ROOT%\build\groove_rebuild.exe" ^
     "%OBJ%\gr_alloc.obj" "%OBJ%\gr_data.obj" "%OBJ%\gr_io.obj" ^
     "%OBJ%\gr_map.obj" "%OBJ%\gr_small.obj" "%OBJ%\host_main.obj"
if errorlevel 1 ( echo [!] link failed & exit /b 1 )

echo.
echo Built %ROOT%\build\groove_rebuild.exe

if /i "%~1"=="run"   "%ROOT%\build\groove_rebuild.exe"
if /i "%~1"=="check" python "%ROOT%\tools\bytecheck.py"
endlocal
