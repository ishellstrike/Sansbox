#include "SpriteBatch.h"
#include "JRectangle.h"
#include "Vector.h"

SpriteBatch::SpriteBatch()
{
	m_textureBuffer = 0;
	m_vertexBuffer = 0;
	m_indecesBuffer = 0;
	vao = 0;
	uv = new Vector2[1000*4];
	vertex = new Vector3[1000*4];
	index = new GLuint[1000*6];
	curz = -90;
	curn = 0;
}

SpriteBatch::~SpriteBatch()
{
	delete[] uv;
	delete[] vertex;
	delete[] index;

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

void SpriteBatch::DrawQuad(Vector2 pos){
	if(curn == 1000){
		Render();
		DrawQuad(pos);
		return;
	}
	vertex[4*curn+0] = Vector3(pos.x, pos.y, curz);
	vertex[4*curn+1] = Vector3(pos.x+100, pos.y, curz);
	vertex[4*curn+2] = Vector3(pos.x, pos.y+100, curz);
	vertex[4*curn+3] = Vector3(pos.x+100, pos.y+100, curz);
	uv[4*curn+0] = Vector2(0, 0);
	uv[4*curn+1] = Vector2(1, 0);
	uv[4*curn+2] = Vector2(0, 1);
	uv[4*curn+3] = Vector2(1, 1);
	index[6*curn+0] = 6*curn+0;
	index[6*curn+1] = 6*curn+1;
	index[6*curn+2] = 6*curn+2;
	index[6*curn+3] = 6*curn+1;
	index[6*curn+4] = 6*curn+2;
	index[6*curn+5] = 6*curn+3;
	curn++;
	curz+=0.001f;
}		

int SpriteBatch::RenderFinally()
{
	if(curn == 0) {
		return 0;
	}
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3)*curn*4, vertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
	glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2)*curn*4, uv, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_TEXTCOORD);
	glVertexAttribPointer(BUFFER_TYPE_TEXTCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*curn*6, index, GL_STATIC_DRAW);


	glDrawElements(GL_TRIANGLES, curn*6, GL_UNSIGNED_INT, NULL);
	curz = -90;
	curn = 0;
	int dcc = dc;
	dc = 0;
	return dcc;
}
			
void SpriteBatch::Render()
{
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3)*curn*4, vertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
	glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2)*curn*4, uv, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_TEXTCOORD);
	glVertexAttribPointer(BUFFER_TYPE_TEXTCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*curn*6, index, GL_STATIC_DRAW);


	glDrawElements(GL_TRIANGLES, curn*6, GL_UNSIGNED_INT, NULL);
	curn = 0;
	dc++;
}
