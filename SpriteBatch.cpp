#include "SpriteBatch.h"
#include "JRectangle.h"
#include "Vector.h"
#include "TextureManager.h"

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


void SpriteBatch::DrawQuad(Vector2 pos, Vector2 size, float rotation, Texture& tex, int atl)
{
	if(curn == 1000){
		Render();
		DrawQuad(pos, size, rotation, tex, atl);
		return;
	}
	if(tex.textureId != currentTex.textureId){
		Render();
		glBindTexture(GL_TEXTURE_2D, tex.textureId);
		currentTex = tex;
	}
	vertex[4*curn+0] = Vector3(pos.x,        pos.y, curz);
	vertex[4*curn+1] = Vector3(pos.x + size.x, pos.y, curz);
	vertex[4*curn+2] = Vector3(pos.x,        pos.y + size.y, curz);
	vertex[4*curn+3] = Vector3(pos.x + size.x, pos.y + size.y, curz);
	int i = atl%64;
	int j = atl/64;
	Rect aa(i/64.0, (j*32.0)/currentTex.height, 1/64.0, 32.0/currentTex.height);
	uv[4*curn+3] = Vector2(aa.x,        aa.y);
	uv[4*curn+2] = Vector2(aa.x + aa.w, aa.y);
	uv[4*curn+1] = Vector2(aa.x,        aa.y + aa.h);
	uv[4*curn+0] = Vector2(aa.x + aa.w, aa.y + aa.h);
	index[6*curn+0] = 4*curn+0;
	index[6*curn+1] = 4*curn+1;
	index[6*curn+2] = 4*curn+2;
	index[6*curn+3] = 4*curn+1;
	index[6*curn+4] = 4*curn+2;
	index[6*curn+5] = 4*curn+3;
	curn++;
	curz+=0.001f;
}	

void SpriteBatch::DrawQuad(Vector2 pos, Vector2 size, float rotation, Texture& tex, Rect sub)
{
	if(curn == 1000){
		Render();
		DrawQuad(pos, size, rotation, tex, sub);
		return;
	}
	if(tex.textureId != currentTex.textureId){
		Render();
		glBindTexture(GL_TEXTURE_2D, tex.textureId);
		currentTex = tex;
	}
	vertex[4*curn+0] = Vector3(pos.x,        pos.y, curz);
	vertex[4*curn+1] = Vector3(pos.x + size.x, pos.y, curz);
	vertex[4*curn+2] = Vector3(pos.x,        pos.y + size.y, curz);
	vertex[4*curn+3] = Vector3(pos.x + size.x, pos.y + size.y, curz);
	uv[4*curn+3] = Vector2(sub.x,         sub.y);
	uv[4*curn+2] = Vector2(sub.x + sub.w, sub.y);
	uv[4*curn+1] = Vector2(sub.x,         sub.y + sub.h);
	uv[4*curn+0] = Vector2(sub.x + sub.w, sub.y + sub.h);
	index[6*curn+0] = 4*curn+0;
	index[6*curn+1] = 4*curn+1;
	index[6*curn+2] = 4*curn+2;
	index[6*curn+3] = 4*curn+1;
	index[6*curn+4] = 4*curn+2;
	index[6*curn+5] = 4*curn+3;
	curn++;
	curz+=0.001f;
}	

void SpriteBatch::DrawQuad(Vector2 pos, Vector2 size, float rotation, Texture& tex)
{
	if(curn == 1000){
		Render();
		DrawQuad(pos, size, rotation, tex);
		return;
	}
	if(tex.textureId != currentTex.textureId){
		Render();
		glBindTexture(GL_TEXTURE_2D, tex.textureId);
		currentTex = tex;
	}
	vertex[4*curn+0] = Vector3(pos.x,        pos.y, curz);
	vertex[4*curn+1] = Vector3(pos.x + size.x, pos.y, curz);
	vertex[4*curn+2] = Vector3(pos.x,        pos.y + size.y, curz);
	vertex[4*curn+3] = Vector3(pos.x + size.x, pos.y + size.y, curz);
	uv[4*curn+3] = Vector2(0,0);
	uv[4*curn+2] = Vector2(1,0);
	uv[4*curn+1] = Vector2(0,1);
	uv[4*curn+0] = Vector2(1,1);
	index[6*curn+0] = 4*curn+0;
	index[6*curn+1] = 4*curn+1;
	index[6*curn+2] = 4*curn+2;
	index[6*curn+3] = 4*curn+1;
	index[6*curn+4] = 4*curn+2;
	index[6*curn+5] = 4*curn+3;
	curn++;
	curz+=0.001f;
}

void SpriteBatch::DrawQuad(Vector2 pos, Vector2 size, Texture& tex)
{
	if(curn == 1000){
		Render();
		DrawQuad(pos, size, tex);
		return;
	}
	if(tex.textureId != currentTex.textureId){
		Render();
		glBindTexture(GL_TEXTURE_2D, tex.textureId);
		currentTex = tex;
	}
	vertex[4*curn+0] = Vector3(pos.x,        pos.y, curz);
	vertex[4*curn+1] = Vector3(pos.x + size.x, pos.y, curz);
	vertex[4*curn+2] = Vector3(pos.x,        pos.y + size.y, curz);
	vertex[4*curn+3] = Vector3(pos.x + size.x, pos.y + size.y, curz);
	uv[4*curn+3] = Vector2(0,0);
	uv[4*curn+2] = Vector2(1,0);
	uv[4*curn+1] = Vector2(0,1);
	uv[4*curn+0] = Vector2(1,1);
	index[6*curn+0] = 4*curn+0;
	index[6*curn+1] = 4*curn+1;
	index[6*curn+2] = 4*curn+2;
	index[6*curn+3] = 4*curn+1;
	index[6*curn+4] = 4*curn+2;
	index[6*curn+5] = 4*curn+3;
	curn++;
	curz+=0.001f;
}

int SpriteBatch::RenderFinally()
{
	if(curn == 0) {
		return 0;
	}
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, currentTex.textureId);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3)*curn*4, vertex, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
	glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2)*curn*4, uv, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_TEXTCOORD);
	glVertexAttribPointer(BUFFER_TYPE_TEXTCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*curn*6, index, GL_DYNAMIC_DRAW);


	glDrawElements(GL_TRIANGLES, curn*6, GL_UNSIGNED_INT, NULL);
	curz = -90;
	curn = 0;
	dc++;
	int dcc = dc;
	dc = 0;
	return dcc;
}
			
void SpriteBatch::Render()
{
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3)*curn*4, vertex, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
	glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2)*curn*4, uv, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_TEXTCOORD);
	glVertexAttribPointer(BUFFER_TYPE_TEXTCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*curn*6, index, GL_DYNAMIC_DRAW);


	glDrawElements(GL_TRIANGLES, curn*6, GL_UNSIGNED_INT, NULL);
	curn = 0;
	dc++;
}
