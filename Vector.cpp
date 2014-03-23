#include "Vector.h"
Vector2::Vector2()
{
	x = y = 0;
}

Vector2::Vector2(float a, float b)
{
	x = a; y = b;
}

Vector2::Vector2(float a)
{
	x = y = a;
}

Vector2::~Vector2()
{

}


Vector3::Vector3()
{
	x = y = z = 0;
}

Vector3::Vector3(float a, float b, float c)
{
	x = a; y = b; z = c;
}

Vector3::Vector3(float a)
{
	x = y = z = a;
}

Vector3::~Vector3()
{

}
