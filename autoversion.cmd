
@echo off
for /F "tokens=*" %%i in ('git describe --tags HEAD') do echo %%i && set VERSION=%%i
for /F "tokens=*" %%i in ('git show -s --format"=""%%ct"') do echo %%i && set VERSION2=%%i
>AutoVersion.h echo public class Version{public static string Version = "%VERSION%"; public static string Time = %VERSION2%";}