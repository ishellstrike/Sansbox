#ifndef Rectangle_h__
#define Rectangle_h__

#include "GameMath.h"
#include "TextureManager.h"
#include "Render.h"

class JRectangle
{
private:
	Texture texture;

	float x, y, z;
	float width;
	float height;

	BufferArray buffer;

public:
	JRectangle(void);
	~JRectangle(void);

	void SetSize(float width, float height);
	void SetPos(const vec3 &pos);

	void SetTexture(const Texture &texture);
	Texture GetTexture();

	BufferArray &GetBufferArray();

};


#endif // Rectangle_h__