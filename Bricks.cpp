#include "Bricks.h"
#include "Registry.h"

void Bricks::Init()
{
	BaseId = Registry::RegisterBlock(*this);
}

Bricks::Bricks()
{
	id = 0;
	mtex = 0;
}

Bricks::~Bricks()
{

}

