#ifndef Registry_h__
#define Registry_h__
#include <vector>
#include "Block.h"

class Registry{
private:
	static std::vector<Block> blockRegistry;
public:
	static int RegisterBlock(Block& block);
	static void Init();
};
#endif // Registry_h__
