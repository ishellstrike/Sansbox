#ifndef Block_h__
#define Block_h__

#include "MapSector.h"
#include "Point.h"
#include "MapSector.h"

class Block {
public:
	Block();
	~Block();
	void Init();
	//void Update(double time, MapSector* ms);
private:
	static int BaseId;
	unsigned short id;
	unsigned short mtex;
};

#endif //Block_h__