#pragma once
#include "Vector.h"
struct DotEntity
{
public:
	DotEntity(void);
	DotEntity(Vector3 p ,Vector3 v, float m);
	~DotEntity(void);
	Vector3 pos;
	Vector3 vel;
	float mass;
};

