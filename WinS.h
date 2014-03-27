#ifndef WinS_h__
#define WinS_h__
#include "SpriteBatch.h"
#include "TextureManager.h"
#include <vector>
#include "Win.h"

class WinS{
public:
	WinS();
	WinS(SpriteBatch* sb_);
	~WinS();
	std::vector<Win> windows;

	void Draw();
	static SpriteBatch* sb;
	static Texture* bp;
};
#endif // WinS_h__
