#ifndef SpriteAtlas_h__
#define SpriteAtlas_h__

#include "ImageAtlas.h";

class SpriteAtlas{
public:
	SpriteAtlas(void);
	~SpriteAtlas(void);

	ImageAtlas* MajorAtlas;

	void Loading(char* dir);
};

#endif // SpriteAtlas_h__
