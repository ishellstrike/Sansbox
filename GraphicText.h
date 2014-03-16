#ifndef GraphicText_h__
#define GraphicText_h__

#include <string>
#include <vector>
#include "BufferArray.h"
#include "Font.h"

class GraphicText
{
private:
	std::vector<uint32_t> utf32text;

	BufferArray buffer;

	float constraintWidth;
	float constraintHeight;

	float x, y, z;

public:
	GraphicText(void);
	~GraphicText(void);

	void SetPos(const vec3 &pos);

	void SetText(std::string text, Font* font );

	void Draw(Font* font);

private:
	void CreateBuffer(Font* font);

};


#endif // GraphicText_h__