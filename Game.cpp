#include "Game.h"
#include "Bitmap.h"
#include "TextureManager.h"
#include "ImageAtlas.h"
#include "Font.h"

#include <vector>
#include "OldCube.h"
#include "Camera.h"
#define GLM_FORCE_RADIANS
#include <gtc/matrix_transform.hpp>
#include "Keyboard.h"
#include "Mouse.h"
#include "JRectangle.h"

#include "utf8.h"
#include "FPSCounter.h"
#include "SpriteAtlas.h"

#include "GraphicText.h"
#include "glog/logging.h"
#include "GameLevel.h"
#include <boost/thread/thread.hpp>
#include "JargShader.h"
#include "SpriteBatch.h"
#include "Vector.h"
#include <vector>
#include "WinS.h"
#include "Win.h"
#include <string>
#include "JButton.h"
#include "WComponent.h"
#include "AutoVersion.h"
#include "DataJsonParser.h"
#include "Registry.h"
#include "Mesh.h"
#include "Icosahedron.h"
#include "Quad.h"
#include "SphereTesselator.h"
#include "Cube.h"
#include "DotEntity.h"
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include "bpPlane.h"
#include "bpSphere.h"
#include "debugDraw.h"

#define sqr(x)(x)*(x)

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

void SetMouseButtonCallbackGLFW3(GLFWwindow *window, int a, int b, int c)
{
	Mouse::SetButton(a, b, c);
}

void WindowFocusCallbackGLFW3(GLFWwindow *window, int focused)
{
	Mouse::WindowFocus(focused);
}

