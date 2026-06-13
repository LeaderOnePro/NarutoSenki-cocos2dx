@echo off
title NarutoSenki

rem ============================================================
rem  NarutoSenki launcher -- double-click to run the game.
rem
rem  The game loads its resources from the CURRENT WORKING
rem  DIRECTORY, so the exe must be started with its working
rem  dir set to the Resources folder.
rem  (Do NOT double-click the exe directly -- it will fail to
rem   find resources.)
rem ============================================================

set "EXE=%~dp0proj.win32\Debug.win32\NarutoSenki.exe"
set "RESDIR=%~dp0Resources"

if not exist "%EXE%" (
    echo [ERROR] Game executable not found:
    echo        %EXE%
    echo.
    echo Please build the project ^(Debug ^| Win32^) first.
    echo.
    pause
    exit /b 1
)

rem /d sets the startup working directory to Resources so the
rem game can locate Audio, textures, plist files, etc.
start "" /d "%RESDIR%" "%EXE%"
exit /b 0
