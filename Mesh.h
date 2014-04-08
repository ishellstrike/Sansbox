#pragma once
#ifndef Mesh_h__
#define Mesh_h__

#include "VertexPositionTexture.h"
#include <glew.h>
#include <vector>
#include "JargShader.h"
#include "TextureManager.h"
class Mesh
{
public:
	Mesh(void);
	~Mesh(void);
	void Create(std::vector<VertexPositionTexture> v, std::vector<GLuint> i);
	void Bind();
	void Render();
	void Combine();
	std::vector<VertexPositionTexture> verteces;
	std::vector<GLuint> indeces;
	Texture* texture;
	JargShader* shader;
	mat4 World;
private:
	GLuint vao;
	GLuint* vbo;
};
#endif // Mesh_h__

