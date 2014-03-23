#ifndef Vector_h__
#define Vector_h__

struct Vector2 {
public:
	float x, y;
	Vector2();
	Vector2(float a, float b);
	Vector2(float a);
	~Vector2();
};

struct Vector3 {
	float x, y, z;
	Vector3();
	Vector3(float a, float b, float c);
	Vector3(float a);
	~Vector3();
};
#endif // Vector_h__
