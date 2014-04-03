#include "Registry.h"
#include "Block.h"
#include <map>
#include <string>
#include "BlockData.h"
#include "DataJsonParser.h"

std::vector<Block> Registry::blockRegistry;
int Registry::RegisterBlock(Block& block)
{
	blockRegistry.push_back(block);
	return blockRegistry.size();
}

void Registry::Init()
{
	Blocks = new std::map<std::string, BlockData*>();
	DataJsonParser::ParseDirectory("Data\\Blocks", Blocks);
}

std::map<std::string, BlockData*>* Registry::Blocks;

