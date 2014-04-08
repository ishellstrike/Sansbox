#include "DotEntity.h"


DotEntity::DotEntity(void)
{
}

DotEntity::DotEntity(Vector3 p ,Vector3 v, float m)
{
	vel = v;
	pos = p;
	mass = m;
}


DotEntity::~DotEntity(void)
{
}
