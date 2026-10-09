@echo off
rem =====================================================================
rem  build_dlls.bat [bulk] - build the two sides of the verification harness.
rem
rem    build\groove_ghidra.dll   the decompiled code
rem    build\groove_hand.dll     the hand-ported track in src\
rem
rem      build_dlls.bat          groove_ghidra.dll from the curated subset
rem      build_dlls.bat bulk     ...from the whole bulk (all 968 functions)
rem
rem  Both export the same wh_* wrappers (harness\wrappers_bulk.c or the subset's
rem  own copy, plus the generated harness\getters_ghidra.c), so harness\verify.c
rem  and the two drivers can load either one without changing a line.
rem
rem  `bulk` compiles all 968 functions into objects and then tries to link them.  The
rem  link needs the system import libraries (advapi32/ddraw/mss32/...) which are not
rem  installed here, so expect it to fail with ~282 unresolved symbols: that list is the
rem  measurement, not a crash.  The tests therefore run against the curated subset
rem  (tools/make_verify_subset.py), which is built from the same generated sources and
rem  the same recorded patch table.
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

rem `build_dlls.bat bulk` puts the *whole* rebuild behind the same wrappers instead of
rem the 13-function curated subset: same drivers, same verifier, code under test is all
rem 968 functions that compile.  Everything the bulk does not define (the ~50
rem artefact functions, the two undecompilable giants, the CRT/STL internals) is
rem resolved by harness\import_stubs.c, regenerated from the link log by
rem tools\gen_import_stubs.py - so a test that reaches one of those will fault, which
rem is why the drivers only exercise the loaders and the allocators.
set "MODE=subset"
if /i "%~1"=="bulk" set "MODE=bulk"

rem labels, not `if (...) else (...)`: a nested `( popd & exit /b 1 )` inside such a
rem block plus `^` continuations runs *both* branches (measured - the subset build
rem silently overwrote the bulk one).
if "%MODE%"=="bulk" goto build_bulk
goto build_subset

:build_bulk
echo === building groove_ghidra.dll (whole bulk: all 968 functions) ===
rem The bulk keeps every function in the image (measured: /Gy + /OPT:REF does *not*
rem discard the ones the wrappers cannot reach - a two-function test proved it), so the
rem ~282 symbols it references but does not define have to be aliased to a stub with
rem tools\gen_import_stubs.py before this link can succeed.  The first run is expected
rem to fail and to write the list into build\_ghidra_link.log; that is the input of the
rem generator.
cl /nologo /c /TC /W0 /GS- /MD /I"%ROOT%\include" /I"%ROOT%\src_generated" ^
   "%ROOT%\src_generated\chunks\chunk_*.c" "%ROOT%\src_generated\ghidra_globals.c" ^
   "%ROOT%\harness\wrappers_bulk.c" "%ROOT%\harness\getters_ghidra.c"
if errorlevel 1 ( popd & exit /b 1 )
rem import_stubs.obj is deliberately *not* linked: measured, its /alternatename
rem aliases resolve nothing in this toolchain (see README).  Nothing depended on it -
rem the subset link never included it either.
link /nologo /DLL /OPT:REF /OUT:"%ROOT%\build\groove_ghidra.dll" ^
     chunk_*.obj ghidra_globals.obj wrappers_bulk.obj getters_ghidra.obj ^
     > "_ghidra_link.log" 2>&1
if errorlevel 1 ( echo [!] bulk link failed - see build\_ghidra_link.log for the ~282 symbols & echo     the bulk references but does not define: the artefact functions, DirectX/Miles, and & echo     MSVC 6 CRT internals.  Resolving them needs import libraries plus real stub & echo     definitions - see the README section on compiling and testing against the WADs. & echo     The compile itself succeeded; the objects are in build\chunk_*.obj & popd & exit /b 1 )
goto build_hand

:build_subset
echo === building groove_ghidra.dll (curated decompiled subset) ===
cl /nologo /c /TC /W0 /GS- /MD /I"%ROOT%\include" /I"%ROOT%\src_generated" ^
   "%ROOT%\harness\verify_subset.c" "%ROOT%\harness\getters_ghidra.c" ^
   "%ROOT%\harness\io_substitutes.c"
if errorlevel 1 ( popd & exit /b 1 )
link /nologo /DLL /OPT:REF /OUT:"%ROOT%\build\groove_ghidra.dll" ^
     verify_subset.obj getters_ghidra.obj io_substitutes.obj ^
     ghidra_globals.obj > "_ghidra_link.log" 2>&1
if errorlevel 1 ( echo [!] ghidra DLL link failed - see build\_ghidra_link.log & popd & exit /b 1 )
goto build_hand

:build_hand

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
echo Built (%MODE% mode):
echo   %ROOT%\build\groove_ghidra.dll
echo   %ROOT%\build\groove_hand.dll
endlocal
