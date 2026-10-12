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
rem System import libraries for the bulk image.  These are what resolves the
rem `__imp__*` symbols - an import-address entry cannot be expressed as a C symbol
rem (`@` is not legal in an identifier), so the library is the only route.  ddraw.lib
rem ships with the Windows SDK; DirectInput and Miles (mss32) do not, so those stay
rem stubs.
rem Kernel32.lib is spelled out because the exe link needs it for the file/process calls
rem the *real* stream wrappers make (CreateFileA, ReadFile, ...), and the DLL link does
rem not pull those in: its chunk set is the filtered one, where the harness substitutes
rem the wrappers.
rem The CRT import libraries are named for the same reason: an exe pulls the runtime's
rem own startup helpers, and those reference the undecorated names (`_memcpy`, `_cos`)
rem and their IAT entries (`__imp__malloc`) - measured as 16 unresolved symbols when the
rem CRT libs were left to the defaults.
set "SYSLIBS=Kernel32.lib User32.lib Gdi32.lib AdvAPI32.lib Ole32.Lib OleAut32.Lib ^
 WinMM.lib Shell32.lib ComCtl32.Lib Version.lib ddraw.lib ^
 ucrt.lib msvcrt.lib libvcruntime.lib"

rem The exe is built against the *static* CRT instead: with the DLL CRT its own runtime
rem helpers come from objects that expect the static implementations, and 14 of them
rem (`_memcpy`, `_cos`, `__imp__malloc`, ...) stay unresolved (measured).  /MT is fine for
rem a single-image rebuild - nothing crosses a runtime boundary there.
set "SYSLIBS_EXE=Kernel32.lib User32.lib Gdi32.lib AdvAPI32.lib Ole32.Lib OleAut32.Lib ^
 WinMM.lib Shell32.lib ComCtl32.Lib Version.lib ddraw.lib libcmt.lib libucrt.lib libvcruntime.lib"

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
rem symbols it references but does not define need definitions: the system import
rem libraries below, plus tools\gen_link_stubs.py for everything else.  That generator
rem reads build\_bulk_link.log (this link) and build\_exe_link.log, and keeps what it
rem already stubbed, so a first run that fails is expected only when something new is
rem unresolved - the list is in src_generated\link_stubs.csv.  The chunk set comes from tools\make_dll_source.py: the same files as
rem src_generated\chunks, minus the six functions the harness supplies itself
rem (harness\substituted.txt) - the drivers feed a chunk from memory, so the real stream
rem wrappers would be handed a FILE* that is not one.
rem
rem io_substitutes.c brings those six (plus groove_ftol), crt_aliases.c the rest of the
rem CRT names, link_stubs.c everything else the bulk references but does not define.
python "%ROOT%\tools\make_dll_source.py"
if errorlevel 1 ( popd & exit /b 1 )
rem /DGROOVE_IO_SUBSTITUTES: io_substitutes.c brings its own operator_new, so
rem crt_aliases.c must not define a second one in this build (LNK2005).
cl /nologo /c /TC /W0 /GS- /MD /DGROOVE_IO_SUBSTITUTES ^
   /I"%ROOT%\include" /I"%ROOT%\src_generated" ^
   "%ROOT%\build\dll_chunks\chunk_*.c" "%ROOT%\src_generated\ghidra_globals.c" ^
   "%ROOT%\src_generated\link_stubs.c" "%ROOT%\harness\crt_aliases.c" ^
   "%ROOT%\harness\io_substitutes.c" ^
   "%ROOT%\harness\wrappers_bulk.c" "%ROOT%\harness\getters_ghidra.c"
if errorlevel 1 ( popd & exit /b 1 )
rem import_stubs.obj is deliberately *not* linked: measured, its /alternatename
rem aliases resolve nothing in this toolchain (see README).  Nothing depended on it -
rem the subset link never included it either.
link /nologo /DLL /OPT:REF /OUT:"%ROOT%\build\groove_ghidra.dll" ^
     chunk_*.obj ghidra_globals.obj link_stubs.obj crt_aliases.obj ^
     io_substitutes.obj wrappers_bulk.obj getters_ghidra.obj ^
     %SYSLIBS% > "_bulk_link.log" 2>&1
if errorlevel 1 ( echo [!] bulk link incomplete - see build\_bulk_link.log.  Regenerate the & echo     missing definitions with tools\gen_link_stubs.py and build again; the list of what & echo     is still a stub is written to src_generated\link_stubs.csv.  The compile itself & echo     succeeded: the objects are in build\chunk_*.obj & popd & exit /b 1 )
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

rem In bulk mode the image also gets linked as an exe: the *unfiltered* chunks (the real
rem stream wrappers, so nothing here is harness-specific) plus the same globals, stubs and
rem CRT aliases.
rem
rem The entry point is NOT /ENTRY:entry.  The original entry is the *MSVC 6 CRT startup*,
rem which in this image is an excluded artefact body - so overriding the entry with a stub
rem of it left the runtime's own entry points unresolved (14 symbols).  Instead the modern
rem CRT keeps its startup (WinMainCRTStartup, since the subsystem is WINDOWS) and
rem harness\exe_main.c supplies the WinMain it asks for, calling the game's own main
rem (sub_41D350, which the original startup calls - see that file).
if not "%MODE%"=="bulk" goto skip_exe
echo === linking groove_rebuild.exe (all 968 functions, original entry) ===
if not exist "exe_obj" mkdir "exe_obj"
rem The exe keeps the real stream wrappers (it reads actual files) but drops the reversed
rem CRT bodies: those need the 2001 FILE layout and _iob table, and crt_aliases.c maps
rem their names onto the modern CRT instead.
python "%ROOT%\tools\make_dll_source.py" --exe
if errorlevel 1 ( popd & exit /b 1 )
cl /nologo /c /TC /W0 /GS- /MT /I"%ROOT%\include" /I"%ROOT%\src_generated" ^
   "%ROOT%\build\exe_chunks\chunk_*.c" "%ROOT%\src_generated\ghidra_globals.c" ^
   "%ROOT%\src_generated\link_stubs.c" "%ROOT%\harness\crt_aliases.c" ^
   "%ROOT%\harness\crt_initialisers.c" ^
   "%ROOT%\harness\exe_main.c" /Fo"exe_obj\\"
rem  crt_initialisers.c is generated by tools/gen_crt_initialisers.py: it calls the game's
rem  static initialisers from exe_main.c, the piece of the 2001 startup the modern CRT does
rem  not supply.  Only the exe gets it - the DLL is driven by the harness, not by a startup.
if errorlevel 1 ( popd & exit /b 1 )
rem /MAP so a crash can be resolved to a function: gdb reports the faulting address, and
rem this file turns it into a name (the image is relocated, so subtract the module handle
rem the trace logs as `hInst=`).  Without it a fault is just a number.
link /nologo /SUBSYSTEM:WINDOWS /OUT:"%ROOT%\build\groove_rebuild.exe" ^
     /MAP:"%ROOT%\build\groove_rebuild.map" ^
     "exe_obj\*.obj" %SYSLIBS_EXE% > "_exe_link.log" 2>&1
rem Not fatal: the exe is documented as one library-set short (14 runtime entry points),
rem and the DLL above - the tested artifact - is already built.  Warn and carry on.
if errorlevel 1 ( echo [!] exe link incomplete - see build\_exe_link.log; add whatever it & echo     still wants with tools\gen_link_stubs.py - it reads this log too. & echo     Continuing: the DLL is built, the exe is a known gap. )
:skip_exe

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
