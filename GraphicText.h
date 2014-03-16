#ifndef GraphicText_h__
#define GraphicText_h__

#include <string>
#include <vector>
#include "BufferArray.h"
#include "Font.h"

class StringBatch
{
private:
	std::vector<uint32_t> utf32text;

	BufferArray buffer;

	float constraintWidth;
	float constraintHeight;

	float x, y, z;

public:
	StringBatch(void);
	~StringBatch(void);

	void Draw(std::string s, int x, int y, Font* font);

private:
	void CreateBuffer(Font* font);
	void SetPos(const vec3 &pos);

	void SetText(std::string text, Font* font );

	void Draw(Font* font);

};


#endif // GraphicText_h__