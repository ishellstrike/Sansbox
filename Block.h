#ifndef Block_h__
#define Block_h__

#include "MapSector.h"
#include "Point.h"

class Block {
public:
	Block();
	~Block();
	virtual void Init();
	//virtual void Update(double time, MapSector& ms);
private:
	static int BaseId;
	unsigned short id;
	unsigned short mtex;
};

#endif //Block_h__