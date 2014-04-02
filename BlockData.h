#pragma once
#ifndef BlockData_h__
#define BlockData_h__
#include <vector>
class BlockData {
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
}

class DropGroup {
	std::vector<std::string> Ids;
	int Min, Max, Prob, Repeat;
}
#endif // BlockData_h__