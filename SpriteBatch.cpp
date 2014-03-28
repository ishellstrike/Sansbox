#include "SpriteBatch.h"
#include "JRectangle.h"
#include "Vector.h"
#include "TextureManager.h"
#include "Font.h"
#include <utf8\unchecked.h>
#include <utf8\checked.h>

Batched::Batched()
{
	uv = new vec2[1000*4];
	vertex = new vec3[1000*4];
	index = new GLuint[1000*6];

	lvertex = new vec3[1000*4];
	lindex = new GLuint[1000*6];
	lcolor = new Color4[1000*4];
	m_textureBuffer = m_vertexBuffer = m_indecesBuffer = l_colorBuffer = l_vertexBuffer = lvao = vao = curn = lcurn = 0;
	curz = -1;
	blankTex = new Texture();
	blankTex->name = "blank";
	blankTex->textureId = 0;
	currentTex = blankTex;
}

Batched::~Batched()
{
	delete[] uv;
	delete[] vertex;
	delete[] index;

	delete[] lcolor;
	delete[] lvertex;
	delete[] lindex;

	delete blankTex;

	glDeleteBuffers(1, &m_indecesBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_textureBuffer);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);

	glDeleteBuffers(1, &l_vertexBuffer);
	glDeleteBuffers(1, &l_indecesBuffer);
	glDeleteBuffers(1, &l_colorBuffer);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &lvao);
}

void Batched::Init(JargShader* tex, JargShader* col){
	textured = tex;
	colored = col;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_indecesBuffer);
	glGenBuffers(1, &m_textureBuffer);

	glGenVertexArrays(1, &lvao);
	glBindVertexArray(lvao);

	glGenBuffers(1, &l_vertexBuffer);
	glGenBuffers(1, &l_indecesBuffer);
	glGenBuffers(1, &l_colorBuffer);
}

void Batched::DrawString(vec2 pos, std::string text, Font& font){
	std::vector<uint32_t> utf32text;
	utf32text.push_back(117);utf32text.push_back(117);utf32text.push_back(117);utf32text.push_back(117);utf32text.push_back(117);utf32text.push_back(117);utf32text.push_back(117);utf32text.push_back(117);
	//utf8::utf8to32(text.begin(), text.end(), std::back_inserter(utf32text));
	currentFont = &font;

	JRectangle geometryRectangle;
	FontTexture fontTexture;
	float glyphX = pos.x;
	float glyphY = pos.y;
	float stringHeight = 22.0f;

	fontTexture = font.GetGlyphTexture(utf32text[0]);
	if(curn > 1000 - utf32text.size() - 1){
		Render();
	}
	if(font.tex->textureId != currentTex->textureId){
		Render();
		currentTex = font.tex;
	}
	for(unsigned int i = 0; i < utf32text.size(); i++)
	{
		float ypos = glyphY + stringHeight - fontTexture.height - fontTexture.offsetDown;
		//innerDraw( vec2(glyphX, ypos), vec2((float)fontTexture.width, (float)fontTexture.height), 0, fontTexture.texture.textureId, Rect(fontTexture.texture.u1, fontTexture.texture.v1, fontTexture.texture.u2 - fontTexture.texture.u1, fontTexture.texture.v2 - fontTexture.texture.v1));
		vertex[4*curn+0] = vec3(glyphX, ypos, curz);
		vertex[4*curn+1] = vec3(glyphX, ypos + (float)fontTexture.height, curz);
		vertex[4*curn+2] = vec3(glyphX + (float)fontTexture.width, ypos + (float)fontTexture.height, curz);
		vertex[4*curn+3] = vec3(glyphX + (float)fontTexture.width, ypos, curz);
		uv[4*curn+0] = vec2(fontTexture.texture.u1, fontTexture.texture.v2);
		uv[4*curn+1] = vec2(fontTexture.texture.u1, fontTexture.texture.v1);
		uv[4*curn+2] = vec2(fontTexture.texture.u2, fontTexture.texture.v1);
		uv[4*curn+3] = vec2(fontTexture.texture.u2, fontTexture.texture.v2);
		index[6*curn+0] = 4*curn+2;
		index[6*curn+1] = 4*curn+3;
		index[6*curn+2] = 4*curn+0;
		index[6*curn+3] = 4*curn+0;
		index[6*curn+4] = 4*curn+1;
		index[6*curn+5] = 4*curn+2;
		curn++;

		glyphX += fontTexture.width;

		//auto ar = geometryRectangle.GetBufferArray();
	}
	//curz+=0.001f;
}

