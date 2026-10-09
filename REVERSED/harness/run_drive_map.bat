@echo off
rem Build and run the MAP loader driver (32-bit).
setlocal
for %%i in ("%~dp0..") do set "ROOT=%%~fi"
set "VSDIR=C:\Program Files\Microsoft Visual Studio\2022\Community"
if not exist "%VSDIR%\VC\Auxiliary\Build\vcvars32.bat" set "VSDIR=F:\Programmi\Microsoft Visual Studio\2022\Community"
call "%VSDIR%\VC\Auxiliary\Build\vcvars32.bat" >nul
pushd "%ROOT%\build"
cl /nologo /W3 /MD /GS- /Fo"drive_map.obj" /Fe"drive_map.exe" "%ROOT%\harness\drive_map.c"
if errorlevel 1 ( popd & exit /b 1 )
popd
exit /b 0
