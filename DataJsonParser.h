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
	static bool Parse(std::string s, std::map<std::string, BlockData*>* blocks);
	static void ParseDirectory(std::string s, std::map<std::string, BlockData*>* blocks);
};
#endif // DataJsonParser_h__

