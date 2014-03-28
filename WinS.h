#ifndef WinS_h__
#define WinS_h__
#include "SpriteBatch.h"
#include "TextureManager.h"
#include <vector>
#include "Win.h"

class WinS{
public:
	WinS();
	WinS(Batched* sb_, Font* fnt);
	~WinS();
	std::vector<Win> windows;

	void Draw();
	static Batched* sb;
	static Texture* bp;
	static Font* font;
};
#endif // WinS_h__