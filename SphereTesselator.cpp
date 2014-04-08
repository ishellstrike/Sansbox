#include "SphereTesselator.h"
#include "Mesh.h"

#define sqr(x)(x)*(x);

Mesh* Tesselator::Tesselate(int iters, const Mesh& mesh)
{
	Mesh* m = new Mesh(mesh);
	for (int i = 0; i< iters; i++)
	{
		auto temp = SubTesselate(*m);
		delete m;
		m = temp;
	}
	return m;
}

Mesh* Tesselator::SphereTesselate(int iters, const Mesh& mesh)
{
	Mesh* m = new Mesh(mesh);
	for (int i = 0; i< iters; i++)
	{
		auto temp = SphereSubTesselate(*m);
		delete m;
		m = temp;
		temp = nullptr;
	}
	return m;
}

Mesh* Tesselator::SphereSubTesselate(const Mesh& mesh)
{
	Mesh* m = new Mesh();

	int off = 0;
	for (int i =0; i< mesh.indeces.size() -2; i+= 3)
	{
		VertexPositionTexture t;

		VertexPositionTexture v0 = mesh.verteces[mesh.indeces[i]];
		VertexPositionTexture v1 = mesh.verteces[mesh.indeces[i+1]];
		VertexPositionTexture v2 = mesh.verteces[mesh.indeces[i+2]];

		t = v0;
		t.pos.Normalize();
		m->verteces.push_back(t);
		t = v1;
		t.pos.Normalize();
		m->verteces.push_back(t);
		t = v2;
		t.pos.Normalize();
		m->verteces.push_back(t);

		t = (v0 + v1)/2;
		t.pos.Normalize();
		m->verteces.push_back(t);

		t = (v0 + v2)/2;
		t.pos.Normalize();
		m->verteces.push_back(t);

		t = (v1 + v2)/2;
		t.pos.Normalize();
		m->verteces.push_back(t);

		m->indeces.push_back(off+0);
		m->indeces.push_back(off+3);
		m->indeces.push_back(off+4);

		m->indeces.push_back(off+3);
		m->indeces.push_back(off+1);
		m->indeces.push_back(off+5);

		m->indeces.push_back(off+5);
		m->indeces.push_back(off+2);
		m->indeces.push_back(off+4);

		m->indeces.push_back(off+3);
		m->indeces.push_back(off+5);
		m->indeces.push_back(off+4);

		off+=6;
	}
	return m;
}

Mesh* Tesselator::SubTesselate(const Mesh& mesh)
{
	Mesh* m = new Mesh();

	int off = 0;
	for (int i =0; i< mesh.indeces.size() -2; i+= 3)
	{
		VertexPositionTexture t;

		m->verteces.push_back(mesh.verteces[mesh.indeces[i]]);
		m->verteces.push_back(mesh.verteces[mesh.indeces[i+1]]);
		m->verteces.push_back(mesh.verteces[mesh.indeces[i+2]]);

		t.pos.x = (mesh.verteces[mesh.indeces[i]].pos.x + mesh.verteces[mesh.indeces[i+1]].pos.x)/2;
		t.pos.y = (mesh.verteces[mesh.indeces[i]].pos.y + mesh.verteces[mesh.indeces[i+1]].pos.y)/2;
		t.pos.z = (mesh.verteces[mesh.indeces[i]].pos.z + mesh.verteces[mesh.indeces[i+1]].pos.z)/2;
		t.uv.x = (mesh.verteces[mesh.indeces[i]].uv.x + mesh.verteces[mesh.indeces[i+1]].uv.x)/2;
		t.uv.y = (mesh.verteces[mesh.indeces[i]].uv.y + mesh.verteces[mesh.indeces[i+1]].uv.y)/2;
		m->verteces.push_back(t);

		t.pos.x = (mesh.verteces[mesh.indeces[i]].pos.x + mesh.verteces[mesh.indeces[i+2]].pos.x)/2;
		t.pos.y = (mesh.verteces[mesh.indeces[i]].pos.y + mesh.verteces[mesh.indeces[i+2]].pos.y)/2;
		t.pos.z = (mesh.verteces[mesh.indeces[i]].pos.z + mesh.verteces[mesh.indeces[i+2]].pos.z)/2;
		t.uv.x = (mesh.verteces[mesh.indeces[i]].uv.x + mesh.verteces[mesh.indeces[i+2]].uv.x)/2;
		t.uv.y = (mesh.verteces[mesh.indeces[i]].uv.y + mesh.verteces[mesh.indeces[i+2]].uv.y)/2;
		m->verteces.push_back(t);

		t.pos.x = (mesh.verteces[mesh.indeces[i+1]].pos.x + mesh.verteces[mesh.indeces[i+2]].pos.x)/2;
		t.pos.y = (mesh.verteces[mesh.indeces[i+1]].pos.y + mesh.verteces[mesh.indeces[i+2]].pos.y)/2;
		t.pos.z = (mesh.verteces[mesh.indeces[i+1]].pos.z + mesh.verteces[mesh.indeces[i+2]].pos.z)/2;
		t.uv.x = (mesh.verteces[mesh.indeces[i+1]].uv.x + mesh.verteces[mesh.indeces[i+2]].uv.x)/2;
		t.uv.y = (mesh.verteces[mesh.indeces[i+1]].uv.y + mesh.verteces[mesh.indeces[i+2]].uv.y)/2;
		m->verteces.push_back(t);

		m->indeces.push_back(off+0);
		m->indeces.push_back(off+3);
		m->indeces.push_back(off+4);

		m->indeces.push_back(off+3);
		m->indeces.push_back(off+1);
		m->indeces.push_back(off+5);

		m->indeces.push_back(off+5);
		m->indeces.push_back(off+2);
		m->indeces.push_back(off+4);

		m->indeces.push_back(off+3);
		m->indeces.push_back(off+5);
		m->indeces.push_back(off+4);

		off+=6;
	}
	return m;
}
