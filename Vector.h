#ifndef Vector_h__
#define Vector_h__

struct Color4 {
public:
	float r, g, b, a;
	static Color4 White;
	Color4();
	Color4(float a_, float r_, float g_, float b_);
	Color4(int a_, int r_, int g_, int b_);
	~Color4();
private:
	inline int clamp(int a, int min, int max);
};
#endif // Vector_h__
