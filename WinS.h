#ifndef WinS_h__
#define WinS_h__
#include "SpriteBatch.h"
#include "TextureManager.h"
#include <vector>
#include "Win.h"
#include "GameTimer.h"

class WinS{
public:
	WinS();
	WinS(Batched* sb_, Font* fnt);
	~WinS();
	static std::vector<Win*> windows;
	static bool MouseHooked;

	void Draw();
	void Update(GameTimer gt);
	static void ToTop(Win* w);
	static Batched* sb;
	static Texture* bp;
	static Font* font;
};
#endif // WinS_h__
