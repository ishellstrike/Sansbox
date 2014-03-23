#ifndef Game_h__
#define Game_h__


#include <glog/logging.h>
#include <glew.h>
#include <glfw3.h>
#include "Render.h"
#include "GameTimer.h"
#include "SpriteAtlas.h"
#include <ostream>

template< typename T >
std::string ToString( const T& val )
{
	std::stringstream iss;
	iss << val;
	return iss.str();
}

class Game
{
protected:

	bool Running;

	const char* title;
	unsigned int width;
	unsigned int height;
	bool fullscreen;

	GLFWwindow* window;

	Render* render;

	unsigned int texture;

	GameTimer gt;

public:
	Game(void);
	~Game(void);

	int Run();

	virtual int Initialize();
	virtual void LoadContent(); 
	virtual void Update();
	virtual void Draw();
	virtual void ResizeWindow(unsigned int width, unsigned int height);
	virtual void UnloadContent(); 

};


#endif // Game_h__

