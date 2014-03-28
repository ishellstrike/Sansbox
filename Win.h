#pragma once
#ifndef Win_h__
#define Win_h__
#include "Vector.h"
#include <detail\type_vec.hpp>
#include <glm.hpp>
class Win
{
public:
	Win(void);
	Win(glm::vec2 p, glm::vec2 s);
	~Win(void);

	void Draw();

	glm::vec2 size;
	glm::vec2 pos;
};

#endif // Win_h__

