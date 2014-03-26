#include "Window.h"
#include "SpriteBatch.h"
#include "WindowSystem.h"
#include "Vector.h"



void Window::Draw()
{
	//WindowSystem.sb.DrawQuad(pos, size, 0, WindowSystem.bp);
}

void Window::Update()
{
	
}

Window::Window()
{
	
}

Window::Window(Vector2 pos_, Vector2 size_)
{
	pos = pos_;
	size = size_;
}
