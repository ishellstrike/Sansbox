#include "SpriteBatch.h"
#include "JRectangle.h"
#include "Vector.h"
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

void SpriteBatch::Init(){
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_indecesBuffer);
	glGenBuffers(1, &m_textureBuffer);
}

void SpriteBatch::Render()
{
	Vector3 verts[4];
	Vector2 uv[4];
	GLuint indeces[6];

	verts[0] = Vector3(0, 0, -1);
	verts[1] = Vector3(100, 0, -1);
	verts[2] = Vector3(0, 100, -1);
	verts[3] = Vector3(100, 100, -1);
	uv[0] = Vector2(0, 0);
	uv[1] = Vector2(1, 0);
	uv[2] = Vector2(0, 1);
	uv[3] = Vector2(1, 1);
	indeces[0] = 0;
	indeces[1] = 1;
	indeces[2] = 2;
	indeces[3] = 1;
	indeces[4] = 2;
	indeces[5] = 3;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3)* 4, verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
	glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2)* 4, uv, GL_STATIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_TEXTCOORD);
	glVertexAttribPointer(BUFFER_TYPE_TEXTCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* 6, indeces, GL_STATIC_DRAW);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
