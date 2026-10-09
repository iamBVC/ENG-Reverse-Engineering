@echo off
rem =====================================================================
rem  ghidra_decompile.bat - decompile groove.exe with Ghidra, headless.
rem
rem  Writes one .c file per function into decompiled\ plus an _index.csv.
rem
rem  Requirements (already installed on this machine):
rem    Ghidra  : D:\Programmi\Ghidra\ghidra_12.1.4_PUBLIC
rem    JDK 21+ : C:\Program Files\Java\jdk-24   (Ghidra needs >= 21; the
rem              JDK 8 further up the PATH is too old and must be overridden)
rem
rem  Override with GHIDRA_HOME / JAVA_HOME if yours live elsewhere.
rem =====================================================================
setlocal enabledelayedexpansion
rem  this script lives in REVERSED\tools, so the project root is one level up
for %%i in ("%~dp0..") do set "ROOT=%%~fi"

if not defined GHIDRA_HOME set "GHIDRA_HOME=D:\Programmi\Ghidra\ghidra_12.1.4_PUBLIC"
if not defined JAVA_HOME   set "JAVA_HOME=C:\Program Files\Java\jdk-24"

if not exist "%GHIDRA_HOME%\support\analyzeHeadless.bat" (
    echo [!] Ghidra not found at "%GHIDRA_HOME%".
    echo     Set GHIDRA_HOME to the extracted ghidra_*_PUBLIC folder.
    exit /b 1
)
if not exist "%JAVA_HOME%\bin\java.exe" (
    echo [!] A JDK 21+ was not found at "%JAVA_HOME%".
    echo     Ghidra 12 requires Java 21 or newer; set JAVA_HOME accordingly.
    exit /b 1
)

set "EXE=%~1"
if "%EXE%"=="" set "EXE=%ROOT%\..\WAD\groove.exe"
if not exist "%EXE%" (
    echo [!] target executable not found: "%EXE%"
    exit /b 1
)

set "OUT=%ROOT%\decompiled"
set "PROJ=%ROOT%\build\ghidra_project"
if not exist "%OUT%" mkdir "%OUT%"
if not exist "%PROJ%" mkdir "%PROJ%"

echo Ghidra      : %GHIDRA_HOME%
echo Java        : %JAVA_HOME%
echo Executable  : %EXE%
echo Output      : %OUT%
echo.

rem  -analysisTimeoutPerFile guards against a pathological function eating the run
call "%GHIDRA_HOME%\support\analyzeHeadless.bat" "%PROJ%" GrooveRebuild ^
     -import "%EXE%" ^
     -scriptPath "%ROOT%\tools" ^
     -postScript ExportDecompiledC.java "%OUT%" ^
     -analysisTimeoutPerFile 1800 ^
     -deleteProject
if errorlevel 1 ( echo [!] analysis failed & exit /b 1 )

echo.
echo Decompiled sources written to %OUT%
endlocal
