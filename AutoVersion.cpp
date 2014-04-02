#include "AutoVersion.h"
std::string AutoVersion::GetTitle()
{
	char buff[100];
	sprintf(buff, "%s %s %s %s", "Jarg", Ver.c_str(), "from", Time.c_str());
	std::string buffAsStdStr = buff;
	return buffAsStdStr;
}
std::string AutoVersion::Time = "1396372287";
std::string AutoVersion::Ver = "v0.0.1-1-g3f77652";
