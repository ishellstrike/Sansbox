#include "SpriteAtlas.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp> 

SpriteAtlas::SpriteAtlas(void)
{

}

SpriteAtlas::~SpriteAtlas(void)
{
	
}

namespace fs = boost::filesystem; 

int CountFiles(char* dir){
	int i = 0;
	fs::path targetDir(dir); 

	fs::recursive_directory_iterator it(targetDir), eod;

	iRect rec(0,0,32,32);

	BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod))  
	{ 
		if(is_regular_file(p) && p.extension() == ".png")
		{
			i++;
		} 
	}
	return i;
}

void SpriteAtlas::Loading(char* dir)
{
	int cou = CountFiles(dir);
	MajorAtlas = new ImageAtlas();
	MajorAtlas->Create(Bitmap::FORMAT_RGBA, 2048, (cou/64+1)*32);

	fs::path targetDir(dir); 

	fs::recursive_directory_iterator it(targetDir), eod;

	iRect rec(0,0,1,1);

	BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod))  
	{ 
		if(is_regular_file(p) && p.extension() == ".png")
		{
			Bitmap *b = new Bitmap();
			b->Load(p.string());

			MajorAtlas->InsertImage(b, rec);

			b->Free();
		} 
	}

	//MajorAtlas->GetAtlas()->Save("spriteatlas.png");
	//MajorAtlas->Remove();
}

