@echo off
gcc main.c glad.c -Wall -o prog.exe -I ..\libraries\include -L ..\libraries\lib -l:libglfw3.a -lgdi32
if %errorlevel% neq 0 exit /b %errorlevel%

.\prog.exe
