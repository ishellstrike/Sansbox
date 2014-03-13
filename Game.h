#ifndef Game_h__
#define Game_h__

//#define GLFW_INCLUDE_GLU
//#pragma comment(lib, "glew32.lib") 
#include <glog/logging.h>
#pragma comment(lib, "libglog.lib")
#include <glew.h>
#include <glfw3.h>
#include "Render.h"
#include "GameTimer.h"
#include "SpriteAtlas.h"

class Game
{
protected:

	bool Running;

	const char* title;
	unsigned int width;
	unsigned int height;
	bool fullscreen;
	SpriteAtlas atlas;

	GLFWwindow *window;

	Render *render;

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

