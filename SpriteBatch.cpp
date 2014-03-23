#include "SpriteBatch.h"
#include "JRectangle.h"
SpriteBatch::SpriteBatch()
{
	m_textureBuffer = 0;
	m_vertexBuffer = 0;
	m_indecesBuffer = 0;
	vao = 0;
}

SpriteBatch::~SpriteBatch()
{
	if(m_indecesBuffer){
		glDeleteBuffers(1, &m_indecesBuffer);
	}
	if(m_vertexBuffer){
		glDeleteBuffers(1, &m_vertexBuffer);
	}
	if(m_textureBuffer){
		glDeleteBuffers(1, &m_textureBuffer);
	}
	if(vao){
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
	}
}

void SpriteBatch::Render()
{
	Vector3[] verts;
	JRectangle jr;
	jr.SetSize(10,10);
	jr.SetPos( vec3(10,10,-1));

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0])* 4, verts, GL_STATIC_DRAW);
}

