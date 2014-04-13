#pragma once
#ifndef DataJsonParser_h__
#define DataJsonParser_h__
#include <string>
#include <map>
#include "BlockData.h"
class DataJsonParser
{
public:
	DataJsonParser(void);
	~DataJsonParser(void);
	static bool Parse(std::string fileName, std::map<std::string, BlockData*>* blockDataBase);
	static void ParseDirectory(std::string directoryName, std::map<std::string, BlockData*>* blockDataBase);
};
#endif // DataJsonParser_h__

