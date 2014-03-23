#ifndef SpriteBatch_h__
#define SpriteBatch_h__
#include <glew.h>
#include "Vector.h"

class SpriteBatch{
private:
	GLuint m_vertexBuffer, m_textureBuffer, m_indecesBuffer, vao;
	Vector2* uv;
	Vector3* vertex;
	GLuint* index;
	float curz;
	int curn;
	int dc;
public:
	SpriteBatch();
	~SpriteBatch();

	void Render();
	void Init();
	void DrawQuad(Vector2 pos);
	int RenderFinally();
};
#endif // SpriteBatch_h__
