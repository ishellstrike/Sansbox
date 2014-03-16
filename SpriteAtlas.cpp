#include "SpriteAtlas.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp> 
#include <glfw3.h>
#include <glog/logging.h>

SpriteAtlas::~SpriteAtlas(void)
{
	Free();
}

namespace fs = boost::filesystem; 

int CountFiles(char* dir){
	int i = 0;
	fs::path targetDir(dir); 

	fs::recursive_directory_iterator it(targetDir), eod;

	BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod))  
	{ 
		if(is_regular_file(p) && p.extension() == ".png")
		{
			i++;
		} 
	}
	return i;
}

void SpriteAtlas::Free(){
	if(MajorAtlas != nullptr)
	{ 
		delete MajorAtlas;
		MajorAtlas = nullptr;
	}
}

SpriteAtlas& SpriteAtlas::Instance(){ static SpriteAtlas inst; return inst; }


void SpriteAtlas::Loading(char* dir)
{
	int cou = CountFiles(dir);
	int wsize = (cou/64+1)*32;
	SpriteW = 1.0/64;
	SpriteH = 1.0/(cou/64);
	if(fs::exists("spriteatlas.png")){
		return;
	}

	MajorAtlas = new Bitmap();
	MajorAtlas->Generate(Bitmap::FORMAT_RGBA, 2048, wsize, 0x00000000);
	LOG(INFO) << "Atlas rebuild " << 2048 << "x" << wsize;

	fs::path targetDir(dir); 

	fs::recursive_directory_iterator it(targetDir), eod;

	i32vec2 dstPoint(0,0);
	int i=0;
	BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod))  
	{ 
		if(is_regular_file(p) && p.extension() == ".png")
		{
			Bitmap *b = new Bitmap();
			b->Load(p.string());

			LOG(INFO) << p.filename() << " added";
			bool blitResult = MajorAtlas->Blit(&dstPoint, nullptr, b);
			i++;
			dstPoint.x = (i%64)*32;
			dstPoint.y = (i/64)*32;
			b->Free();
		} 
	}

	MajorAtlas->Save("spriteatlas.png");
	MajorAtlas->Free();
	MajorAtlas = nullptr;
}

