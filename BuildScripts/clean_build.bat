@echo off
cd ..
REM Check if the build directory exists
if exist build (
    echo Removing contents of the build directory...
    rmdir /s /q build
    echo Build directory cleaned.
) else (
    echo Build directory does not exist.
)

pause