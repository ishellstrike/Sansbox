#include "Mesh.h"
#include <vector>
#include "VertexPositionTexture.h"
#include <glew.h>
#include "BufferArray.h"
#include <glog\logging.h>

#define OPENGL_CHECK_ERRORS() \
	while( unsigned int openGLError = glGetError() ) \
{ \
	LOG(ERROR) << "OpenGL Error "; \
};

Mesh::Mesh(void)
{
	vao = -1;
	vbo = nullptr;
	texture = nullptr;
	shader = nullptr;
}


Mesh::~Mesh(void)
{
	glDeleteBuffers(2, vbo);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);

	delete vbo;
	vbo = nullptr;
}

void Mesh::Create(std::vector<VertexPositionTexture> v, std::vector<GLuint> i)
{
	verteces.assign(v.begin(), v.end());
	indeces.assign(i.begin(), i.end());
}

void Mesh::Bind()
{
	if(vao == -1){
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		vbo = new GLuint[2];
		glGenBuffers(2, vbo);
	} else {
		glBindVertexArray(vao);
	}
	GLuint stride = sizeof(VertexPositionTexture);
	GLuint offset = 0;
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionTexture)*verteces.size(), &verteces[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(BUFFER_TYPE_VERTEX);
	glVertexAttribPointer(BUFFER_TYPE_VERTEX, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset)); offset += sizeof(Vector3);
	glEnableVertexAttribArray(BUFFER_TYPE_TEXTCOORD);
	glVertexAttribPointer(BUFFER_TYPE_TEXTCOORD, 2, GL_FLOAT, GL_FALSE, stride, (void*)(offset));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indeces.size(), &indeces[0], GL_STATIC_DRAW);

	OPENGL_CHECK_ERRORS();
}

void Mesh::Render()
{
	if(verteces.size() == 0){
		return;
	}
	if(shader != nullptr) {
		shader->BindProgram();
		glUniformMatrix4fv(shader->vars[1], 1, GL_FALSE, &World[0][0]);
	}
	if(texture != nullptr) {
		glBindTexture(GL_TEXTURE_2D, texture->textureId);
	}
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indeces.size(), GL_UNSIGNED_INT, NULL);
}

void Mesh::Combine()
{

}
