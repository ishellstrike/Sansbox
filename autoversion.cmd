
@echo off
for /F "tokens=*" %%i in ('git describe --tags HEAD') do echo %%i && set VERSION=%%i
for /F "tokens=*" %%i in ('git show -s --format"=""%%ct"') do echo %%i && set VERSION2=%%i
>AutoVersion.h echo #ifndef AutoVersion_h__ 
>>AutoVersion.h echo #define AutoVersion_h__ 
>>AutoVersion.h echo #include ^<string^>
>>AutoVersion.h echo class AutoVersion { 
>>AutoVersion.h echo public: 
>>AutoVersion.h echo 	static std::string Ver; 
>>AutoVersion.h echo 	static std::string Time;
>>AutoVersion.h echo 	static std::string GetTitle();
>>AutoVersion.h echo };
>>AutoVersion.h echo #endif // AutoVersion_h__   

>AutoVersion.cpp echo #include "AutoVersion.h"
>>AutoVersion.cpp echo std::string AutoVersion::GetTitle()
>>AutoVersion.cpp echo {
>>AutoVersion.cpp echo 	char buff[100];
>>AutoVersion.cpp echo 	sprintf(buff, "%%s %%s %%s %%s", "Jarg", Ver.c_str(), "from", Time.c_str());
>>AutoVersion.cpp echo 	std::string buffAsStdStr = buff;
>>AutoVersion.cpp echo 	return buffAsStdStr;
>>AutoVersion.cpp echo }
>>AutoVersion.cpp echo std::string AutoVersion::Time = "1396372287";
>>AutoVersion.cpp echo std::string AutoVersion::Ver = "v0.0.1-1-g3f77652";