#pragma once
#ifndef Mouse_h__
#define Mouse_h__

#include <glfw3.h>
#include "Vector.h"

class Mouse
{
private:
	static GLFWwindow *window;

	static double xpos;
	static double ypos;

	static double dxpos;
	static double dypos;

	static double lastxpos;
	static double lastypos;

	static double deltaxpos;
	static double deltaypos;

	static unsigned int windowWidth;
	static unsigned int windowHeight;

	static bool stateFixedMousePos;
	static bool isCursorClientArea;
	static bool isWindowFocused;
	static int Buttons[10];

public:

	static void CursorClientArea(int entered);
	static void SetButton(int a, int b, int c);
	static void SetCursorPos(double xpos, double ypos);
	static void WindowFocus(int focused);

	static void Init( GLFWwindow *win );

	static void SetFixedPosState( bool state);

	static bool GetFixedPosState()
	{
		return stateFixedMousePos;
	}

	static void SetWindowSize(unsigned int width, unsigned int height);

	static void GetCursorPos(double &xpos, double &ypos);
	static Vector2 GetCursorPos();
	static Vector2 GetCursorLastPos();
	static Vector2 GetCursorDelta();

	static double IsMoveCursorX();
	static double IsMoveCursorY();

	static bool IsRightPressed();
	static bool IsLeftPressed();
	static void Update();
};


#endif // Mouse_h__