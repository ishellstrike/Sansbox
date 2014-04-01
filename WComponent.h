#pragma once
#ifndef WComponent_h__
#define WComponent_h__
#include "Vector.h"

class WComponent {
public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual Vector2 GlobalPos() = 0;
};

class WContainer {
public:
	virtual Vector2 GlobalPos() = 0;
};
#endif // WComponent_h__
