@echo off
rem =====================================================================
rem  build_dlls.bat - build the two sides of the verification harness.
rem
rem    build\groove_ghidra.dll   the decompiled code (curated, linkable subset)
rem    build\groove_hand.dll     the hand-ported track in src\
rem
rem  Both export the same wh_* wrappers (harness\wrappers_*.c plus the
rem  generated harness\getters_ghidra.c), so tools\verify.py can load them
rem  side by side and compare behaviour.
rem
rem  The Ghidra side is a *curated* subset on purpose: the full bulk needs the
rem  binary's own CRT/SEH helpers and the Win32/DirectX/Miles imports, which in a
rem  rebuild come from the system.  See tools/make_verify_subset.py.
rem =====================================================================
setlocal enabledelayedexpansion
for %%i in ("%~dp0..") do set "ROOT=%%~fi"

set "VSDIR=C:\Program Files\Microsoft Visual Studio\2022\Community"
if not exist "%VSDIR%\VC\Auxiliary\Build\vcvars32.bat" set "VSDIR=F:\Programmi\Microsoft Visual Studio\2022\Community"
call "%VSDIR%\VC\Auxiliary\Build\vcvars32.bat" >nul
if errorlevel 1 ( echo [!] no Visual C++ toolchain & exit /b 1 )

set "OBJ=%ROOT%\build"
if not exist "%OBJ%" mkdir "%OBJ%"
pushd "%OBJ%"

echo === building groove_ghidra.dll (curated decompiled subset) ===
cl /nologo /c /TC /W0 /GS- /MD /I"%ROOT%\include" /I"%ROOT%\src_generated" ^
   "%ROOT%\harness\verify_subset.c" "%ROOT%\harness\getters_ghidra.c" ^
   "%ROOT%\harness\io_substitutes.c"
if errorlevel 1 ( popd & exit /b 1 )
link /nologo /DLL /OPT:REF /OUT:"%ROOT%\build\groove_ghidra.dll" ^
     verify_subset.obj getters_ghidra.obj io_substitutes.obj ^
     ghidra_globals.obj > "_ghidra_link.log" 2>&1
if errorlevel 1 ( echo [!] ghidra DLL link failed - see build\_ghidra_link.log & popd & exit /b 1 )

echo === building groove_hand.dll (hand-ported track) ===
cl /nologo /c /TC /W0 /GS- /MD /I"%ROOT%\include" ^
   "%ROOT%\src\gr_alloc.c" "%ROOT%\src\gr_data.c" "%ROOT%\src\gr_io.c" ^
   "%ROOT%\src\gr_map.c" "%ROOT%\src\gr_small.c" ^
   "%ROOT%\harness\hand_extras.c" "%ROOT%\harness\wrappers_hand.c"
if errorlevel 1 ( popd & exit /b 1 )
link /nologo /DLL /OPT:REF /OUT:"%ROOT%\build\groove_hand.dll" ^
     gr_alloc.obj gr_data.obj gr_io.obj gr_map.obj gr_small.obj ^
     hand_extras.obj wrappers_hand.obj > "_hand_link.log" 2>&1
if errorlevel 1 ( echo [!] hand DLL link failed - see build\_hand_link.log & popd & exit /b 1 )

popd
echo.
echo Built:
echo   %ROOT%\build\groove_ghidra.dll
echo   %ROOT%\build\groove_hand.dll
endlocal