void errorCallbackGLFW3(int error, const char* description)
{
	LOG(ERROR) << description;
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

int Game::Initialize()
{
#if WIN32 && _DEBUG
	//system ("");
#endif
	google::InitGoogleLogging("Jarg.exe");
	google::SetLogFilenameExtension(".txt");
	google::SetLogDestination(google::INFO, "logs/");
	LOG(INFO) << "Jarg initialization start";
	glfwSetErrorCallback(errorCallbackGLFW3);

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
	glfwSetWindowTitle(window, AutoVersion::GetTitle().c_str());
	
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
	glfwSetMouseButtonCallback(window, SetMouseButtonCallbackGLFW3);
	wire = 0;

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
	//SpriteAtlas::Instance().Loading("Textures/");

	atlas.Load("spriteatlas.png");
	test.Load("img.png");

	ShaderID = new JargShader();
	ShaderID->LoadFromFile("shaders/t2.fs", "shaders/t2.vs");
	mvpBasic = ShaderID->LocateVars("MVP");
	worldID = ShaderID->LocateVars("World");

	ShaderLines = new JargShader();
	ShaderLines->LoadFromFile("shaders/lines.fs", "shaders/lines.vs");
	mvpLine = ShaderLines->LocateVars("MVP");


	MVP = render->GetOrthoProjection();
	glUniformMatrix4fv(mvpBasic, 1, GL_FALSE, &MVP[0][0]);

	big = new Font();
	big->Init();
	big->Create("font.json");

	smallf = new Font();
	smallf->Init();
	smallf->Create("fontsmall.json");

	giantf = new Font();
	giantf->Init();
	giantf->Create("fontgiant.json");

	sb.Init(ShaderID, ShaderLines);

	Registry::Init();
}

int Game::Run()
{

	if(!Initialize()) 
	{
		LOG(ERROR) << "Инициализация завершилась с ошибками.";
		return -1;
	}

	LoadContent();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	Camera camera;
	camera.SetWindowSize(width, height);
	glm::mat4 model = glm::mat4(1.0f);
	MVP = camera.CalculateMatrix() * model;

	glm::mat4 Identity(1.0f);
	glm::mat4 World(1.0f);

	WinS* ws = new WinS(&sb, smallf);
	Win* w;
	for(int i = 0; i< 10; i++) {
		w = new Win(Vector2(100 +i*5, 100 +i*5), Vector2(200,200));
		ws->windows.push_back(w);
		JButton* jb = new JButton(Vector2(10,100), Vector2(50,20));
		jb->parent = w;
		w->Items.push_back(jb);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 1);

	GLint colorTextureLocation = -1;
	colorTextureLocation = ShaderID->LocateVars("colorTexture");


	Mesh* ico = Cube::GetMesh();
	ico->Bind();
	ico->texture = &test;
	ico->shader = ShaderID;
	ico->World = glm::scale(glm::mat4(1.0f), vec3(6));

	Mesh* mm = ico;
	mm = Tesselator::SphereTesselate(2, *ico);
	mm->Bind();
	mm->texture = &test;
	mm->shader = ShaderID;
	mm->World = glm::scale(glm::mat4(1.0f), vec3(6));

	float const speed = 0.05f;

	FPSCounter fps;

	StringBatch fpsText;
	int tesse = 1;

	std::vector<DotEntity> ent;

	ent.push_back(DotEntity(Vector3(0,0,0), Vector3(0), 1000));
	ent.push_back(DotEntity(Vector3(-20,-20,0), Vector3(-1,0,0), 100));
	ent.push_back(DotEntity(Vector3(20,20,0), Vector3(1,1,0), 100));
	ent.push_back(DotEntity(Vector3(-20,20,0), Vector3(1,0,0), 100));
	ent.push_back(DotEntity(Vector3(20,-20,0), Vector3(0,1,0), 100));


	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-9.8,0));
	GLDebugDrawer* drawer = new GLDebugDrawer();
	drawer->setDebugMode(true);
	dynamicsWorld->setDebugDrawer(drawer);
	drawer->SetBatched(&sb);

	std::vector<bpSphere*> spheres;
	bpSphere* sphere1 = new bpSphere();
	sphere1->bpRegister(dynamicsWorld);
	spheres.push_back(sphere1);

	bpPlane* plane1 = new bpPlane();
	plane1->bpRegister(dynamicsWorld);

	while(Running && !glfwWindowShouldClose(window)) 
	{
		glEnable(GL_DEPTH_TEST);
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

		if(Keyboard::isKeyPress(GLFW_KEY_F2)){
			switch(wire){
			case 0:
				glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
				wire = 1;
				break;	
			case 1:
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
				wire = 2;
				break;
			default:
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
				wire = 0;
				break;
			}
		}
		
		if(Keyboard::isKeyPress(GLFW_KEY_F3)){
			ent.clear();
			ent.push_back(DotEntity(Vector3(0,0,0), Vector3(0), 1.98892e+30));
			for(int i =0; i< 10; i++){
				ent.push_back(DotEntity(Vector3(i*149597871000,i*149597871000,0), Vector3(29783,0,0), 5.972e+24));
			}
		}

		if(Keyboard::isKeyPress(GLFW_KEY_F4)){
			bpSphere* sphere1 = new bpSphere();
			sphere1->bpRegister(dynamicsWorld);
			spheres.push_back(sphere1);
		}

		//for (int i=0; i< ent.size(); i++)
		//{
		//	DotEntity& p0 = ent[i];
		//	for (int j=0; j< ent.size(); j++)
		//	{
		//		if(i!=j){
		//			DotEntity& p = ent[j];
		//			float d = sqrt(sqr(p0.pos.x - p.pos.x) + sqr(p0.pos.y - p.pos.y) + sqr(p0.pos.z - p.pos.z));
		//			if(d > 3){
		//				p0.vel.x += 6.67545e-23 * p.mass /d /d * (p.pos.x - p0.pos.x)/d;
		//				p0.vel.y += 6.67545e-23 * p.mass /d /d * (p.pos.y - p0.pos.y)/d;
		//				p0.vel.z += 6.67545e-23 * p.mass /d /d * (p.pos.z - p0.pos.z)/d;
		//			}
		//			/*if(d < 3) {
		//				p0.vel = (p.vel*2*p.mass+p0.vel*(p0.mass-p.mass))/(p0.mass+p.mass);
		//				p.vel = (p0.vel*2*p0.mass+p.vel*(p.mass-p0.mass))/(p0.mass+p.mass);
		//			}*/
		//		}
		//	}
		//	p0.pos += p0.vel * gt.elapsed * 1000;
		//}

// 		float dx = float(Mouse::IsMoveCursorX());
// 		if( dx != 0)
// 		{
// 			camera.RotateX( dx );
// 		}

// 		float dy = float(Mouse::IsMoveCursorY());
// 		if( dy != 0)
// 		{
// 			camera.RotateY( dy );
// 		}
		camera.view = glm::lookAt(vec3(20,20,20), vec3(0,0,0), vec3(0,1,0));

		MVP = camera.CalculateMatrix() * model;
	
		
		// Use our shader
		ShaderID->BindProgram();
		glUniformMatrix4fv(mvpBasic, 1, GL_FALSE, &MVP[0][0]);
		glUniform1i(colorTextureLocation, 1);

		//mm->World = glm::rotate(mm->World, (float)gt.elapsed, vec3(1,0,1));
		/*for (int i =0; i< ent.size(); i++)
		{
		mm->World = glm::scale(Identity, vec3(6,6,6));
		mm->World = glm::translate(mm->World, vec3(ent[i].pos.x/10000000.0,ent[i].pos.y/10000000.0,ent[i].pos.z/100000000.0));
		mm->Render();
		}*/

		if(wire != 2)
		for (unsigned int i =0; i< spheres.size(); i++)
		{
			
			btTransform trans;
			spheres[i]->fallRigidBody->getMotionState()->getWorldTransform(trans);
			auto q = trans.getRotation();
			auto t = trans.getOrigin();
			mm->World = glm::translate(Identity, vec3(t.getX(),t.getY(),t.getZ()));
			mm->World = glm::rotate(mm->World, q.getAngle(), vec3(q.getAxis().x(), q.getAxis().y(), q.getAxis().z()));
			mm->World = glm::scale(mm->World, vec3(1,1,1));
			mm->Render();
		}

		//glDisable(GL_DEPTH_TEST);
		glUniformMatrix4fv(worldID, 1, GL_FALSE, &Identity[0][0]);


		if(wire == 2) {
			
			ShaderLines->BindProgram();
			glUniformMatrix4fv(mvpLine, 1, GL_FALSE, &MVP[0][0]);
			dynamicsWorld->debugDrawWorld();
			sb.RenderFinallyWorld();
		}
		//after debug draw calc
		dynamicsWorld->stepSimulation(gt.elapsed,10);

		//glDisable(GL_DEPTH_TEST);
		MVP = render->GetOrthoProjection();
		glUniformMatrix4fv(mvpBasic, 1, GL_FALSE, &MVP[0][0]);
		ShaderLines->BindProgram();
		glUniformMatrix4fv(mvpLine, 1, GL_FALSE, &MVP[0][0]);

		

		WinS::sb->DrawString(Vector2(10,10), std::to_string((long double)fps.GetCount()).append(" ").append(std::to_string((long double)tesse)).append(" ").append(std::to_string((long double)mm->indeces.size()/3)), *smallf);
		ws->Update(gt);
		ws->Draw();
		//sb.DrawQuad(Vector2(10,10), Vector2(100,100), atlas);
		int dc = sb.RenderFinally();



		fps.Update(gt);
		Mouse::Update();

		glfwSwapBuffers(window);
		glfwPollEvents();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(16));
	}
	

	UnloadContent();
	delete ShaderID;
	big->Remove();
	delete big;
	delete ws;
	delete smallf;
	delete giantf;

	for (unsigned int i =0; i< spheres.size(); i++)
	{
		spheres[i]->bpUnregister(dynamicsWorld);
		delete spheres[i];
	}
	spheres.clear();

	plane1->bpUnregister(dynamicsWorld);
	delete plane1;

	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;


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
	
}

void Game::ResizeWindow( unsigned int _width, unsigned int _height )
{
	
// 	width = _width;
// 	height = _height;
// 	render->ResizeWindow(width, height);
	
}
