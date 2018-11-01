@echo off

TASKLIST | FIND "omniNames.exe" > NUL
IF NOT ERRORLEVEL 1  (
        TASKKILL /F /IM omniNames.exe
)

