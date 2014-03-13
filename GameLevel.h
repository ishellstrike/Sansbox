#ifndef GameLevel_h__
#define GameLevel_h__

#include "MapSector.h"

class GameLevel{
public:
	std::map<Point, MapSector> ActiveSectors;
};

#endif // GameLevel_h__
