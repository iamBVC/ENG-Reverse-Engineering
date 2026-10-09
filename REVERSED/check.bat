@echo off
rem =====================================================================
rem  check.bat - byte-compare the compiled functions against groove.exe.
rem
rem  check.bat                 compare everything in build\objects
rem  check.bat --only sub_415AB0 sub_41EF00
rem  check.bat --list          show the work queue without compiling
rem =====================================================================
setlocal
python "%~dp0tools\bytecheck.py" %*
endlocal
