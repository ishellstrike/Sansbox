#ifndef SpriteBatch_h__
#define SpriteBatch_h__
#include <glew.h>

class SpriteBatch{
private:
	GLuint m_vertexBuffer, m_textureBuffer, m_indecesBuffer, vao;
public:
	SpriteBatch();
	~SpriteBatch();

	void Render();
	void Init();
};
#endif // SpriteBatch_h__
