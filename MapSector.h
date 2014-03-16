#ifndef MapSector_h__
#define MapSector_h__

#include "Block.h"
#include "Point.h"
#include <map>
#include <string>

class MapSector {
public:
	int a;
	std::map<Point, Block> Blocks;
	int SectorOffsetX, SectorOffsetY;
	static const int Rx = 25, Ry = 25;
	void SetFloor(int i, int j, int id);

};
#endif // MapSector_h__
