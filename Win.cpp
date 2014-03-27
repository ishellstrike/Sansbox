#include "Win.h"
#include "Vector.h"
#include "WinS.h"


Win::Win(void)
{
}

Win::Win(Vector2 p, Vector2 s)
{
	size = s;
	pos = p;
}


Win::~Win(void)
{
}

void Win::Draw()
{
	WinS::sb->DrawQuad(pos, Vector2(size.x, 2), 0, *WinS::bp);
	WinS::sb->DrawQuad(Vector2(pos.x, pos.y + 20), Vector2(size.x, 2), 0, *WinS::bp);
	WinS::sb->DrawQuad(pos, Vector2(2, size.y), 0, *WinS::bp);
	WinS::sb->DrawQuad(Vector2(pos.x + size.x - 2, pos.y), Vector2(2, size.y), 0, *WinS::bp);
	WinS::sb->DrawQuad(Vector2(pos.x, pos.y + size.y - 2), Vector2(size.x, 2), 0, *WinS::bp);
}
