#pragma once
#include "Vector.h"
struct DotEntity
{
public:
	DotEntity(void);
	DotEntity(Vector3 position, Vector3 velocity, float mass);
	~DotEntity(void);
	Vector3 Position;
	Vector3 Velocity;
	float Mass;
};

