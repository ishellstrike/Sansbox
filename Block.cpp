#include "Block.h"
#include "Registry.h"

int Block::BaseId = -1;
void Block::Init()
{
	BaseId = Registry::RegisterBlock(*this);
}

Block::Block()
{
	id = 0;
	mtex = 0;
}

Block::~Block()
{

}

