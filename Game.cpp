#include "Game.h"
#include "Bitmap.h"
#include "TextureManager.h"
#include "ImageAtlas.h"
#include "Font.h"

#include <vector>
#include "Cube.h"
#include "Camera.h"
#define GLM_FORCE_RADIANS
#include <gtc/matrix_transform.hpp>
#include "Keyboard.h"
#include "Mouse.h"
#include "JRectangle.h"

#include "utf8.h"
#include "Map.h"
#include "FPSCounter.h"
#include "SpriteAtlas.h"

#include "GraphicText.h"
#include "glog/logging.h"
#include "GameLevel.h"
#include <boost/thread/thread.hpp>
#include "JargShader.h"
#include "CoreMod.h"
#include "SpriteBatch.h"
#include "Vector.h"
#include <vector>
#include "WinS.h"
#include "Win.h"
#include <string>

void KeyCallbackGLFW3(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	Keyboard::SetKey(key, scancode, action, mods);
}

void CursorPosCallbackGLFW3(GLFWwindow *window, double xpos, double ypos)
{
	Mouse::SetCursorPos(xpos, ypos);
}

void CursorClientAreaCallbackGLFW3(GLFWwindow *window, int entered)
{
	Mouse::CursorClientArea(entered);
}

void WindowFocusCallbackGLFW3(GLFWwindow *window, int focused)
{
	Mouse::WindowFocus(focused);
}

void errorCallbackGLFW3(int error, const char* description)
{
	
}

Game::Game(void)
{
	srand(1);
	Running = true;

	title = "Game";
	width = 800;
	height = 600;
	fullscreen = false;
	render = nullptr;
}


Game::~Game(void)
{

}

CoreMod* cm;
int Game::Initialize()
{

	google::InitGoogleLogging("Jarg.exe");
	google::SetLogDestination(google::INFO, "logs/");
	LOG(INFO) << "Jarg initialization start";
	glfwSetErrorCallback(errorCallbackGLFW3);

	cm = new CoreMod();
	cm->Load();

	int glfwErrorCode = glfwInit();
	if (!glfwErrorCode)
	{
		LOG(ERROR) << "glfwInit error " << glfwErrorCode;
		return glfwErrorCode;
	}
	
	//glfwWindowHint(GLFW_SAMPLES, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	LOG(INFO) <<"OpenGL: 3.3 glfw: " << glfwGetVersionString();

	GLFWmonitor *monitor = nullptr;
	if(fullscreen)
	{
		monitor = glfwGetPrimaryMonitor();
	}

	window = glfwCreateWindow(width, height, title, monitor, nullptr);
	if (!window)
	{
		glfwTerminate();
		LOG(FATAL) << "Ошибка создания окна GLFW.";
		return false;
	}
	glfwMakeContextCurrent(window);
	
	glfwSwapInterval(0);

	render = new Render;
	render->Init();
	render->SetWindowSize(width, height);

	Keyboard::Init();
	glfwSetKeyCallback(window, KeyCallbackGLFW3);

	Mouse::Init(window);
	Mouse::SetWindowSize(width, height);
//	Mouse::SetFixedPosState(true);
	glfwSetCursorPosCallback(window, CursorPosCallbackGLFW3);
	glfwSetCursorEnterCallback(window, CursorClientAreaCallbackGLFW3);	
	glfwSetWindowFocusCallback(window, WindowFocusCallbackGLFW3);


	//*******************************

	Bitmap *b = new Bitmap();

	b->Load("img.png");

	unsigned int texture = 0;
	texture = GenerateOpenglBitmap(*b, true, true);

	b->Free();

	return true;
}

void Game::LoadContent()
{
	SpriteAtlas::Instance().Loading("Textures/");
}

int Game::Run()
{

	if(!Initialize()) 
	{
		LOG(ERROR) << "Инициализация завершилась с ошибками.";
		return -1;
	}

	LoadContent();


	Texture atlas;
	atlas.Load("spriteatlas.png");

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Create and compile our GLSL program from the shaders
	JargShader* ShaderID = new JargShader();
	ShaderID->LoadFromFile("shaders/t2.fs", "shaders/t2.vs");
	unsigned int mvpID = ShaderID->LocateVars("MVP");

	JargShader* ShaderLines = new JargShader();
	ShaderLines->LoadFromFile("shaders/lines.fs", "shaders/lines.vs");
	ShaderLines->BindProgram();
	unsigned int mvpLine = ShaderLines->LocateVars("MVP");
	glm::mat4 MVP = render->GetOrthoProjection();
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);

	Camera camera;
	camera.SetWindowSize(width, height);
	glm::mat4 model = glm::mat4(1.0f);
	MVP = camera.CalculateMatrix() * model;

 	JRectangle geometryRectangle;
 	geometryRectangle.SetPos(vec3(0, 50, -1));
 	geometryRectangle.SetSize(100, 100);
 	TextureOld tex;
 	tex.u1 = 0.0f;
 	tex.v1 = 0.0f;
 	tex.u2 = 1.0f;
 	tex.v2 = 1.0f;
 	geometryRectangle.SetTexture(tex);

	BufferArray ba;
	ba.Create(false, true, false);
	ba.PushBack(geometryRectangle.GetBufferArray());
	ba.CreateVideoBuffer();

