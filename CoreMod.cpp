#include "CoreMod.h"
#include "Block.h"
#include "Bricks.h"

Block *grass;
Bricks *bricks;
void CoreMod::Load()
{
	grass = new Block();
	grass->Init();

	bricks = new Bricks();
	bricks->Init();
}

void CoreMod::Unload()
{
	delete grass;
	delete bricks;
}

