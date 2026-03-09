@echo off

call build.bat

if %errorlevel%==0 (
    call .\.out\win\debug\game.exe
)