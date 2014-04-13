#include "Registry.h"
#include <map>
#include <string>
#include "BlockData.h"
#include "DataJsonParser.h"
std::map<std::string, BlockData*>* Registry::Blocks;
void Registry::Initialize()
{
	Blocks = new std::map<std::string, BlockData*>();
	DataJsonParser::ParseDirectory("Data\\Blocks", Blocks);
}
