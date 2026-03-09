@echo off

set target=src\main.c
set out=app.exe

set debug_out=out\debug
set release_out=out\release
set includes=-Isrc

set build=clang %target% %includes% -std=c99
set debug=%build% -o %debug_out%\%out% -g -O0 -DDEBUG
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