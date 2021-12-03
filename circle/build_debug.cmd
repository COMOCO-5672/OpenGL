@echo off
title qmake and nmake build prompt
set VCINSTALLDIR=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC
set QTDIR=C:\Qt\Qt5.12.5\5.12.5\msvc2015_64
set PATH=%VCINSTALLDIR%\bin;%QTDIR%\bin;%PATH%
call "%VCINSTALLDIR%\vcvarsall.bat" amd64
md bin
cd bin
qmake ./src/Circle.pro -spec win32-msvc "CONFIG+=debug" "CONFIG+=qml_debug" 
nmake

@REM cd MediaPlayer/debug/out
@REM set type = %~1
@REM if "%type%"=="debug" (
@REM     @echo come in debug1
@REM     qmake ../MediaPlayer.pro -spec win32-msvc "CONFIG+=debug" "CONFIG+=qml_debug" 
@REM ) else (
@REM     if "%type%"=="release" (
@REM         qmake ../MediaPlayer.pro -spec win32-msvc "CONFIG+=qtquickcompiler" 
@REM         ) else (
@REM             goto END 
@REM         )
@REM ) 
@REM nmake 
@REM if "%type%"=="debug" (
@REM     @echo come in debug
@REM     cd MediaPlayer/debug/out 
@REM ) else (
@REM     if "%type%"=="release"( 
@REM         @echo come release
@REM         cd MediaPlayer/release/out 
@REM     ) else ( 
@REM         goto END 
@REM     ) 
@REM )
@echo current path is %cd%
@REM windeployqt MediaPlayer.exe