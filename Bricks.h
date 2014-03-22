#ifndef Bricks_h__
#define Bricks_h__
#include "Block.h"

class Bricks : public Block{
public:
	static int BaseId;
	Bricks();
	~Bricks();
	void Init();
};
#endif // Bricks_h__
