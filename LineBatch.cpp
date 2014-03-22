#include "LineBatch.h"
#include "JRectangle.h"

LineBatch::LineBatch()
{
	buffer.Create(false, true, false);
	zorder = -100;
}

LineBatch::~LineBatch()
{

}

void LineBatch::AddLine(vec2 a, vec2 b, int size)
{
	JRectangle r;
	r.SetPos(vec3(a.x, a.y, zorder));
	r.SetSize(b.x - a.x, b.y - a.y);
	buffer.PushBack(r.GetBufferArray());
	zorder+=0.01;
}

void LineBatch::Draw()
{

}

void LineBatch::Clear()
{

}