#pragma once
#ifndef BlockData_h__
#define BlockData_h__
#include <vector>
class DropGroup {
public:
	std::vector<std::string> Ids;
	int Min, Max, Prob, Repeat;
	DropGroup(){};
	~DropGroup(){};
};

class BlockData {
public:
	BlockData(){};
	~BlockData(){};
	std::string Id;

	std::string AfterDeathId;
	std::vector<std::string> AlterMtex;

	float Damage;
	std::string Description;

	float Hp;
	bool IsDestructable, IsTransparent, IsWalkable, Wallmaker;
	std::string MTex;
	std::string Name;
	std::string Type;
	float Height;

	std::vector<DropGroup> ItemSpawn;

	int swide;

	std::string RandomMtexFromAlters() {
		if (AlterMtex.size() != 0)
		{
			return AlterMtex[rand()%AlterMtex.size()];
		}
		return MTex;
	}
};
#endif // BlockData_h__