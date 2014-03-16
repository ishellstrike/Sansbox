#include "Map.h"
#include "SpriteAtlas.h"


Map::Map(void) : buffer(false, true, false)
{
}


Map::~Map(void)
{

}

void Map::CreateGeometry()
{
	geometryCube.SetFromAtlasAllSide(1);
	
	for(int x = 0; x < 64; x++)
		for(int z = 0; z < 64; z++)
			for(int y = 0; y < 1; y++)
			{
				map[x][y][z].full = true;
				map[x][y][z].visible = 0;
			}
	
	for(int x = 1; x < 63; x++)
		for(int z = 1; z < 63; z++)
			for(int y = 1; y < 1; y++)
			{
				if( map[x - 1][y][z].full ) map[x][y][z].visible ++;
				if( map[x + 1][y][z].full ) map[x][y][z].visible ++;
				if( map[x][y - 1][z].full ) map[x][y][z].visible ++;
				if( map[x][y + 1][z].full ) map[x][y][z].visible ++;
				if( map[x][y][z - 1].full ) map[x][y][z].visible ++;
				if( map[x][y][z + 1].full ) map[x][y][z].visible ++;
			}

	for(int x = 0; x < 64; x++)
		for(int z = 0; z < 64; z++)
			for(int y = 0; y < 1; y++)
			{
				if(map[x][y][z].visible < 6)
				{
					geometryCube.SetPos(vec3(x, y, z));
					buffer.PushBack(geometryCube.GetBufferArray());
				}
			}
	buffer.CreateVideoBuffer("MapBuffer");
}

void Map::Draw()
{
	buffer.Draw();
}
