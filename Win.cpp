#include "Win.h"
#include "Vector.h"
#include "WinS.h"
#include <detail\type_vec.hpp>


Win::Win(void)
{
}

Win::Win(vec2 p, vec2 s)
{
	size = s;
	pos = p;
}


Win::~Win(void)
{
}

void Win::Draw()
{
	/*WinS::sb->DrawQuad(pos, Vector2(size.x, 2), 0, *WinS::bp);
	WinS::sb->DrawQuad(Vector2(pos.x, pos.y + 20), Vector2(size.x, 2), 0, *WinS::bp);
	WinS::sb->DrawQuad(pos, Vector2(2, size.y), 0, *WinS::bp);
	WinS::sb->DrawQuad(Vector2(pos.x + size.x - 2, pos.y), Vector2(2, size.y), 0, *WinS::bp);
	WinS::sb->DrawQuad(Vector2(pos.x, pos.y + size.y - 2), Vector2(size.x, 2), 0, *WinS::bp);*/

	//WinS::sb->DrawRectangle(pos, size, Color4(0.0F,0.5F,0.5F,0.5F));

	//WinS::sb->DrawLine(pos, vec2(pos[0], pos[0] + size[1]), 2, Color4::White);
	//WinS::sb->DrawLine(pos, vec2(pos[0] + size[0], pos[1]), 2, Color4::White);
	//WinS::sb->DrawLine(pos + vec2(0,20), vec2(pos[0] + size[0], pos[1] + 20), 2, Color4::White);
	WinS::sb->DrawString(pos + vec2(3,-8), "azazazaadasdasd234234234", *WinS::font);
	//WinS::sb->DrawLine(vec2(pos[0], pos[1] + size[1]), vec2(pos[0]  + size[0], pos[1] + size[1]), 2, Color4::White);
	//WinS::sb->DrawLine(vec2(pos[0] + size[0], pos[1]), vec2(pos[0]  + size[0], pos[1] + size[1]), 2, Color4::White);
}
