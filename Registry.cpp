#include "Registry.h"
#include "Block.h"
#include <map>

std::vector<Block> Registry::blockRegistry;
int Registry::RegisterBlock(Block& block)
{
	blockRegistry.push_back(block);
	return blockRegistry.size();
}

void Registry::Init()
{
	
}

