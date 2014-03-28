#ifndef SpriteBatch_h__
#define SpriteBatch_h__
#include <glew.h>
#include "Vector.h"
#include "TextureManager.h"
#include "JargShader.h"
#include "Font.h"

class Batched{
private:
	GLuint m_vertexBuffer, m_textureBuffer, m_indecesBuffer, vao;
	vec2* uv;
	vec3* vertex;
	GLuint* index;

	GLuint l_vertexBuffer, l_colorBuffer, l_indecesBuffer, lvao;
	vec3* lvertex;
	Color4* lcolor;
	GLuint* lindex;

	float curz;
	int curn, lcurn;
	int dc;
	Texture* currentTex;
	Texture* blankTex;
	Font* currentFont;
	JargShader* textured;
	JargShader* colored;
public:
	Batched();
	~Batched();

	void DrawString(vec2 pos, std::string text, Font& font);
	void Init(JargShader* tex, JargShader* col);
	void DrawQuad(vec2 pos, vec2 size, float rotation, Texture& tex, Rect sub);
	void DrawQuad(vec2 pos, vec2 size, float rotation, Texture& tex, int atl);
	void DrawQuad(vec2 pos, vec2 size, float rotation, Texture& tex);
	void DrawQuad(vec2 pos, vec2 size, Texture& tex);
	int RenderFinally();
	void DrawLine(vec2 from, vec2 to, float w, Color4 col);
	void DrawRectangle(vec2 from, vec2 to, Color4 col);
private:
	inline void innerDraw(vec2 pos, vec2 size, float rotation, Texture& tex, Rect sub);
	void LRender();
	void Render();
};
#endif // SpriteBatch_h__
