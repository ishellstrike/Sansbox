#ifndef SpriteBatch_h__
#define SpriteBatch_h__
#include <glew.h>
#include "Vector.h"
#include "TextureManager.h"

class SpriteBatch{
private:
	GLuint m_vertexBuffer, m_textureBuffer, m_indecesBuffer, vao;
	Vector2* uv;
	Vector3* vertex;
	GLuint* index;
	float curz;
	int curn;
	int dc;
	Texture currentTex;
public:
	SpriteBatch();
	~SpriteBatch();

	void Render();
	void Init();
	void DrawQuad(Vector2 pos, Vector2 size, float rotation, Texture& tex, Rect sub);
	void DrawQuad(Vector2 pos, Vector2 size, float rotation, Texture& tex, int atl);
	void DrawQuad(Vector2 pos, Vector2 size, float rotation, Texture& tex);
	int RenderFinally();
};
#endif // SpriteBatch_h__