//	Cube geometryCube;
//	geometryCube.SetTextureAllSide(tex);
//	geometryCube.GetBufferArray().CreateVideoBuffer();
// 
// 	char* twochars = "abggcde";
// 	std::vector<uint32_t> utf32result;
// 	utf8::utf8to32(twochars, twochars + 7, std::back_inserter(utf32result));
// 
	Font* big = new Font();
	big->Init();
	big->Create("font.json");

	Font* smallf = new Font();
	smallf->Init();
	smallf->Create("fontsmall.json");

	Font* giantf = new Font();
	giantf->Init();
	giantf->Create("fontgiant.json");

	Map map;
	map.CreateGeometry();

    Batched sb;
	sb.Init(ShaderID, ShaderLines);

	WinS* ws = new WinS(&sb, smallf);
	Win* w;
	for(int i = 0; i< 10; i++) {
		w = new Win(vec2(100 +i*5, 100 +i*5), vec2(200,200));
		ws->windows.push_back(w);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 1);

	GLint colorTextureLocation = -1;
	colorTextureLocation = ShaderID->LocateVars("colorTexture");

	float const speed = 0.05f;

	FPSCounter fps;

	StringBatch fpsText;

	while(Running && !glfwWindowShouldClose(window)) 
	{
		gt.Update(glfwGetTime());

		//glfwSetWindowTitle(window, a.c_str());

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(204/255.0F, 1.0f, 1.0f, 1.0f);

		if(Keyboard::isKeyDown(GLFW_KEY_W))
		{
			camera.MoveZ(speed);
		}

		if(Keyboard::isKeyDown(GLFW_KEY_S))
		{
			camera.MoveZ(-speed);
		}

		if(Keyboard::isKeyDown(GLFW_KEY_SPACE))
		{
			camera.MoveY(speed);
		}

		if(Keyboard::isKeyDown(GLFW_KEY_LEFT_SHIFT))
		{
			camera.MoveY(-speed);
		}

		if(Keyboard::isKeyDown(GLFW_KEY_D))
		{
			camera.MoveX(speed);
		}

		if(Keyboard::isKeyDown(GLFW_KEY_A))
		{
			camera.MoveX(-speed);
		}

		float dx = float(Mouse::IsMoveCursorX());
		if( dx != 0)
		{
			camera.RotateX( dx );
		}

		float dy = float(Mouse::IsMoveCursorY());
		if( dy != 0)
		{
			camera.RotateY( dy );
		}
		

		MVP = camera.CalculateMatrix() * model;
		// Use our shader
		ShaderID->BindProgram();
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);
		glUniform1i(colorTextureLocation, 1);

		glBindTexture(GL_TEXTURE_2D, 2);
		map.Draw();

		MVP = render->GetOrthoProjection();
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);

		WinS::sb->DrawString(vec2(10,10), "azazazaadasdasd", *smallf);
		ws->Draw();
		

		int dc = sb.RenderFinally();

		fps.Update(gt);
		glfwSetWindowTitle(window, std::to_string((long double)fps.GetCount()).append(" ").append(std::to_string((long double)dc)).c_str());
		//fpsText.Draw(a, 10, 10, big);
		//fpsText.Draw("cho cho, mnogo shriftov lolol 123123123 wertyuidfghjvbn", 40, 10, smallf);
		//fpsText.Draw("giant", 100, 100, giantf);

		glfwSwapBuffers(window);
		glfwPollEvents();
		//boost::this_thread::sleep_for(boost::chrono::milliseconds(16));
	}
	

	UnloadContent();
	delete ShaderID;
	big->Remove();
	delete big;
	delete ws;
	delete smallf;
	delete giantf;

	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

void Game::Update()
{

}

void Game::Draw()
{

}

void Game::UnloadContent()
{
	cm->Unload();
}

void Game::ResizeWindow( unsigned int _width, unsigned int _height )
{
	/*
	width = _width;
	height = _height;
	render->ResizeWindow(width, height);
	*/
}
