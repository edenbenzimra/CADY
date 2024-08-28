@echo off
cd ..
mkdir build


:: Configure the project with CMake and generate a Visual Studio solution
cmake -G "Visual Studio 16 2019" -A x64 -B build -S .

pause
