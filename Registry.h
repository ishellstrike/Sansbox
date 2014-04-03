#ifndef Registry_h__
#define Registry_h__
#include <vector>
#include "Block.h"
#include "BlockData.h"

class Registry{
private:
	static std::vector<Block> blockRegistry;
	static std::map<std::string, BlockData*>* Blocks;
public:
	static int RegisterBlock(Block& block);
	static void Init();
};
#endif // Registry_h__
