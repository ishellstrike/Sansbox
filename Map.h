#ifndef Map_h__
#define Map_h__

#include "OldCube.h"
#include "TextureManager.h"

struct B
{
	unsigned char full;
	unsigned char visible;
};

class Map
{
private:
	BufferArray buffer;
	B map[64][1][64];
	
	OldCube geometryCube;

public:
	Map(void);
	~Map(void);

	void CreateGeometry(Texture* atlas);

	void Draw();

};


#endif // Map_h__