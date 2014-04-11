#pragma once
#ifndef VertexPositionTexture_h__
#define VertexPositionTexture_h__

#include "Vector.h"
struct VertexPositionTexture{
public:
	Vector3 pos;
	Vector2 uv;

	VertexPositionTexture operator + (VertexPositionTexture a){ VertexPositionTexture b; b.pos = pos + a.pos; b.uv = a.uv + uv; return b; }
	VertexPositionTexture operator / (float a){ VertexPositionTexture b; b.pos = pos / a; b.uv = uv / a; return b; }
};

struct VertexPositionColor{
public:
	Vector3 pos;
	Color4 col;
};
#endif // VertexPositionTexture_h__
