#ifndef Game_h__
#define Game_h__


#include <glog/logging.h>
#include <glew.h>
#include <glfw3.h>
#include "Render.h"
#include "GameTimer.h"
#include "SpriteAtlas.h"
#include "Font.h"
#include "JargShader.h"
#include "TextureManager.h"
#include "SpriteBatch.h"

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

	//
	Texture atlas;
	JargShader* ShaderID;
	JargShader* ShaderLines;
	glm::mat4 MVP;
	Font* big, *smallf, *giantf;
	Batched sb;
	unsigned int mvpID;

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

