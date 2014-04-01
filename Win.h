#pragma once
#ifndef Win_h__
#define Win_h__
#include "Vector.h"
#include <detail\type_vec.hpp>
#include <glm.hpp>
#include "WComponent.h"
#include <vector>
class Win : public WContainer
{
public:
	Win(void);
	Win(Vector2 p, Vector2 s);
	~Win(void);
	void Draw();
	void Update();
	Vector2 GlobalPos();
	Vector2 size;
	Vector2 pos;
	std::vector<WComponent*> Items;
};

#endif // Win_h__

