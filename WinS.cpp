#include "WinS.h"

WinS::WinS()
{

}

WinS::WinS(Batched* sb_, Font* fnt)
{
	WinS::sb = sb_;
	WinS::bp = new Texture();
	WinS::bp->Load("wp.png");
	font = fnt;
}

WinS::~WinS()
{

}

void WinS::Draw()
{
	if(windows.size() > 0){
		for (int i =0; i< windows.size(); i++)
		{
			windows.at(i).Draw();
		}
	}
}

Font* WinS::font;

Texture* WinS::bp;

Batched* WinS::sb;

