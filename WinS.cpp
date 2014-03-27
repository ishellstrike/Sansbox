#include "WinS.h"

WinS::WinS()
{

}

WinS::WinS(SpriteBatch* sb_)
{
	WinS::sb = sb_;
	WinS::bp = new Texture();
	WinS::bp->Load("wp.png");
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

Texture* WinS::bp;

SpriteBatch* WinS::sb;

