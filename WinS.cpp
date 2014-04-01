#include "WinS.h"
#include "GameTimer.h"
#include <vector>

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
	if(windows.size() > 0){
		for(int i=0 ;i< windows.size(); i++){
			delete windows.at(i);
		}
	}
	windows.clear();
}

void WinS::Draw()
{
	if(windows.size() > 0) {
		for (int i =0; i< windows.size(); i++) {
			windows.at(i)->Draw();
		}
	}
}

void WinS::ToTop(Win* w){
	std::vector<Win*>::iterator iter;
	int i =0;
	for (iter = windows.begin() ; iter != windows.end(); ++iter){
		if(*iter == w){
			Win* temp = w;
			windows[i] = windows[windows.size() - 1];
			windows[windows.size() - 1] = temp;
			return;
		}
		i++;
	}
}

void WinS::Update(GameTimer gt){
	MouseHooked = false;
	if(windows.size() > 0) {
		for (int i =windows.size() - 1; i >= 0; i--) {
			windows.at(i)->Update();
		}
	}
}

std::vector<Win*> WinS::windows;

bool WinS::MouseHooked;
Font* WinS::font;
Texture* WinS::bp;
Batched* WinS::sb;

