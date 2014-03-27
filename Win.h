#pragma once
#include "Vector.h"
#ifndef Win_h__
#define Win_h__

class Win
{
public:
	Win(void);
	Win(Vector2 p, Vector2 s);
	~Win(void);

	void Draw();

	Vector2 size;
	Vector2 pos;
};

#endif // Win_h__

