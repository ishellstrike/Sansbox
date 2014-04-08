#pragma once
#ifndef SpriteAtlas_h__
#define SpriteAtlas_h__

#include "ImageAtlas.h";
#include "TextureManager.h"

class SpriteAtlas{
public:
	~SpriteAtlas(void);

	Bitmap* MajorAtlas;
	Texture atlasTex;

	void Loading(char* dir);

	float SpriteW, SpriteH;
	static SpriteAtlas& Instance();

private:        
        SpriteAtlas(){};
        SpriteAtlas(const SpriteAtlas& root);
        SpriteAtlas& operator=(const SpriteAtlas&);
		void Free();
};

#endif // SpriteAtlas_h__
