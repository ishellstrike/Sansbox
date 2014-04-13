#pragma once
#ifndef Registry_h__
#define Registry_h__
#include <vector>
#include "BlockData.h"
#include <string>
#include <map>

class Registry{
private:
	static std::map<std::string, BlockData*>* Blocks;
public:
	static void Initialize();
};
#endif // Registry_h__
