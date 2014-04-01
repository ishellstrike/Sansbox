#include "JButton.h"
#include "WComponent.h"
#include "SpriteBatch.h"
#include "WinS.h"
#include "GameMath.h"
#include "Mouse.h"

JButton::JButton(void)
{
}

JButton::JButton(Vector2 pos_, Vector2 size_)
{
	pos = pos_; size = size_;
}


JButton::~JButton(void)
{
}

void JButton::Draw()
{
	Batched& sb = *WinS::sb;
	Vector2 Pos = GlobalPos();
	Color4 col;
	if(aimed){
		col = Color4::White;
	} else {
		col = Color4::Red;
	}
	sb.DrawLine(Pos, Vector2(Pos.x, Pos.y + size.y), 2, col);
	sb.DrawLine(Pos, Vector2(Pos.x + size.x, Pos.y), 2, col);
	sb.DrawString(Pos + Vector2(3,-8), "Button", *WinS::font);
	sb.DrawLine(Vector2(Pos.x, Pos.y + size.y), Pos + size, 2, col);
	sb.DrawLine(Vector2(Pos.x + size.x, Pos.y), Pos + size, 2, col);
}

void JButton::Update()
{
	Vector2 wpos = GlobalPos();
	if(inLims(Mouse::GetCursorPos(), wpos, wpos + size)){
		aimed = true;
	} else {
		aimed = false;
	}
}

Vector2 JButton::GlobalPos()
{
	return parent->GlobalPos() + pos;
}
