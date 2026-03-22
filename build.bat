@echo off

set target=src\main.c
set out=game.exe

set debug_out=.out\win\debug
set release_out=.out\win\release
set includes=-Isrc

:: "-lgdi32"  graphics context. 
:: "-luser32" window and events. 

set build=zig cc %target% %includes% -std=c99 -lopengl32 -lgdi32 -luser32 -lwinmm -DENGINE_API_GL
set debug=%build% -o %debug_out%\%out% -g -O0 -DENGINE_CONFIG_DEBUG
set release=%build% -o %release_out%\%out% -O2

:: "-g"        generates debug info.
:: "-O0"       zero optimizations.
:: "-O2"       high level optimizations.
:: "-DDEBUG"   defines DEBUG macro.
:: "-Isrc"     includes src folder recursively.

echo Build started at %time%.

if "%1"=="release" (
    if not exist %release_out% mkdir %release_out%
    %release%
) else (
    if not exist %debug_out% mkdir %debug_out%
    %debug%
)

if %errorlevel%==0 (
    echo Build succeeded at %time%.
) else (
    echo Build failed.
)