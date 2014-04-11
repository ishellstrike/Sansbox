#include "Win.h"
#include "Vector.h"
#include "WinS.h"
#include <detail\type_vec.hpp>
#include "Mouse.h"
#include <vector>


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
	if(Items.size() > 0){
		for(int i=0; i< Items.size(); i++){
			delete Items[i];
		}
	}
	Items.clear();
}

void Win::Draw()
{
	/*WinS::sb->DrawQuad(pos, Vector2(size.x, 2), 0, *WinS::bp);
	WinS::sb->DrawQuad(Vector2(pos.x, pos.y + 20), Vector2(size.x, 2), 0, *WinS::bp);
	WinS::sb->DrawQuad(pos, Vector2(2, size.y), 0, *WinS::bp);
	WinS::sb->DrawQuad(Vector2(pos.x + size.x - 2, pos.y), Vector2(2, size.y), 0, *WinS::bp);
	WinS::sb->DrawQuad(Vector2(pos.x, pos.y + size.y - 2), Vector2(size.x, 2), 0, *WinS::bp);*/

	Batched& sb = *WinS::sb;
	
	sb.DrawRectangle(pos, size, Color4(1.F,0.F,0.F,0.5F));
	sb.DrawString(pos + Vector2(3,-8), "azazazaadasdasd", *WinS::font);
	sb.DrawLine(pos, Vector2(pos.x, pos.y + size.y), 2, Color4(1.F,1.F,1.F,0.5F));

	sb.DrawLine(pos, Vector2(pos.x + size.x, pos.y), 2, Color4::White);
	sb.DrawLine(pos + Vector2(0,20), Vector2(pos.x + size.x, pos.y + 20), 2, Color4::White);
	sb.DrawLine(Vector2(pos.x, pos.y + size.y), pos + size, 2, Color4::White);
	sb.DrawLine(Vector2(pos.x + size.x, pos.y), pos + size, 2, Color4::White);

	if(Items.size() > 0){
		for(int i=0; i< Items.size(); i++){
			Items[i]->Draw();
		}
	}


}

void Win::Update()
{
	Vector2 wpos = GlobalPos();
	if(!WinS::MouseHooked && inLims(Mouse::GetCursorLastPos(), wpos, wpos + Vector2(size.x,20))){
		if(Mouse::IsLeftPressed()){
			pos += Mouse::GetCursorDelta();
		}
	}
	if(!WinS::MouseHooked && inLims(Mouse::GetCursorLastPos(), wpos, wpos + size)){
		if(Mouse::IsLeftPressed()){
			WinS::MouseHooked = true;
			WinS::ToTop(this);
		}
	}

	if(Items.size() > 0){
		for(int i=0; i< Items.size(); i++){
			Items[i]->Update();
		}
	}
}

Vector2 Win::GlobalPos()
{
	return pos;
}
