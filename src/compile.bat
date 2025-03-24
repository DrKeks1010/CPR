@echo off
gcc main.c glad.c -Wall -o prog.exe -I D:\_C\_dev\CPR\libraries\include D:\_C\_dev\CPR\libraries\lib\libglfw3.a -lgdi32
if %errorlevel% neq 0 exit /b %errorlevel%

.\prog.exe
