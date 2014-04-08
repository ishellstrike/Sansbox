#include "Quad.h"
#include "Mesh.h"


Mesh* Quad::GetMesh()
{
	Mesh* m = new Mesh();

	m->verteces.resize(4);
	m->indeces.resize(6);

	float s2 = 0.5;
	m->verteces[0].pos = Vector3(-s2,-s2,0);
	m->verteces[1].pos = Vector3(s2,-s2,0);
	m->verteces[2].pos = Vector3(-s2,s2,0);
	m->verteces[3].pos = Vector3(s2,s2,0);
	m->verteces[0].uv = Vector2(0,0);
	m->verteces[1].uv = Vector2(1,0);
	m->verteces[2].uv = Vector2(0,1);
	m->verteces[3].uv = Vector2(1,1);

	m->indeces[0] = 0;
	m->indeces[1] = 1;
	m->indeces[2] = 2;
	m->indeces[3] = 1;
	m->indeces[4] = 3;
	m->indeces[5] = 2;

	return m;
}
