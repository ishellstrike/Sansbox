#include "Mouse.h"


GLFWwindow *Mouse::window;

double Mouse::xpos;
double Mouse::ypos;

double Mouse::dxpos;
double Mouse::dypos;

unsigned int Mouse::windowWidth;
unsigned int Mouse::windowHeight;

bool Mouse::stateFixedMousePos;
bool Mouse::isCursorClientArea;
bool Mouse::isWindowFocused;

void Mouse::Init( GLFWwindow *win )
{
	window = win;
	xpos = 1.0;
	ypos = 1.0;
	dxpos = 0.0;
	dypos = 0.0;
	windowWidth = 0;
	windowHeight = 0;
	stateFixedMousePos = false;
	isCursorClientArea = true;
	isWindowFocused = true;

	glfwSetCursorPos(window, xpos, ypos);
}


void Mouse::SetButton( int button, int state ,int c )
{
	Mouse::Buttons[button] = state;
}

void Mouse::SetCursorPos( double x, double y )
{
	if(!isWindowFocused)
		return;

	dxpos = x - xpos;
	dypos = y - ypos;
	deltaxpos = dxpos;
	deltaypos = dypos;
	lastxpos = xpos;
	lastypos = ypos;

	if(!isCursorClientArea)
	{
		dxpos = 0.0;
		dypos = 0.0;
	}

	if(stateFixedMousePos)
	{
		// устанавливаем курсор в центр экрана
		xpos = double(windowWidth) / 2.0;
		ypos = double(windowHeight) / 2.0;
		glfwSetCursorPos(window, xpos, ypos);
	}
	else
	{
		xpos = x;
		ypos = y;
	}
}

double Mouse::IsMoveCursorX()
{
	double dx = dxpos;
	dxpos = 0.0;
	return dx;
}

double Mouse::IsMoveCursorY()
{
	double dy = dypos;
	dypos = 0.0;
	return dy;
}

void Mouse::GetCursorPos( double &x, double &y )
{
	x = xpos;
	y = ypos;
}

Vector2 Mouse::GetCursorPos()
{
	return Vector2(xpos, ypos);
}

void Mouse::SetFixedPosState( bool state )
{
	stateFixedMousePos = state;
	if(stateFixedMousePos)
	{
		xpos = double(windowWidth) / 2.0;
		ypos = double(windowHeight) / 2.0;
		dxpos = 0.0;
		dypos = 0.0;
		glfwSetCursorPos(window, xpos, ypos);
	}
}

void Mouse::SetWindowSize( unsigned int width, unsigned int height )
{
	windowWidth = width;
	windowHeight = height;
}

void Mouse::CursorClientArea( int entered )
{
	if(entered == GL_TRUE)
	{
		isCursorClientArea = true;
		glfwGetCursorPos(window, &xpos, &ypos);
	}
	else
	{
		isCursorClientArea = false;
	}
}

void Mouse::Update(){
	deltaypos = 0;
	deltaxpos = 0;
}

void Mouse::WindowFocus( int focused )
{
	if(focused == GL_TRUE)
	{
		isWindowFocused = true;
		glfwGetCursorPos(window, &xpos, &ypos);
	}
	else
	{
		isWindowFocused = false;
	}
}

bool Mouse::IsRightPressed()
{
	return Buttons[GLFW_MOUSE_BUTTON_RIGHT] == GLFW_PRESS;
}

bool Mouse::IsLeftPressed()
{
	return Buttons[GLFW_MOUSE_BUTTON_LEFT] == GLFW_PRESS;
}

Vector2 Mouse::GetCursorDelta()
{
	return Vector2(deltaxpos, deltaypos);
}

Vector2 Mouse::GetCursorLastPos()
{
	return Vector2(lastxpos, lastypos);
}

double Mouse::lastypos;
double Mouse::lastxpos;
double Mouse::deltaypos;
double Mouse::deltaxpos;
int Mouse::Buttons[10];