inline void Batched::innerDraw(vec2 pos, vec2 size, float rotation, Texture& tex, Rect sub){
	if(curn == 1000){
		Render();
	}
	if(tex.textureId != currentTex->textureId){
		Render();
		currentTex = &tex;
	}
	vertex[4*curn+0] = vec3(pos.x, pos.y, curz);
	vertex[4*curn+1] = vec3(pos.x + size.x, pos.y, curz);
	vertex[4*curn+2] = vec3(pos.x, pos.y + size.y, curz);
	vertex[4*curn+3] = vec3(pos.x + size.x, pos.y + size.y, curz);
	uv[4*curn+3] = vec2(sub.x, sub.y);
	uv[4*curn+2] = vec2(sub.x + sub.w, sub.y);
	uv[4*curn+1] = vec2(sub.x, sub.y + sub.h);
	uv[4*curn+0] = vec2(sub.x + sub.w, sub.y + sub.h);
	index[6*curn+0] = 4*curn+0;
	index[6*curn+1] = 4*curn+1;
	index[6*curn+2] = 4*curn+2;
	index[6*curn+3] = 4*curn+1;
	index[6*curn+4] = 4*curn+2;
	index[6*curn+5] = 4*curn+3;
	curn++;
	//curz+=0.001f;
}

void Batched::DrawQuad(vec2 pos, vec2 size, float rotation, Texture& tex, Rect sub)
{
	innerDraw(pos, size, rotation, tex, sub);
}	

void Batched::DrawQuad(vec2 pos, vec2 size, float rotation, Texture& tex, int atl)
{
	int i = atl%64;
	int j = atl/64;
	Rect aa(i/64.0, (j*32.0)/tex.height, 1/64.0, 32.0/tex.height);
	innerDraw(pos, size, rotation, tex, aa);
}

void Batched::DrawQuad(vec2 pos, vec2 size, float rotation, Texture& tex)
{
	innerDraw(pos, size, rotation, tex, Rect(0,0,1,1));
}

void Batched::DrawQuad(vec2 pos, vec2 size, Texture& tex)
{
	innerDraw(pos, size, 0, tex, Rect(0,0,1,1));
}

void Batched::DrawLine(vec2 from, vec2 to, float w, Color4 col){
	if(lcurn == 1000){
		LRender();
	}
	lvertex[4*lcurn+0] = vec3(from.x - 1, from.y + 1, curz);
	lvertex[4*lcurn+1] = vec3(from.x + 1, from.y - 1, curz);
	lvertex[4*lcurn+2] = vec3(to.x - 1, to.y + 1, curz);
	lvertex[4*lcurn+3] = vec3(to.x + 1, to.y - 1, curz);
	lcolor[4*lcurn+3] = col;
	lcolor[4*lcurn+2] = col;
	lcolor[4*lcurn+1] = col;
	lcolor[4*lcurn+0] = col;
	lindex[6*lcurn+0] = 4*lcurn+0;
	lindex[6*lcurn+1] = 4*lcurn+1;
	lindex[6*lcurn+2] = 4*lcurn+2;
	lindex[6*lcurn+3] = 4*lcurn+1;
	lindex[6*lcurn+4] = 4*lcurn+2;
	lindex[6*lcurn+5] = 4*lcurn+3;
	lcurn++;
	curz+=0.001f;
}

