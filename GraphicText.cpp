#include "GraphicText.h"
#include "Font.h"
#include "JRectangle.h"
#include <utf8.h>


StringBatch::StringBatch(void) : buffer(false, true, false)
{
	x = 0;
	y = 0;
	z = 0;
	constraintWidth = 0;
	constraintHeight = 0;
}


StringBatch::~StringBatch(void)
{
}

void StringBatch::SetText( std::string text, Font* font )
{
	utf32text.clear();
	utf8::utf8to32(text.begin(), text.end(), std::back_inserter(utf32text));
	buffer.Clear();
	buffer.DeleteVideoBuffer();
	CreateBuffer(font);
}

void StringBatch::CreateBuffer(Font* font)
{
	JRectangle geometryRectangle;
	FontTexture fontTexture;
	float glyphX = x;
	float glyphY = y;
	float stringHeight = 22.0f;

	for(unsigned int i = 0; i < utf32text.size(); i++)
	{
		fontTexture = font->GetGlyphTexture(utf32text[i]);

		geometryRectangle.SetPos(vec3(glyphX, glyphY + stringHeight - fontTexture.height - fontTexture.offsetDown, z));
		geometryRectangle.SetSize((float)fontTexture.width, (float)fontTexture.height);
		geometryRectangle.SetTexture(fontTexture.texture);

		glyphX += fontTexture.width;

		buffer.PushBack(geometryRectangle.GetBufferArray());
	}

	buffer.CreateVideoBuffer("GraphicText " + font->name);

}

void StringBatch::SetPos( const vec3 &pos )
{
	x = pos[0];
	y = pos[1];
	z = pos[2];
}

void StringBatch::Draw(Font* font)
{
	glBindTexture(GL_TEXTURE_2D, font->GetGlyphTexture(0).texture.textureId);
	buffer.Draw();
}

void StringBatch::Draw(std::string s, int x, int y, Font* font)
{
	SetPos(vec3(x,y,-1));
	SetText(s, font);
	Draw(font);
}
