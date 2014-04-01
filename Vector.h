#ifndef Vector_h__
#define Vector_h__

struct Color4 {
public:
	float r, g, b, a;
	static Color4 White;
	static Color4 Red;
	Color4();
	Color4(float a_, float r_, float g_, float b_);
	Color4(int a_, int r_, int g_, int b_);
	~Color4();
private:
	inline int clamp(int a, int min, int max);
};
struct Vector2 {
public:
	float x, y;
	Vector2();
	Vector2(float a, float b);
	Vector2(float a);
	~Vector2();
	Vector2 operator + (Vector2 a){return Vector2(x + a.x, y + a.y);}
	void operator += (Vector2 a){x += a.x; y += a.y;}
	Vector2 operator - (Vector2 a){return Vector2(x - a.x, y - a.y);}
	Vector2 operator - (){return Vector2(-x, -y);}
	void operator -= (Vector2 a){x -= a.x; y -= a.y;}
	Vector2 operator * (float a){return Vector2(x * a, y * a);}
	void operator *= (float a){x = x * a; y = y * a;}
	bool operator > (Vector2 a){return (x > a.x && y > a.y);}
	bool operator >= (Vector2 a){return (x >= a.x && y >= a.y);}
	bool operator < (Vector2 a){return (x < a.x && y < a.y);}
	bool operator <= (Vector2 a){return (x <= a.x && y <= a.y);}
	bool operator == (Vector2 a){return (x == a.x && y == a.y);}
	bool operator != (Vector2 a){return (x != a.x && y != a.y);}
};

struct Vector3 {
	float x, y, z;
	Vector3();
	Vector3(float a, float b, float c);
	Vector3(float a);
	~Vector3();
};
#endif // Vector_h__