void Batched::DrawRectangle(vec2 pos, vec2 size, Color4 col){
	if(lcurn == 1000){
		LRender();
	}
	lvertex[4*lcurn+0] = vec3(pos.x, pos.y, curz);
	lvertex[4*lcurn+1] = vec3(pos.x + size.x, pos.y, curz);
	lvertex[4*lcurn+2] = vec3(pos.x, pos.y + size.y, curz);
	lvertex[4*lcurn+3] = vec3(pos.x + size.x, pos.y + size.y, curz);
	lcolor[4*lcurn+3] = col;
	lcolor[4*lcurn+2] = col;
	lcolor[4*lcurn+1] = col;
	lcolor[4*lcurn+0] = col;
	lindex[6*lcurn+0] = 4*lcurn+0;
	lindex[6*lcurn+1] = 4*lcurn+1;
	lindex[6*lcurn+2] = 4*lcurn+2;
	lindex[6*lcurn+3] = 4*lcurn+1;
	lindex[6*lcurn+4] = 4*lcurn+2;
	lindex[6*lcurn+5] = 4*lcurn+3;
	lcurn++;
	curz+=0.001f;
}

int Batched::RenderFinally()
{
	if(curn != 0) {
		glBindVertexArray(vao);
		textured->BindProgram();
		glBindTexture(GL_TEXTURE_2D, currentTex->textureId);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*curn*4, vertex, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
		glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*curn*4, uv, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(BUFFER_TYPE_TEXTCOORD);
		glVertexAttribPointer(BUFFER_TYPE_TEXTCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indecesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*curn*6, index, GL_DYNAMIC_DRAW);


		glDrawElements(GL_TRIANGLES, curn*6, GL_UNSIGNED_INT, NULL);
		dc++;
	}
	if(lcurn != 0) {
		glBindVertexArray(lvao);
		colored->BindProgram();

		glBindBuffer(GL_ARRAY_BUFFER, l_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*lcurn*4, lvertex, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
		glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

		glBindBuffer(GL_ARRAY_BUFFER, l_colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Color4)*lcurn*4, lcolor, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(BUFFER_TYPE_COLOR);
		glVertexAttribPointer(BUFFER_TYPE_COLOR, 2, GL_FLOAT, GL_FALSE, sizeof(Color4), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, l_indecesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*lcurn*6, lindex, GL_DYNAMIC_DRAW);


		glDrawElements(GL_TRIANGLES, lcurn*6, GL_UNSIGNED_INT, NULL);
		dc++;
	}

	curz = -90;
	curn = 0;
	lcurn = 0;
	int dcc = dc;
	dc = 0;
	return dcc;
}
			
void Batched::Render()
{
	if(curn == 0) {
		return;
	}
	glBindVertexArray(vao);
	textured->BindProgram();
	glBindTexture(GL_TEXTURE_2D, currentTex->textureId);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*curn*4, vertex, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
	glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*curn*4, uv, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_TEXTCOORD);
	glVertexAttribPointer(BUFFER_TYPE_TEXTCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*curn*6, index, GL_DYNAMIC_DRAW);


	glDrawElements(GL_TRIANGLES, curn*6, GL_UNSIGNED_INT, NULL);
	curn = 0;
	dc++;
}

void Batched::LRender()
{
	if(lcurn == 0) {
		return;
	}
	glBindVertexArray(lvao);
	colored->BindProgram();

	glBindBuffer(GL_ARRAY_BUFFER, l_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*lcurn*4, lvertex, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
	glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, l_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Color4)*lcurn*4, lcolor, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_COLOR);
	glVertexAttribPointer(BUFFER_TYPE_COLOR, 2, GL_FLOAT, GL_FALSE, sizeof(Color4), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, l_indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*lcurn*6, lindex, GL_DYNAMIC_DRAW);


	glDrawElements(GL_TRIANGLES, lcurn*6, GL_UNSIGNED_INT, NULL);
	dc++;
	lcurn = 0;
}
