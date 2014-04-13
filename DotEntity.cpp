#include "DotEntity.h"


DotEntity::DotEntity(void)
{
}

DotEntity::DotEntity(Vector3 p ,Vector3 v, float m)
{
	Velocity = v;
	Position = p;
	Mass = m;
}


DotEntity::~DotEntity(void)
{
}
