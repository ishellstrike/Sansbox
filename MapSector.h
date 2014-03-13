#ifndef MapSector_h__
#define MapSector_h__

#include "Block.h"
#include "Point.h"
#include <map>

class MapSector {
public:
	int a;
	std::map<Point, Block> Blocks;
};

#endif // MapSector_h__
