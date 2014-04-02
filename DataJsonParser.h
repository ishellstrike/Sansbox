#pragma once
#ifndef DataJsonParser_h__
#define DataJsonParser_h__

#include <string>
class DataJsonParser
{
public:
	DataJsonParser(void);
	~DataJsonParser(void);
	static std::map<std::string, BlockData>* Parse(std::string s);
	static std::map<std::string, BlockData>* ParseDirectory(std::string s);
};
#endif // DataJsonParser_h__

